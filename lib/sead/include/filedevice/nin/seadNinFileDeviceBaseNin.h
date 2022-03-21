#pragma once

#include <nn/fs.h>
#include "filedevice/seadFileDevice.h"
#include "prim/seadSafeString.h"

namespace sead
{
class NinFileDeviceBase : public FileDevice
{
    SEAD_RTTI_OVERRIDE(NinFileDeviceBase, FileDevice)

public:
    NinFileDeviceBase(const SafeString& name, const SafeString& mount_point);

protected:
    struct FileHandleInner;
    struct DirectoryHandleInner;

    bool doIsAvailable_() const override;
    FileDevice* doOpen_(FileHandle* handle, const SafeString& path, FileOpenFlag flag) override;
    bool doClose_(FileHandle* handle) override;
    bool doFlush_(FileHandle* handle) override;
    bool doRemove_(const SafeString& path) override;
    bool doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead) override;
    bool doWrite_(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                  u32 bytesToWrite) override;
    bool doSeek_(FileHandle* handle, s32 offset, SeekOrigin origin) override;
    bool doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle) override;
    bool doGetFileSize_(u32* fileSize, const SafeString& path) override;
    bool doGetFileSize_(u32* fileSize, FileHandle* handle) override;
    bool doIsExistFile_(bool* exists, const SafeString& path) override;
    bool doIsExistDirectory_(bool* exists, const SafeString& path) override;
    FileDevice* doOpenDirectory_(DirectoryHandle* handle, const SafeString& path) override;
    bool doCloseDirectory_(DirectoryHandle* handle) override;
    bool doReadDirectory_(u32* entriesRead, DirectoryHandle* handle, DirectoryEntry* entries,
                          u32 entriesToRead) override;
    bool doMakeDirectory_(const SafeString& path, u32 u_32) override;
    s32 doGetLastRawError_() const override;
    void doResolvePath_(BufferedSafeString* out, const SafeString& path) const override;

    virtual bool formatPathForFS_(BufferedSafeString* out, const SafeString& path) const;

    FileHandleInner* getFileHandleInner_(HandleBase* handle, bool construct = false) const;
    DirectoryHandleInner* getDirectoryHandleInner_(HandleBase* handle,
                                                   bool construct = false) const;

    nn::Result mLastError = nn::ResultSuccess{};
    SafeString mMountPoint;
};
}  // namespace sead
