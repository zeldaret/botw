#ifndef SEAD_ARCHIVE_RES_H_
#define SEAD_ARCHIVE_RES_H_

#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <filedevice/seadFileDevice.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>

namespace sead
{
class ArchiveRes : public DirectResource
{
    SEAD_RTTI_OVERRIDE(ArchiveRes, DirectResource)

public:
    struct FileInfo
    {
        u32 mStartOffset;
        u32 mLength;
    };

public:
    ArchiveRes() : DirectResource(), mEnable(false) {}
    ~ArchiveRes() override = default;

    s32 getLoadDataAlignment() const override;
    void doCreate_(u8* buf, u32, Heap*) override;

    const void* getFile(const SafeString& file_path, FileInfo* info = nullptr) const
    {
        SEAD_ASSERT(mEnable);
        return getFileImpl_(file_path, info);
    }

    const void* getFileFast(const s32 entry_id, FileInfo* info) const
    {
        SEAD_ASSERT(mEnable);
        return getFileFastImpl_(entry_id, info);
    }

    s32 convertPathToEntryID(const SafeString& path) const
    {
        SEAD_ASSERT(mEnable);
        return convertPathToEntryIDImpl_(path);
    }

    bool setCurrentDirectory(const SafeString& dir)
    {
        SEAD_ASSERT(mEnable);
        return setCurrentDirectoryImpl_(dir);
    }

    bool openDirectory(HandleBuffer* handle, const SafeString& dir) const
    {
        return openDirectoryImpl_(handle, dir);
    }

    bool closeDirectory(HandleBuffer* handle) const { return closeDirectoryImpl_(handle); }

    u32 readDirectory(HandleBuffer* handle, DirectoryEntry* entries, u32 num) const
    {
        return readDirectoryImpl_(handle, entries, num);
    }

    bool isExistFile(const SafeString& path) const { return isExistFileImpl_(path); }

protected:
    virtual const void* getFileImpl_(const SafeString& file_path,
                                     FileInfo* file_info = nullptr) const = 0;
    virtual const void* getFileFastImpl_(s32 entry_id, FileInfo* file_info) const = 0;
    virtual s32 convertPathToEntryIDImpl_(const SafeString& file_path) const = 0;
    virtual bool setCurrentDirectoryImpl_(const SafeString&) = 0;
    virtual bool openDirectoryImpl_(HandleBuffer* handle, const SafeString& path) const = 0;
    virtual bool closeDirectoryImpl_(HandleBuffer* handle) const = 0;
    virtual u32 readDirectoryImpl_(HandleBuffer* handle, DirectoryEntry* entries,
                                   u32 num) const = 0;
    virtual bool isExistFileImpl_(const SafeString& path) const;
    virtual bool prepareArchive_(const void* archive) = 0;

    bool mEnable;
};

}  // namespace sead

#endif  // SEAD_ARCHIVE_RES_H_
