#include <cstdint>
#include <ore/BinaryFile.h>
#include <ore/BitUtils.h>

namespace ore {

bool BinaryFileHeader::IsValid(s64 magic_, int ver_major_, int ver_minor_, int ver_patch_,
                               int ver_sub_) const {
    bool valid = true;
    valid &= int(ver_major) == ver_major_ && int(ver_minor) == ver_minor_ &&
             magic == magic_ & int(ver_patch) <= ver_patch_;
    valid &= IsEndianReverse() || IsEndianValid();
    valid &= IsAlignmentValid();
    return valid;
}

bool BinaryFileHeader::IsSignatureValid(s64 magic_) const {
    return magic == magic_;
}

bool BinaryFileHeader::IsVersionValid(int major, int minor, int patch, int sub) const {
    if (int(ver_major) != major)
        return false;
    if (int(ver_minor) != minor)
        return false;
    if (int(ver_patch) > patch)
        return false;
    return true;
}

bool BinaryFileHeader::IsEndianReverse() const {
    return bom == s16(0xFFFE);
}

bool BinaryFileHeader::IsEndianValid() const {
    return bom == s16(0xFEFF);
}

bool BinaryFileHeader::IsAlignmentValid() const {
    return (std::uintptr_t(this) & (GetAlignment() - 1)) == 0;
}

int BinaryFileHeader::GetAlignment() const {
    return 1 << alignment;
}

static constexpr u32 FlagRelocated = 1 << 0;

bool BinaryFileHeader::IsRelocated() const {
    return relocation_flags & FlagRelocated;
}

void BinaryFileHeader::SetRelocated(bool relocated) {
    if (relocated)
        relocation_flags |= FlagRelocated;
    else
        relocation_flags &= ~FlagRelocated;
}

void BinaryFileHeader::SetByteOrderMark() {
    bom = s16(0xFEFF);
}

int BinaryFileHeader::GetFileSize() const {
    return file_size;
}

void BinaryFileHeader::SetFileSize(int size) {
    file_size = size;
}

void BinaryFileHeader::SetAlignment(int alignment_) {
    alignment = CountTrailingZeros(u32(alignment_));
}

StringView BinaryFileHeader::GetFileName() const {
    StringView name;
    if (file_name_offset != 0)
        name = reinterpret_cast<const char*>(this) + file_name_offset;
    return name;
}

void BinaryFileHeader::SetFileName(const StringView& name) {
    if (name.empty()) {
        file_name_offset = 0;
    } else {
        file_name_offset = int(intptr_t(name.data()) - intptr_t(this));
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
    }
}

RelocationTable* BinaryFileHeader::GetRelocationTable() {
    if (relocation_table_offset == 0)
        return nullptr;
    return reinterpret_cast<RelocationTable*>(reinterpret_cast<char*>(this) +
                                              relocation_table_offset);
}

void BinaryFileHeader::SetRelocationTable(RelocationTable* table) {
    if (table == nullptr) {
        relocation_table_offset = 0;
    } else {
        relocation_table_offset = int(intptr_t(table) - intptr_t(this));
#ifdef MATCHING_HACK_NX_CLANG
        asm("");
#endif
    }
}

BinaryBlockHeader* BinaryFileHeader::GetFirstBlock() {
    if (first_block_offset == 0)
        return nullptr;
    return reinterpret_cast<BinaryBlockHeader*>(reinterpret_cast<char*>(this) + first_block_offset);
}

const BinaryBlockHeader* BinaryFileHeader::GetFirstBlock() const {
    if (first_block_offset == 0)
        return nullptr;
    return reinterpret_cast<const BinaryBlockHeader*>(reinterpret_cast<const char*>(this) +
                                                      first_block_offset);
}

BinaryBlockHeader* BinaryFileHeader::FindFirstBlock(int type) {
    auto* block = GetFirstBlock();
    if (!block || block->magic == type)
        return block;
    return block->FindNextBlock(type);
}

const BinaryBlockHeader* BinaryFileHeader::FindFirstBlock(int type) const {
    auto* block = GetFirstBlock();
    if (!block || block->magic == type)
        return block;
    return block->FindNextBlock(type);
}

void BinaryFileHeader::SetFirstBlock(BinaryBlockHeader* block) {
    if (block == nullptr)
        first_block_offset = 0;
    else
        first_block_offset = int(intptr_t(block) - intptr_t(this));
}

BinaryBlockHeader* BinaryBlockHeader::FindNextBlock(int type) {
    auto* block = this;
    do
        block = block->GetNextBlock();
    while (block && block->magic != type);
    return block;
}

const BinaryBlockHeader* BinaryBlockHeader::FindNextBlock(int type) const {
    auto* block = this;
    do
        block = block->GetNextBlock();
    while (block && block->magic != type);
    return block;
}

BinaryBlockHeader* BinaryBlockHeader::GetNextBlock() {
    if (next_block_offset == 0)
        return nullptr;
    return reinterpret_cast<BinaryBlockHeader*>(reinterpret_cast<char*>(this) + next_block_offset);
}

const BinaryBlockHeader* BinaryBlockHeader::GetNextBlock() const {
    if (next_block_offset == 0)
        return nullptr;
    return reinterpret_cast<const BinaryBlockHeader*>(reinterpret_cast<const char*>(this) +
                                                      next_block_offset);
}

void BinaryBlockHeader::SetNextBlock(BinaryBlockHeader* block) {
    if (block == nullptr)
        next_block_offset = 0;
    else
        next_block_offset = int(intptr_t(block) - intptr_t(this));
}

}  // namespace ore
