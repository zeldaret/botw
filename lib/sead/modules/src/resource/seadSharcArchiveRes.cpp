#include <container/seadBuffer.h>
#include <prim/seadPtrUtil.h>
#include <prim/seadSafeString.h>
#include <resource/seadSharcArchiveRes.h>

namespace
{
u32 calcHash32(const sead::SafeString& str, u32 key)
{
    const char* str_ = str.cstr();

    u32 result = 0;
    // Each character must be treated as a signed value.
    // The cast to s8 (not s32) is necessary to avoid unsigned conversions.
    for (s32 i = 0; str_[i] != '\0'; i++)
        result = result * key + s8(str_[i]);

    return result;
}

#ifdef NNSDK
s32 binarySearch_(u32 hash, const sead::SharcArchiveRes::FATEntry* buffer, s32 start, s32 end,
                  sead::Endian::Types endian)
#else
s32 binarySearch_(u32 hash, const sead::SharcArchiveRes::FATEntry* buffer, s32 start, s32 end)
#endif
{
    s32 middle;

    for (;;)
    {
        middle = (start + end) / 2;

#ifdef NNSDK
        u32 entryHash = sead::Endian::toHostU32(endian, buffer[middle].hash);
#else
        u32 entryHash = buffer[middle].hash;
#endif
        if (entryHash == hash)
            return middle;

        else if (entryHash < hash)
        {
            if (start == middle)
                return -1;

            start = middle;
        }

        else
        {
            if (end == middle)
                return -1;

            end = middle;
        }
    }
}

}  // namespace

