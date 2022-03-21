#ifndef SEAD_MAIN_FILEDEVICE_H_
#define SEAD_MAIN_FILEDEVICE_H_

#include <basis/seadTypes.h>
#include <filedevice/seadFileDevice.h>
#include <prim/seadRuntimeTypeInfo.h>
#include <prim/seadSafeString.h>

namespace sead
{
class MainFileDevice : public FileDevice
{
    SEAD_RTTI_OVERRIDE(MainFileDevice, FileDevice)

public:
    explicit MainFileDevice(Heap* heap);
    ~MainFileDevice() override;

    void traceFilePath(const SafeString& path) const override;
    void traceDirectoryPath(const SafeString& path) const override;
    void resolveFilePath(BufferedSafeString* out, const SafeString& path) const override;
    void resolveDirectoryPath(BufferedSafeString* out, const SafeString& path) const override;

protected:
    bool doIsAvailable_() const override { return mFileDevice->isAvailable(); }

    FileDevice* doOpen_(FileHandle* handle, const SafeString& path, FileOpenFlag flag) override
    {
        return mFileDevice->tryOpen(handle, path, flag, handle->getDivSize());
    }

    bool doClose_(FileHandle* handle) override { return mFileDevice->tryClose(handle); }

    bool doFlush_(FileHandle* handle) override { return mFileDevice->tryFlush(handle); }

    bool doRemove_(const SafeString& str) override { return mFileDevice->tryRemove(str); }

    bool doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead) override
    {
        return mFileDevice->tryRead(bytesRead, handle, outBuffer, bytesToRead);
    }

    bool doWrite_(u32* bytesWritten, FileHandle* handle, const u8* inBuffer,
                  u32 bytesToWrite) override
    {
        return mFileDevice->tryWrite(bytesWritten, handle, inBuffer, bytesToWrite);
    }

    bool doSeek_(FileHandle* handle, s32 offset, SeekOrigin origin) override
    {
        return mFileDevice->trySeek(handle, offset, origin);
    }

    bool doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle) override
    {
        return mFileDevice->tryGetCurrentSeekPos(seekPos, handle);
    }

    bool doGetFileSize_(u32* fileSize, const SafeString& path) override
    {
        return mFileDevice->tryGetFileSize(fileSize, path);
    }

    bool doGetFileSize_(u32* fileSize, FileHandle* handle) override
    {
        return mFileDevice->tryGetFileSize(fileSize, handle);
    }

    bool doIsExistFile_(bool* exists, const SafeString& path) override
    {
        return mFileDevice->tryIsExistFile(exists, path);
    }

    bool doIsExistDirectory_(bool* exists, const SafeString& path) override
    {
        return mFileDevice->tryIsExistDirectory(exists, path);
    }

    FileDevice* doOpenDirectory_(DirectoryHandle* handle, const SafeString& path) override
    {
        return mFileDevice->tryOpenDirectory(handle, path);
    }

    bool doCloseDirectory_(DirectoryHandle* handle) override
    {
        return mFileDevice->tryCloseDirectory(handle);
    }

    bool doReadDirectory_(u32* entriesRead, DirectoryHandle* handle, DirectoryEntry* entries,
                          u32 entriesToRead) override
    {
        return mFileDevice->tryReadDirectory(entriesRead, handle, entries, entriesToRead);
    }

    bool doMakeDirectory_(const SafeString& path, u32 x) override
    {
        return mFileDevice->tryMakeDirectory(path, x);
    }

    s32 doGetLastRawError_() const override { return mFileDevice->getLastRawError(); }

    bool isMatchDevice_(const HandleBase* handle) const override
    {
        return mFileDevice->isMatchDevice_(handle);
    }

    FileDevice* mFileDevice;
};

}  // namespace sead

#endif  // SEAD_MAIN_FILEDEVICE_H_
