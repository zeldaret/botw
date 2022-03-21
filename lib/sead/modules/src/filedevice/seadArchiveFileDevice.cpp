#include "filedevice/seadArchiveFileDevice.h"
#include "basis/seadRawPrint.h"
#include "math/seadMathCalcCommon.h"
#include "prim/seadPtrUtil.h"
#include "resource/seadArchiveRes.h"

namespace sead
{
struct ArchiveFileDevice::ArchiveFileHandle
{
    const u8* mFileData;
    ArchiveRes::FileInfo mFileInfo;
    u32 mPos;
};

ArchiveFileDevice::ArchiveFileDevice(ArchiveRes* res) : FileDevice("arc"), mArchive(res) {}

u8* ArchiveFileDevice::tryLoadWithEntryID(s32 id, FileDevice::LoadArg& arg)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return nullptr;

    return doLoadWithEntryID_(id, arg);
}

FileDevice* ArchiveFileDevice::tryOpenWithEntryID(FileHandle* handle, s32 id,
                                                  FileDevice::FileOpenFlag flag, u32 div_size)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return nullptr;

    setFileHandleDivSize_(handle, div_size);
    FileDevice* ret = doOpenWithEntryID_(handle, id, flag);
    setHandleBaseFileDevice_(handle, ret);
    return ret;
}

s32 ArchiveFileDevice::tryConvertPathToEntryID(const SafeString& path)
{
    return doConvertPathToEntryID_(path);
}

bool ArchiveFileDevice::setCurrentDirectory(const SafeString& dir)
{
    SEAD_ASSERT_MSG(mPermission, "Device permission error.");
    if (!mPermission)
        return false;

    return doSetCurrentDirectory_(dir);
}

bool ArchiveFileDevice::doGetFileSize_(u32* fileSize, const SafeString& path)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    if (!path.cstr())
    {
        SEAD_ASSERT_MSG(false, "invalid path");
        return false;
    }

    ArchiveRes::FileInfo info{};
    if (!mArchive->getFile(path, &info))
        return false;

    *fileSize = info.mLength;
    return true;
}

bool ArchiveFileDevice::doGetFileSize_(u32* fileSize, FileHandle* handle)
{
    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "invalid handle");
        return false;
    }

    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    *fileSize = getArchiveFileHandle_(handle)->mFileInfo.mLength;
    return true;
}

ArchiveFileDevice::ArchiveFileHandle*
ArchiveFileDevice::getArchiveFileHandle_(FileHandle* handle) const
{
    return reinterpret_cast<ArchiveFileHandle*>(getHandleBaseHandleBuffer_(handle).getBufferPtr());
}

ArchiveFileDevice::ArchiveFileHandle*
ArchiveFileDevice::constructArchiveFileHandle_(FileHandle* handle) const
{
    return new (getHandleBaseHandleBuffer_(handle).getBufferPtr()) ArchiveFileHandle;
}

bool ArchiveFileDevice::doIsExistFile_(bool* exists, const SafeString& path)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    if (!path.cstr())
    {
        SEAD_ASSERT_MSG(false, "invalid path");
        return false;
    }

    *exists = mArchive->isExistFile(path);
    return true;
}

bool ArchiveFileDevice::doIsExistDirectory_(bool* exists, const SafeString& path)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    if (!path.cstr())
    {
        SEAD_ASSERT_MSG(false, "invalid path");
        return false;
    }

    *exists = false;
    return true;
}

