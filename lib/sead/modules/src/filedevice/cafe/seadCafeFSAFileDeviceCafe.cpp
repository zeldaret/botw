#include <cafe.h>

#include <filedevice/cafe/seadCafeFSAFileDeviceCafe.h>
#include <filedevice/seadFileDevice.h>
#include <filedevice/seadFileDeviceMgr.h>
#include <prim/seadSafeString.h>

namespace sead
{
CafeFSAFileDevice::CafeFSAFileDevice(const SafeString& name, const SafeString& devicePath)
    : FileDevice(name), devicePath(devicePath.cstr()), status(FS_STATUS_OK),
      openErrHandling(FS_RET_PERMISSION_ERROR | FS_RET_ACCESS_ERROR | FS_RET_NOT_FILE |
                      FS_RET_NOT_FOUND | FS_RET_ALREADY_OPEN),
      closeErrHandling(FS_RET_NO_ERROR), readErrHandling(FS_RET_NO_ERROR), client(NULL)
{
}

bool CafeFSAFileDevice::doIsAvailable_() const
{
    return true;
}

FileDevice* CafeFSAFileDevice::doOpen_(FileHandle* handle, const SafeString& path,
                                       FileDevice::FileOpenFlag flag)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);

    char* mode;
    switch (flag)
    {
    case FileDevice::cFileOpenFlag_ReadOnly:
        mode = "r";
        break;
    case FileDevice::cFileOpenFlag_WriteOnly:
        mode = "w";
        break;
    case FileDevice::cFileOpenFlag_ReadWrite:
        mode = "r+";
        break;
    case FileDevice::cFileOpenFlag_Create:
        mode = "w+";
        break;
    default:
        mode = "r";
    }

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    FSStatus status = FSOpenFile(client_, &block, fullPath.cstr(), mode, fsHandle, openErrHandling);
    fsHandle[1] = 0;

    if (this->status = status, status != FS_STATUS_OK)
    {
        fsHandle[0] = 0;
        return NULL;
    }

    return this;
}

bool CafeFSAFileDevice::doClose_(FileHandle* handle)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);

    return FSCloseFile(client_, &block, *fsHandle, closeErrHandling) == FS_STATUS_OK;
}

bool CafeFSAFileDevice::doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);

    s32 status = FSReadFile(client_, &block, outBuffer, sizeof(u8), bytesToRead, *fsHandle, 0,
                            readErrHandling);
    if (status >= 0)
    {
        this->status = FS_STATUS_OK;
        fsHandle[1] += status;

        if (bytesRead != NULL)
            *bytesRead = status;

        return true;
    }

    this->status = status;
    return false;
}

bool CafeFSAFileDevice::doWrite_(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                                 u32 bytesToWrite)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);

    s32 status = FSWriteFile(client_, &block, inBuffer, sizeof(const u8), bytesToWrite, *fsHandle,
                             0, FS_RET_STORAGE_FULL | FS_RET_FILE_TOO_BIG);
    if (status >= 0)
    {
        this->status = FS_STATUS_OK;
        fsHandle[1] += status;

        if (bytesWritten != NULL)
            *bytesWritten = status;

        return true;
    }

    this->status = status;
    return false;
}

bool CafeFSAFileDevice::doSeek_(FileHandle* handle, s32 offset, FileDevice::SeekOrigin origin)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);

    if (origin != FileDevice::cSeekOrigin_Begin)
    {
        if (origin == FileDevice::cSeekOrigin_Current)
            offset += fsHandle[1];

        else if (origin != FileDevice::cSeekOrigin_End)
            return false;

        else
        {
            u32 fileSize = 0;
            if (!doGetFileSize_(&fileSize, handle))
                return false;

            offset += fileSize;
        }
    }

    FSStatus status = FSSetPosFile(client_, &block, *fsHandle, offset, FS_RET_NO_ERROR);
    if (this->status = status, status != FS_STATUS_OK)
        return false;

    fsHandle[1] = offset;
    return true;
}

bool CafeFSAFileDevice::doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle)
{
    *seekPos = getFileHandleInner_(handle)[1];
    return true;
}

bool CafeFSAFileDevice::doGetFileSize_(u32* fileSize, const SafeString& path)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSStat stat;

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    FSStatus status = FSGetStat(client_, &block, fullPath.cstr(), &stat, FS_RET_NO_ERROR);
    if (this->status = status, status != FS_STATUS_OK)
        return false;

    *fileSize = stat.size;
    return true;
}

bool CafeFSAFileDevice::doGetFileSize_(u32* fileSize, FileHandle* handle)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSFileHandle* fsHandle = getFileHandleInner_(handle);
    FSStat stat;

    FSStatus status = FSGetStatFile(client_, &block, *fsHandle, &stat, FS_RET_NO_ERROR);
    if (this->status = status, status != FS_STATUS_OK)
        return false;

    *fileSize = stat.size;
    return true;
}

