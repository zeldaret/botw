#ifdef cafe
#include <cafe.h>
#include <nn/save.h>
#endif  // cafe

#ifdef NNSDK
#include <nn/fs.h>
#endif

#include <basis/seadNew.h>
#include <basis/seadRawPrint.h>
#include <devenv/seadEnvUtil.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <filedevice/seadPath.h>
#include <heap/seadHeapMgr.h>

namespace sead
{
SEAD_SINGLETON_DISPOSER_IMPL(FileDeviceMgr)

FileDeviceMgr::FileDeviceMgr()
{
    if (HeapMgr::sInstancePtr == NULL)
    {
        SEAD_ASSERT_MSG(false, "FileDeviceMgr need HeapMgr");
        return;
    }

    Heap* const heap = HeapMgr::instance()->findContainHeap(this);
    mount_(heap);

    mMainFileDevice = new (heap) MainFileDevice(heap);
    mount(mMainFileDevice);

    mDefaultFileDevice = mMainFileDevice;
}

FileDeviceMgr::~FileDeviceMgr()
{
    if (mMainFileDevice != NULL)
    {
        delete mMainFileDevice;
        mMainFileDevice = NULL;
    }
    unmount_();
}

void FileDeviceMgr::mount_([[maybe_unused]] Heap* heap)
{
#ifdef cafe
    FSInit();
    FSAddClient(&client, FS_RET_NO_ERROR);

    FSStateChangeParams changeParams = {
        .userCallback = stateChangeCallback_, .userContext = NULL, .ioMsgQueue = NULL};

    FSSetStateChangeNotification(&client, &changeParams);
    SAVEInit();
    _17A4[0] = 0;
    _1824 = 0;
#elif defined(NNSDK)
    // For release builds, only content is mounted using the regular nn::fs::MountRom.
    // For debug builds, content is mounted using nn::fs::MountRom or by mounting
    // SEAD_NIN_CONTENT_DIR on the host computer and the host root and SD are also mounted.
#ifdef SEAD_DEBUG
    const auto mount_host_result = nn::fs::MountHostRoot();
    if (mount_host_result.IsFailure())
    {
        SEAD_WARN("nn::fs::MountHostRoot() failed. module = %d desc = %d innervalue = 0x%08x",
                  mount_host_result.GetModule(), mount_host_result.GetDescription(),
                  mount_host_result.GetInnerValueForDebug());
        mMountedHost = false;
    }
    else
    {
        mMountedHost = true;
    }
#endif  // SEAD_DEBUG

#ifdef SEAD_DEBUG
    if (nn::fs::CanMountRomForDebug())
#endif
    {
        u64 cache_size = 0;
        const auto query_result = nn::fs::QueryMountRomCacheSize(&cache_size);
        SEAD_ASSERT_MSG(query_result.IsSuccess(),
                        "nn::fs::QueryMountRomCacheSize() failed. module = %d desc = %d "
                        "innervalue = 0x%08x",
                        query_result.GetModule(), query_result.GetDescription(),
                        query_result.GetInnerValueForDebug());

        SEAD_DEBUG_PRINT("FileDeviceMgr: MountRom cache size => %zd\n", cache_size);
        mRomCache = new (heap) u8[cache_size];

        const auto result = nn::fs::MountRom("content", mRomCache, cache_size);
        SEAD_ASSERT_MSG(result.IsSuccess(),
                        "nn::fs::MountRom() failed. module = %d desc = %d innervalue = 0x%08x",
                        result.GetModule(), result.GetDescription(),
                        result.GetInnerValueForDebug());
    }
#ifdef SEAD_DEBUG
    else
    {
        FixedSafeString<256> content_dir;
        if (EnvUtil::getEnvironmentVariable(&content_dir, "SEAD_NIN_CONTENT_DIR") == -1)
        {
            SEAD_WARN("SEAD_NIN_CONTENT_DIR is not set.");
        }
        else
        {
            const auto result = nn::fs::MountHost("content", content_dir.cstr());
            SEAD_ASSERT_MSG(result.IsSuccess(),
                            "nn::fs::MountHost() failed. module = %d desc = %d innervalue = 0x%08x",
                            result.GetModule(), result.GetDescription(),
                            result.GetInnerValueForDebug());
            system::Print("FileDeviceMgr: MountHost => %s\n", content_dir.cstr());
        }
    }

    const auto sd_result = nn::fs::MountSdCardForDebug("sd");
    mMountedSd = sd_result.IsSuccess();
    if (sd_result.IsSuccess())
        system::Print("FileDeviceMgr: mount SD card\n");
    else if (nn::fs::ResultMountNameAlreadyExists().Includes(sd_result))
        system::Print("FileDeviceMgr: SD card already mounted\n");
    else if (nn::fs::ResultSdCardAccessFailed().Includes(sd_result))
        system::Print("FileDeviceMgr: SD card is not ready\n");
#endif  // SEAD_DEBUG
#else
#error "Unknown platform"
#endif
}

void FileDeviceMgr::unmount_()
{
#ifdef cafe
    FSDelClient(&client, FS_RET_NO_ERROR);
    SAVEShutdown();
    FSShutdown();
#elif defined(NNSDK)
#ifdef SEAD_DEBUG
    if (mMountedHost)
        nn::fs::UnmountHostRoot();
#endif

    nn::fs::Unmount("content");
    if (mRomCache)
        delete[] mRomCache;

#ifdef SEAD_DEBUG
    if (mMountedSd)
        nn::fs::Unmount("sd");
#endif
#else
#error "Unknown platform"
#endif
}

void FileDeviceMgr::traceFilePath(const SafeString& path) const
{
    SEAD_DEBUG_PRINT("[FileDeviceMgr] %s\n", path.cstr());
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);

