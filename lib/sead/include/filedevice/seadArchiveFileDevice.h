#pragma once

#include "filedevice/seadFileDevice.h"

namespace sead
{
class ArchiveRes;

class ArchiveFileDevice : public FileDevice
{
    SEAD_RTTI_OVERRIDE(ArchiveFileDevice, FileDevice)
public:
    explicit ArchiveFileDevice(ArchiveRes* archive_res);
    ~ArchiveFileDevice() override = default;

    u8* tryLoadWithEntryID(s32 id, LoadArg& arg);
    FileDevice* tryOpenWithEntryID(FileHandle* handle, s32 id, FileOpenFlag flag, u32 div_size);
    s32 tryConvertPathToEntryID(const SafeString& path);
    bool setCurrentDirectory(const SafeString& dir);

protected:
    struct ArchiveFileHandle;

    bool doIsAvailable_() const override { return true; }
    u8* doLoad_(LoadArg& arg) override;
    FileDevice* doOpen_(FileHandle* handle, const SafeString& path, FileOpenFlag flag) override;
    bool doClose_(FileHandle* handle) override;
    bool doFlush_(FileHandle* handle) override;
    bool doRemove_(const SafeString& str) override;
    bool doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead) override;
    bool doWrite_(u32*, FileHandle*, const u8*, u32) override { return false; }
    bool doSeek_(FileHandle* handle, s32 offset, SeekOrigin origin) override;
    bool doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle) override;
    bool doGetFileSize_(u32* fileSize, const SafeString& path) override;
    bool doGetFileSize_(u32* fileSize, FileHandle* handle) override;
    bool doIsExistFile_(bool* exists, const SafeString& path) override;
    bool doIsExistDirectory_(bool* exists, const SafeString& path) override;
    FileDevice* doOpenDirectory_(DirectoryHandle* handle, const SafeString& path) override;
    bool doCloseDirectory_(DirectoryHandle* handle) override;
    bool doReadDirectory_(u32* entriesRead, DirectoryHandle* handle, DirectoryEntry* entry,
                          u32 entriesToRead) override;
    bool doMakeDirectory_(const SafeString& path, u32 u_32) override;
    s32 doGetLastRawError_() const override;

    virtual u8* doLoadWithEntryID_(s32 id, LoadArg& arg);
    virtual FileDevice* doOpenWithEntryID_(FileHandle* handle, s32 id, FileOpenFlag flag);
    virtual s32 doConvertPathToEntryID_(const SafeString& path);
    virtual bool doSetCurrentDirectory_(const SafeString& path);

    ArchiveFileHandle* getArchiveFileHandle_(FileHandle* handle) const;
    ArchiveFileHandle* constructArchiveFileHandle_(FileHandle* handle) const;

    ArchiveRes* mArchive;
};
}  // namespace sead