namespace sead
{
struct SharcArchiveRes::HandleInner
{
    u32 x;
};

SharcArchiveRes::SharcArchiveRes()
    : ArchiveRes(), mArchiveBlockHeader(NULL), mFATBlockHeader(NULL), mFNTBlock(NULL),
      mDataBlock(NULL)
#ifdef cafe
      ,
      mEndianType(Endian::cBig)
#else
      ,
      mEndianType(Endian::cLittle)
#endif
{
}

SharcArchiveRes::~SharcArchiveRes() {}

const void* SharcArchiveRes::getFileImpl_(const SafeString& file_path, FileInfo* file_info) const
{
    s32 id = convertPathToEntryIDImpl_(file_path);
    if (id < 0)
        return NULL;

    return getFileFastImpl_(id, file_info);
}

const void* SharcArchiveRes::getFileFastImpl_(s32 entry_id, FileInfo* file_info) const
{
    if (entry_id < 0 || entry_id >= mFATEntrys.size())
        return NULL;

    u32 start = Endian::toHostU32(mEndianType, mFATEntrys(entry_id).data_start_offset);

    if (file_info != NULL)
    {
        u32 end = Endian::toHostU32(mEndianType, mFATEntrys(entry_id).data_end_offset);
        if (start > end)
            return NULL;

        u32 length = end - start;

        file_info->mStartOffset = start;
        file_info->mLength = length;
    }

    return mDataBlock + start;
}

s32 SharcArchiveRes::convertPathToEntryIDImpl_(const SafeString& file_path) const
{
    u32 hash = calcHash32(file_path, Endian::toHostU32(mEndianType, mFATBlockHeader->hash_key));

    s32 start = 0;
    s32 end = mFATEntrys.size();

#ifdef NNSDK
    s32 id = binarySearch_(hash, mFATEntrys.getBufferPtr(), start, end, mEndianType);
#else
    s32 id = binarySearch_(hash, mFATEntrys.getBufferPtr(), start, end);
#endif
    if (id == -1)
        return -1;

    u32 offset = Endian::toHostU32(mEndianType, mFATEntrys(id).name_offset);
    if (offset != 0)
    {
        id -= (offset >> 24) - 1;

        while (id < end)
        {
            const FATEntry* entry = mFATEntrys.unsafeGet(id);
            if (Endian::toHostU32(mEndianType, entry->hash) != hash)
                return -1;

            else
            {
                u32 offset_ = Endian::toHostU32(mEndianType, entry->name_offset);

                if (PtrUtil::addOffset(mFNTBlock, offset_ & 0xffffff) > mDataBlock)
                {
                    SEAD_ASSERT_MSG(false, "Invalid data start offset");
                    return -1;
                }

                if (file_path.isEqual(mFNTBlock + (offset_ & 0xffffff) * cFileNameTableAlign))
                    return id;
            }

            id++;
        }
    }

    return id;
}

bool SharcArchiveRes::setCurrentDirectoryImpl_(const SafeString&)
{
    SEAD_ASSERT_MSG(false, "Not support.");
    return false;
}

bool SharcArchiveRes::openDirectoryImpl_(HandleBuffer* handle, const SafeString& path) const
{
    if (path.isEmpty() || path == "/")
    {
        getHandleInner_(handle)->x = 0;
        return true;
    }

    SEAD_WARN("dir_path[%s] is not allowed to open sharc directory. must be root.", path.cstr());
    return false;
}

bool SharcArchiveRes::closeDirectoryImpl_(HandleBuffer*) const
{
    return true;
}

u32 SharcArchiveRes::readDirectoryImpl_(HandleBuffer* handle_, DirectoryEntry* entry, u32 num) const
{
    auto* handle = getHandleInner_(handle_);
    u32 count = 0;

    while (handle->x + count < Endian::toHostU16(mEndianType, mFATBlockHeader->file_num) &&
           count < num)
    {
        u32 id = handle->x + count;
        SEAD_ASSERT(id >= handle->x);

        u32 offset = Endian::toHostU32(mEndianType, mFATEntrys(id).name_offset);
        if (offset == 0)
            entry[count].name.format("%08x", Endian::toHostU32(mEndianType, mFATEntrys(id).hash));
        else
        {
            if (reinterpret_cast<const u8*>(mFNTBlock + (offset & 0xffffff)) > mDataBlock)
            {
                SEAD_WARN("Invalid data start offset");
                entry[count].name.clear();
            }
            else
                entry[count].name.copy(mFNTBlock + (offset & 0xffffff) * cFileNameTableAlign);
        }

        entry[count].is_directory = false;
        count++;
    }

    handle->x += count;
    return count;
}

bool SharcArchiveRes::prepareArchive_(const void* archive)
{
    if (archive == nullptr)
    {
        SEAD_ASSERT_MSG(false, "archive must not be nullptr.");
        return false;
    }

    const u8* archive_ = reinterpret_cast<const u8*>(archive);

    mArchiveBlockHeader = reinterpret_cast<const ArchiveBlockHeader*>(archive_);
    if (std::memcmp(mArchiveBlockHeader->signature, "SARC", 4) != 0)
    {
        SEAD_ASSERT_MSG(false, "Invalid ArchiveBlockHeader");
        return false;
    }

    mEndianType = Endian::markToEndian(mArchiveBlockHeader->byte_order);

    if (Endian::toHostU16(mEndianType, mArchiveBlockHeader->version) != cArchiveVersion)
    {
        SEAD_ASSERT_MSG(false, "unmatching version ( expect: %x, actual: %x )", cArchiveVersion,
                        mArchiveBlockHeader->version);
        return false;
    }

    if (Endian::toHostU16(mEndianType, mArchiveBlockHeader->header_size) !=
        sizeof(ArchiveBlockHeader))
    {
        SEAD_ASSERT_MSG(false, "Invalid ArchiveBlockHeader");
        return false;
    }

    mFATBlockHeader = reinterpret_cast<const FATBlockHeader*>(
        archive_ + Endian::toHostU16(mEndianType, mArchiveBlockHeader->header_size));
    if (std::memcmp(mFATBlockHeader->signature, "SFAT", 4) != 0)
    {
        SEAD_ASSERT_MSG(false, "Invalid FATBlockHeader");
        return false;
    }

    if (Endian::toHostU16(mEndianType, mFATBlockHeader->header_size) != sizeof(FATBlockHeader))
    {
        SEAD_ASSERT_MSG(false, "Invalid FATBlockHeader");
        return false;
    }

    if (Endian::toHostU16(mEndianType, mFATBlockHeader->file_num) > cArchiveEntryMax)
    {
        SEAD_ASSERT_MSG(false, "Invalid FATBlockHeader");
        return false;
    }

    mFATEntrys.setBuffer(
        Endian::toHostU16(mEndianType, mFATBlockHeader->file_num),
        const_cast<FATEntry*>(reinterpret_cast<const FATEntry*>(
            archive_ + Endian::toHostU16(mEndianType, mArchiveBlockHeader->header_size) +
            Endian::toHostU16(mEndianType, mFATBlockHeader->header_size))));

    auto* fnt_header = reinterpret_cast<const FNTBlockHeader*>(
        archive_ + Endian::toHostU16(mEndianType, mArchiveBlockHeader->header_size) +
        Endian::toHostU16(mEndianType, mFATBlockHeader->header_size) +
        Endian::toHostU16(mEndianType, mFATBlockHeader->file_num) * sizeof(FATEntry));
    if (std::memcmp(fnt_header->signature, "SFNT", 4) != 0)
    {
        SEAD_ASSERT_MSG(false, "Invalid FNTBlockHeader");
        return false;
    }

    if (Endian::toHostU16(mEndianType, fnt_header->header_size) != sizeof(FNTBlockHeader))
    {
        SEAD_ASSERT_MSG(false, "Invalid FNTBlockHeader");
        return false;
    }

    mFNTBlock = reinterpret_cast<const char*>(fnt_header) +
                Endian::toHostU16(mEndianType, fnt_header->header_size);
    if (Endian::toHostU32(mEndianType, mArchiveBlockHeader->data_block_offset) <
        PtrUtil::diff(mFNTBlock, mArchiveBlockHeader))
    {
        SEAD_ASSERT_MSG(false, "Invalid data block offset");
        return false;
    }

    mDataBlock = archive_ + Endian::toHostU32(mEndianType, mArchiveBlockHeader->data_block_offset);
    return true;
}

SharcArchiveRes::HandleInner* SharcArchiveRes::getHandleInner_(HandleBuffer* handle,
                                                               bool create_new) const
{
    static_assert(sizeof(HandleInner) <= sizeof(HandleBuffer));
    if (create_new)
        return new (handle) HandleInner;
    return reinterpret_cast<HandleInner*>(handle);
}

bool SharcArchiveRes::isExistFileImpl_(const SafeString& path) const
{
    const u32 hash = calcHash32(path, Endian::toHostU32(mEndianType, mFATBlockHeader->hash_key));
    const u32 size = mFATEntrys.size();
#ifdef NNSDK
    const s32 id = binarySearch_(hash, mFATEntrys.getBufferPtr(), 0, size, mEndianType);
#else
    const s32 id = binarySearch_(hash, mFATEntrys.getBufferPtr(), 0, size);
#endif
    return id != -1;
}
}  // namespace sead