bool CafeFSAFileDevice::doIsExistFile_(bool* exists, const SafeString& path)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSStat stat;

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    FSStatus status = FSGetStat(client_, &block, fullPath.cstr(), &stat,
                                FS_RET_PERMISSION_ERROR | FS_RET_NOT_FOUND);
    if (this->status = status, status != FS_STATUS_OK)
    {
        if (status != FS_STATUS_NOT_FOUND)
            return false;

        *exists = false;
    }

    else
        *exists = (stat.flag & (FS_STAT_FLAG_IS_DIRECTORY | FS_STAT_FLAG_IS_QUOTA)) != 0;

    return true;
}

bool CafeFSAFileDevice::doIsExistDirectory_(bool* exists, const SafeString& path)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSStat stat;

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    FSStatus status = FSGetStat(client_, &block, fullPath.cstr(), &stat,
                                FS_RET_PERMISSION_ERROR | FS_RET_NOT_FOUND);
    if (this->status = status, status != FS_STATUS_OK)
    {
        if (status != FS_STATUS_NOT_FOUND)
            return false;

        *exists = false;
    }

    else
        *exists = (stat.flag & FS_STAT_FLAG_IS_DIRECTORY) != 0;

    return true;
}

FileDevice* CafeFSAFileDevice::doOpenDirectory_(DirectoryHandle* handle, const SafeString& path)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSDirHandle* fsHandle = getDirHandleInner_(handle);

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    FSStatus status = FSOpenDir(client_, &block, fullPath.cstr(), fsHandle,
                                FS_RET_PERMISSION_ERROR | FS_RET_ACCESS_ERROR | FS_RET_NOT_DIR |
                                    FS_RET_NOT_FOUND | FS_RET_ALREADY_OPEN);

    if (this->status = status, status != FS_STATUS_OK)
        return NULL;

    return this;
}

bool CafeFSAFileDevice::doCloseDirectory_(DirectoryHandle* handle)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSDirHandle* fsHandle = getDirHandleInner_(handle);

    return (status = FSCloseDir(client_, &block, *fsHandle, FS_RET_NO_ERROR),
            status == FS_STATUS_OK);
}

bool CafeFSAFileDevice::doReadDirectory_(u32* entriesRead, DirectoryHandle* handle,
                                         DirectoryEntry* entries, u32 entriesToRead)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();
    FSDirHandle* fsHandle = getDirHandleInner_(handle);

    for (s32 i = 0; i < entriesToRead; i++)
    {
        FSDirEntry dirEntry;

        status = FSReadDir(client_, &block, *fsHandle, &dirEntry, FS_RET_NO_ERROR);
        if (status != FS_STATUS_OK)
        {
            if (entriesRead != NULL)
                *entriesRead = i;

            if (status == FS_STATUS_END)
                return true;

            return false;
        }

        SafeString name(dirEntry.name);

        entries[i].name.copy(name);
        entries[i].is_directory = (dirEntry.stat.flag & FS_STAT_FLAG_IS_DIRECTORY) != 0;
    }

    if (entriesRead != NULL)
        *entriesRead = entriesToRead;

    return true;
}

bool CafeFSAFileDevice::doMakeDirectory_(const SafeString& path, u32)
{
    FSCmdBlock block;
    FSInitCmdBlock(&block);

    FSClient* client_ = getUsableFSClient_();

    FixedSafeString<FS_MAX_ENTNAME_SIZE> fullPath;
    formatPathForFSA_(&fullPath, path);

    return (status = FSMakeDir(client_, &block, fullPath.cstr(),
                               FS_RET_JOURNAL_FULL | FS_RET_STORAGE_FULL | FS_RET_PERMISSION_ERROR |
                                   FS_RET_NOT_FOUND),
            status == FS_STATUS_OK);
}

s32 CafeFSAFileDevice::doGetLastRawError_() const
{
    return status;
}

void CafeFSAFileDevice::doResolvePath_(BufferedSafeString* out, const SafeString& path) const
{
    formatPathForFSA_(out, path);
}

void CafeFSAFileDevice::formatPathForFSA_(BufferedSafeString* out, const SafeString& path) const
{
    out->format("%s/%s", devicePath, path.cstr());
}

FSClient* CafeFSAFileDevice::getUsableFSClient_() const
{
    if (client == NULL)
        return &FileDeviceMgr::instance()->client;

    return client;
}
FSFileHandle* CafeFSAFileDevice::getFileHandleInner_(FileHandle* handle)
{
    return reinterpret_cast<FSFileHandle*>(getHandleBaseHandleBuffer_(handle));
}
FSDirHandle* CafeFSAFileDevice::getDirHandleInner_(DirectoryHandle* handle)
{
    return reinterpret_cast<FSDirHandle*>(getHandleBaseHandleBuffer_(handle));
}

CafeContentFileDevice::CafeContentFileDevice() : CafeFSAFileDevice("content", FS_CONTENT_DIR) {}

}  // namespace sead