    if (device != NULL)
        device->traceFilePath(pathNoDrive);
    else
        SEAD_WARN("FileDevice not found: %s", path.cstr());
}

void FileDeviceMgr::traceDirectoryPath(const SafeString& path) const
{
    SEAD_DEBUG_PRINT("[FileDeviceMgr] %s\n", path.cstr());
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);

    if (device != NULL)
        device->traceDirectoryPath(pathNoDrive);
    else
        SEAD_WARN("FileDevice not found: %s", path.cstr());
}

void FileDeviceMgr::resolveFilePath(BufferedSafeString* out, const SafeString& path) const
{
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);

    if (device != NULL)
        device->resolveFilePath(out, pathNoDrive);
    else
        SEAD_WARN("FileDevice not found: %s", path.cstr());
}

void FileDeviceMgr::resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const
{
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);

    if (device != NULL)
        device->resolveDirectoryPath(out, pathNoDrive);
    else
        SEAD_WARN("FileDevice not found: %s", path.cstr());
}

void FileDeviceMgr::mount(FileDevice* device, const SafeString& name)
{
    if (!name.isEqual(SafeString::cEmptyString))
        device->setDriveName(name);

    mDeviceList.pushBack(device);
}

void FileDeviceMgr::unmount(FileDevice* device)
{
    mDeviceList.erase(device);

    if (device == mDefaultFileDevice)
        mDefaultFileDevice = NULL;
}

void FileDeviceMgr::unmount(const SafeString& name)
{
    auto* device = findDevice(name);
    if (!device)
    {
        SEAD_ASSERT_MSG(false, "drive not found: %s\n", name.cstr());
        return;
    }
    unmount(device);
}

FileDevice* FileDeviceMgr::findDeviceFromPath(const SafeString& path,
                                              BufferedSafeString* pathNoDrive) const
{
    FixedSafeString<32> driveName;
    FileDevice* device;

    if (!Path::getDriveName(&driveName, path))
    {
        device = mDefaultFileDevice;
        if (!device)
        {
            SEAD_ASSERT_MSG(false, "drive name not found and default file device is null");
            return nullptr;
        }
    }
    else
        device = findDevice(driveName);

    if (!device)
        return nullptr;

    if (pathNoDrive != NULL)
        Path::getPathExceptDrive(pathNoDrive, path);

    return device;
}

FileDevice* FileDeviceMgr::findDevice(const SafeString& name) const
{
    for (auto it = mDeviceList.begin(); it != mDeviceList.end(); ++it)
        if ((*it)->getDriveName() == name)
            return *it;

    return nullptr;
}

FileDevice* FileDeviceMgr::tryOpen(FileHandle* handle, const SafeString& path,
                                   FileDevice::FileOpenFlag flag, u32 divSize)
{
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);

    if (device == NULL)
        return NULL;

    return device->tryOpen(handle, pathNoDrive, flag, divSize);
}

FileDevice* FileDeviceMgr::tryOpenDirectory(DirectoryHandle* handle, const SafeString& path)
{
    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(path, &pathNoDrive);
    if (!device)
        return nullptr;

    if (!device->isExistDirectory(pathNoDrive))
        return nullptr;

    return device->tryOpenDirectory(handle, pathNoDrive);
}

u8* FileDeviceMgr::tryLoad(FileDevice::LoadArg& arg)
{
    SEAD_ASSERT_MSG(arg.path != SafeString::cEmptyString, "path is null");

    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(arg.path, &pathNoDrive);

    if (device == NULL)
        return NULL;

    FileDevice::LoadArg arg2(arg);
    arg2.path = pathNoDrive.cstr();

    u8* data = device->tryLoad(arg2);

    arg.read_size = arg2.read_size;
    arg.roundup_size = arg2.roundup_size;
    arg.need_unload = arg2.need_unload;

    return data;
}

void FileDeviceMgr::unload(u8* data)
{
    SEAD_ASSERT(data);
    if (data)
        delete data;
}

bool FileDeviceMgr::trySave(FileDevice::SaveArg& arg)
{
    SEAD_ASSERT_MSG(arg.path != SafeString::cEmptyString, "path is null");

    FixedSafeString<256> pathNoDrive;
    FileDevice* device = findDeviceFromPath(arg.path, &pathNoDrive);
    if (!device)
        return false;

    FileDevice::SaveArg arg2(arg);
    arg2.path = pathNoDrive.cstr();

    const bool ret = device->trySave(arg2);
    arg.write_size = arg2.write_size;
    return ret;
}

#ifdef NNSDK
void FileDeviceMgr::mountSaveDataForDebug(Heap*)
{
    const auto result = nn::fs::MountSaveDataForDebug("save");
    SEAD_ASSERT_MSG(
        result.IsSuccess(),
        "nn::fs::MountSaveDataForDebug() failed. module = %d desc = %d innervalue = 0x%08x",
        result.GetModule(), result.GetDescription(), result.GetInnerValueForDebug());
}

void FileDeviceMgr::unmountSaveDataForDebug()
{
    nn::fs::Unmount("save");
}
#endif

#ifdef cafe
void FileDeviceMgr::stateChangeCallback_(FSClient* client, FSVolumeState state, void* context)
{
    FSGetLastError(client);
}
#endif  // cafe

}  // namespace sead
