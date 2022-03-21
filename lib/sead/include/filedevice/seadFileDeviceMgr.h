#ifndef SEAD_FILEDEVICEMGR_H_
#define SEAD_FILEDEVICEMGR_H_

#ifdef cafe
#include <cafe.h>
#endif  // cafe

#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include <filedevice/seadFileDevice.h>
#include <filedevice/seadMainFileDevice.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>

namespace sead
{
class FileDeviceMgr
{
    SEAD_SINGLETON_DISPOSER(FileDeviceMgr)
    FileDeviceMgr();
    ~FileDeviceMgr();

public:
    void traceFilePath(const SafeString& path) const;
    void traceDirectoryPath(const SafeString& path) const;
    void resolveFilePath(BufferedSafeString* out, const SafeString& path) const;
    void resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const;

    void mount(FileDevice* device, const SafeString& name = SafeString::cEmptyString);
    void unmount(FileDevice* device);
    void unmount(const SafeString& name);
    FileDevice* findDeviceFromPath(const SafeString& path, BufferedSafeString* pathNoDrive) const;
    FileDevice* findDevice(const SafeString& name) const;

    FileDevice* tryOpen(FileHandle* handle, const SafeString& path, FileDevice::FileOpenFlag flag,
                        u32 divSize);
    FileDevice* tryOpenDirectory(DirectoryHandle* handle, const SafeString& path);

    u8* tryLoad(FileDevice::LoadArg& arg);
    void unload(u8* data);
    bool trySave(FileDevice::SaveArg& arg);

    void mountSaveDataForDebug(Heap* heap);
    void unmountSaveDataForDebug();

    FileDevice* getMainFileDevice() const { return mMainFileDevice; }
    FileDevice* getDefaultFileDevice() const { return mDefaultFileDevice; }
    void setDefaultFileDevice(FileDevice* device) { mDefaultFileDevice = device; }

#ifdef NNSDK
    bool hasMountedHost() const { return mMountedHost; }
    bool hasMountedSd() const { return mMountedSd; }
#endif

private:
    typedef TList<FileDevice*> DeviceList;

    void mount_(Heap* heap);
    void unmount_();

    DeviceList mDeviceList{};
    FileDevice* mDefaultFileDevice = nullptr;
    MainFileDevice* mMainFileDevice = nullptr;

#ifdef cafe
    static void stateChangeCallback_(FSClient* client, FSVolumeState state, void* context);

    FSClient client;
    u8 _1724[128];
    u8 _17A4[128];
    u32 _1824;
#elif defined(NNSDK)
    u8* mRomCache = nullptr;
    bool mMountedHost = false;
    bool mMountedSd = false;
#endif
};

}  // namespace sead

#endif  // SEAD_FILEDEVICEMGR_H_