u8* ArchiveFileDevice::doLoadWithEntryID_(s32 entry_id, LoadArg& arg)
{
    if (entry_id == -1)
    {
        SEAD_ASSERT_MSG(false, "Invalid entry_id");
        return nullptr;
    }

    if (arg.buffer_size_alignment % 32 != 0)
    {
        SEAD_ASSERT_MSG(false, "arg.buffer_size_alignment[%u] is not multipe of 32",
                        arg.buffer_size_alignment);
        return nullptr;
    }

    if (arg.buffer || arg.heap)
    {
        FileHandle handle;
        if (!tryOpenWithEntryID(&handle, entry_id, {}, arg.div_size))
            return nullptr;

        // Determine the buffer size.
        u32 buffer_size = arg.buffer_size;
        if (buffer_size == 0)
        {
            u32 file_size = 0;
            if (!tryGetFileSize(&file_size, &handle))
                return nullptr;

            SEAD_ASSERT(file_size != 0);

            if (arg.buffer_size_alignment)
                buffer_size = Mathu::roundUp(file_size, arg.buffer_size_alignment);
            else
                buffer_size = Mathi::roundUpPow2(file_size, cBufferMinAlignment);
        }

        // Allocate the buffer if need be.
        u8* buffer = arg.buffer;
        bool buffer_allocated = false;
        if (!buffer)
        {
            const s32 aligment_sign = Mathi::sign(arg.alignment);
            const s32 alignment = std::max(Mathi::abs(arg.alignment), 32);
            buffer = new (arg.heap, alignment * aligment_sign) u8[buffer_size];
            buffer_allocated = true;
        }

        u32 bytes_read = 0;
        if (!tryRead(&bytes_read, &handle, buffer, buffer_size) || !tryClose(&handle))
        {
            // Clean up the allocation on failure.
            if (buffer && buffer_allocated)
                delete[] buffer;
            return nullptr;
        }

        arg.read_size = bytes_read;
        arg.need_unload = buffer_allocated;
        arg.roundup_size = buffer_size;
        return buffer;
    }

    ArchiveRes::FileInfo info{};
    auto* ret = mArchive->getFileFast(entry_id, &info);
    if (!ret)
        return nullptr;

    SEAD_ASSERT(arg.alignment == 0 || PtrUtil::isAligned(ret, Mathi::abs(arg.alignment)));
    if (arg.buffer_size_alignment && info.mLength % arg.buffer_size_alignment != 0)
    {
        SEAD_WARN("archive file size[%u] is not multipe of arg.buffer_size_alignment[%u]",
                  info.mLength, arg.buffer_size_alignment);
        return nullptr;
    }

    arg.read_size = info.mLength;
    arg.roundup_size = info.mLength;
    arg.need_unload = false;
    return const_cast<u8*>(static_cast<const u8*>(ret));
}

u8* ArchiveFileDevice::doLoad_(LoadArg& arg)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return nullptr;
    }

    if (arg.buffer || arg.heap)
        return FileDevice::doLoad_(arg);

    ArchiveRes::FileInfo info{};
    auto* ret = mArchive->getFile(arg.path, &info);
    if (!ret)
        return nullptr;

    SEAD_ASSERT(arg.alignment == 0 || PtrUtil::isAligned(ret, Mathi::abs(arg.alignment)));
    if (arg.buffer_size_alignment && info.mLength % arg.buffer_size_alignment != 0)
    {
        SEAD_WARN("archive file size[%u] is not multipe of arg.buffer_size_alignment[%u]",
                  info.mLength, arg.buffer_size_alignment);
        return nullptr;
    }

    arg.read_size = info.mLength;
    arg.roundup_size = info.mLength;
    arg.need_unload = false;
    return const_cast<u8*>(static_cast<const u8*>(ret));
}

FileDevice* ArchiveFileDevice::doOpen_(FileHandle* handle, const SafeString& path,
                                       FileDevice::FileOpenFlag)
{
    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "invalid handle");
        return nullptr;
    }

    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return nullptr;
    }

    if (!path.cstr())
    {
        SEAD_ASSERT_MSG(false, "invalid filename");
        return nullptr;
    }

    auto* inner = constructArchiveFileHandle_(handle);

    auto* file_data = static_cast<const u8*>(mArchive->getFile(path, &inner->mFileInfo));
    if (!file_data)
        return nullptr;

    inner->mFileData = file_data;
    inner->mPos = 0;
    return this;
}

FileDevice* ArchiveFileDevice::doOpenWithEntryID_(FileHandle* handle, s32 id,
                                                  FileDevice::FileOpenFlag)
{
    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "invalid handle");
        return nullptr;
    }

    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return nullptr;
    }

    auto* inner = constructArchiveFileHandle_(handle);

    auto* file_data = static_cast<const u8*>(mArchive->getFileFast(id, &inner->mFileInfo));
    if (!file_data)
        return nullptr;

    inner->mFileData = file_data;
    inner->mPos = 0;
    return this;
}

