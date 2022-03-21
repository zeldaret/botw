#ifndef SEAD_CAFE_FSA_FILEDEVICE_H_
#define SEAD_CAFE_FSA_FILEDEVICE_H_

#include <cafe.h>

#include <basis/seadTypes.h>
#include <filedevice/seadFileDevice.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>

namespace sead
{
class CafeFSAFileDevice : public FileDevice
{
    SEAD_RTTI_OVERRIDE(CafeFSAFileDevice, FileDevice)

public:
    CafeFSAFileDevice(const SafeString& name, const SafeString& devicePath);
    virtual ~CafeFSAFileDevice() {}

    virtual bool doIsAvailable_() const;
    virtual FileDevice* doOpen_(FileHandle* handle, const SafeString& path, FileOpenFlag flag);
    virtual bool doClose_(FileHandle* handle);
    virtual bool doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead);
    virtual bool doWrite_(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                          u32 bytesToWrite);
    virtual bool doSeek_(FileHandle* handle, s32 offset, SeekOrigin origin);
    virtual bool doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle);
    virtual bool doGetFileSize_(u32* fileSize, const SafeString& path);
    virtual bool doGetFileSize_(u32* fileSize, FileHandle* handle);
    virtual bool doIsExistFile_(bool* exists, const SafeString& path);
    virtual bool doIsExistDirectory_(bool* exists, const SafeString& path);
    virtual FileDevice* doOpenDirectory_(DirectoryHandle* handle, const SafeString& path);
    virtual bool doCloseDirectory_(DirectoryHandle* handle);
    virtual bool doReadDirectory_(u32* entriesRead, DirectoryHandle* handle,
                                  DirectoryEntry* entries, u32 entriesToRead);
    virtual bool doMakeDirectory_(const SafeString& path, u32);
    virtual s32 doGetLastRawError_() const;
    virtual void doResolvePath_(BufferedSafeString* out, const SafeString& path) const;
    virtual void formatPathForFSA_(BufferedSafeString* out, const SafeString& path) const;

    FSClient* getUsableFSClient_() const;
    FSFileHandle* getFileHandleInner_(FileHandle* handle);
    FSDirHandle* getDirHandleInner_(DirectoryHandle* handle);

    const char* devicePath;
    FSStatus status;
    FSRetFlag openErrHandling;
    FSRetFlag closeErrHandling;
    FSRetFlag readErrHandling;
    FSClient* client;
};

class CafeContentFileDevice : public CafeFSAFileDevice
{
    SEAD_RTTI_OVERRIDE(CafeContentFileDevice, CafeFSAFileDevice)

public:
    CafeContentFileDevice();
    virtual ~CafeContentFileDevice() {}
};

}  // namespace sead

#endif  // SEAD_CAFE_FSA_FILEDEVICE_H_