s32 ArchiveFileDevice::doConvertPathToEntryID_(const SafeString& path)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return 0;
    }
    return mArchive->convertPathToEntryID(path);
}

bool ArchiveFileDevice::doClose_(FileHandle*)
{
    return true;
}

bool ArchiveFileDevice::doFlush_(FileHandle*)
{
    SEAD_ASSERT_MSG(false, "not supported");
    return false;
}

bool ArchiveFileDevice::doRemove_(const SafeString&)
{
    SEAD_ASSERT_MSG(false, "not supported");
    return false;
}

bool ArchiveFileDevice::doRead_(u32* bytesRead, FileHandle* handle, u8* outBuffer, u32 bytesToRead)
{
    ArchiveFileHandle* inner = getArchiveFileHandle_(handle);

    u32 read_size;
    if (inner->mPos + bytesToRead <= inner->mFileInfo.mLength)
        read_size = bytesToRead;
    else
        read_size = inner->mFileInfo.mLength - inner->mPos;

    MemUtil::copy(outBuffer, inner->mFileData + inner->mPos, read_size);

    inner->mPos += read_size;
    if (bytesRead)
        *bytesRead = read_size;

    return true;
}

bool ArchiveFileDevice::doSeek_(FileHandle* handle, s32 offset, FileDevice::SeekOrigin origin)
{
    ArchiveFileHandle* inner = getArchiveFileHandle_(handle);
    u32 new_position;
    switch (origin)
    {
    case cSeekOrigin_Begin:
        new_position = offset;
        break;
    case cSeekOrigin_Current:
        new_position = inner->mPos + offset;
        break;
    case cSeekOrigin_End:
        new_position = inner->mFileInfo.mLength + offset;
        break;
    default:
        SEAD_ASSERT_MSG(false, "Unexpected origin");
        return false;
    }

    if (new_position > inner->mFileInfo.mLength)
        return false;

    inner->mPos = new_position;
    return true;
}

bool ArchiveFileDevice::doGetCurrentSeekPos_(u32* seekPos, FileHandle* handle)
{
    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "invalid handle");
        return false;
    }

    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    ArchiveFileHandle* inner = getArchiveFileHandle_(handle);
    *seekPos = inner->mPos;
    return true;
}

FileDevice* ArchiveFileDevice::doOpenDirectory_(DirectoryHandle* handle, const SafeString& path)
{
    if (!handle)
    {
        SEAD_ASSERT_MSG(false, "invalid handle");
        return nullptr;
    }

    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return nullptr;
    }

    if (!mArchive->openDirectory(&getHandleBaseHandleBuffer_(handle), path))
        return nullptr;

    return this;
}

bool ArchiveFileDevice::doCloseDirectory_(DirectoryHandle* handle)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }
    return mArchive->closeDirectory(&getHandleBaseHandleBuffer_(handle));
}

bool ArchiveFileDevice::doReadDirectory_(u32* entriesRead, DirectoryHandle* handle,
                                         DirectoryEntry* entry, u32 entriesToRead)
{
    auto* archive = mArchive;
    if (!archive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    auto* buffer = &getHandleBaseHandleBuffer_(handle);
    SEAD_ASSERT(entry);
    const u32 actual_read_count = archive->readDirectory(buffer, entry, entriesToRead);
    if (entriesRead)
        *entriesRead = actual_read_count;

    return true;
}

bool ArchiveFileDevice::doSetCurrentDirectory_(const SafeString& path)
{
    if (!mArchive)
    {
        SEAD_ASSERT_MSG(false, "no archive mounted");
        return false;
    }

    if (!path.cstr())
    {
        SEAD_ASSERT_MSG(false, "invalid filename");
        return false;
    }

    return mArchive->setCurrentDirectory(path);
}

bool ArchiveFileDevice::doMakeDirectory_(const SafeString&, u32)
{
    return false;
}

s32 ArchiveFileDevice::doGetLastRawError_() const
{
    SEAD_ASSERT_MSG(false, "not impremented");
    return 0;
}
}  // namespace sead
