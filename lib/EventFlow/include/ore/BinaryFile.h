#pragma once

#include <ore/StringView.h>
#include <ore/Types.h>
#include <type_traits>
#include <utility>

namespace ore {

template <typename T>
constexpr T AlignUpToPowerOf2(T val, int base) {
    return val + base - 1 & static_cast<unsigned int>(-base);
}

struct RelocationTable;

struct BinaryBlockHeader {
    BinaryBlockHeader* FindNextBlock(int type);
    const BinaryBlockHeader* FindNextBlock(int type) const;
    BinaryBlockHeader* GetNextBlock();
    const BinaryBlockHeader* GetNextBlock() const;
    void SetNextBlock(BinaryBlockHeader* block);

    u32 magic;
    int next_block_offset;
};

struct BinaryFileHeader {
    bool IsValid(s64 magic_, int ver_major_, int ver_minor_, int ver_patch_, int ver_sub_) const;
    bool IsSignatureValid(s64 magic_) const;
    bool IsVersionValid(int major, int minor, int patch, int sub) const;
    bool IsEndianReverse() const;
    bool IsEndianValid() const;

    bool IsAlignmentValid() const;
    int GetAlignment() const;
    void SetAlignment(int alignment_);

    bool IsRelocated() const;
    void SetRelocated(bool relocated);

    void SetByteOrderMark();

    int GetFileSize() const;
    void SetFileSize(int size);

    StringView GetFileName() const;
    void SetFileName(const StringView& name);

    RelocationTable* GetRelocationTable();
    void SetRelocationTable(RelocationTable* table);

    BinaryBlockHeader* GetFirstBlock();
    const BinaryBlockHeader* GetFirstBlock() const;
    void SetFirstBlock(BinaryBlockHeader* block);

    BinaryBlockHeader* FindFirstBlock(int type);
    const BinaryBlockHeader* FindFirstBlock(int type) const;

    u64 magic;
    u8 ver_major;
    u8 ver_minor;
    u8 ver_patch;
    u8 ver_sub;
    s16 bom;
    u8 alignment;
    u8 _f;
    int file_name_offset;
    u16 relocation_flags;
    u16 first_block_offset;
    int relocation_table_offset;
    int file_size;
};

template <typename T>
struct BinTString {
    // Make it impossible to accidentally construct a (partial, broken) copy.
    BinTString(const BinTString&) = delete;
    auto operator=(const BinTString&) = delete;

    T* data() { return chars; }
    const T* data() const { return chars; }

    T& operator[](size_t idx) { return data()[idx]; }
    const T& operator[](size_t idx) const { return data()[idx]; }

    auto begin() { return data(); }
    auto begin() const { return data(); }

    auto end() { return data() + length; }
    auto end() const { return data() + length; }

    bool empty() const { return length == 0; }

    // NOLINTNEXTLINE(google-explicit-constructor)
    operator TStringView<T>() const { return {data(), length}; }

    BinTString* NextString() { return const_cast<BinTString*>(std::as_const(*this).NextString()); }

    const BinTString* NextString() const {
        // XXX: this shouldn't have to be a separate case.
        if constexpr (std::is_same_v<T, wchar_t>) {
            const auto offset = ((2 + (4 * (length + 1) - 1)) & -4) + 2;
            return reinterpret_cast<const BinTString*>(reinterpret_cast<const char*>(this) +
                                                       offset);

        } else {
            // + 1 for the null terminator
            const auto offset = offsetof(BinTString, chars) + sizeof(T) * (length + 1);
            return reinterpret_cast<const BinTString*>(
                reinterpret_cast<const char*>(this) +
                AlignUpToPowerOf2(offset, alignof(BinTString)));
        }
    }

    u16 length;
    T chars[1];
};

using BinString = BinTString<char>;
using BinWString = BinTString<wchar_t>;

template <typename T>
struct BinTPtr {
    void Clear() { offset_or_ptr = 0; }
    void Set(T* ptr) { offset_or_ptr = reinterpret_cast<u64>(ptr); }

    // Only use this after relocation.
    T* Get() { return reinterpret_cast<T*>(offset_or_ptr); }
    const T* Get() const { return reinterpret_cast<const T*>(offset_or_ptr); }

    void SetOffset(void* base, void* ptr) {
        offset_or_ptr = static_cast<int>(ptr ? uintptr_t(ptr) - uintptr_t(base) : 0);
    }

    u64 GetOffset() const { return offset_or_ptr; }

    T* ToPtr(void* base) const {
        const auto offset = static_cast<int>(offset_or_ptr);
        if (offset == 0)
            return nullptr;
        return reinterpret_cast<T*>(reinterpret_cast<char*>(base) + offset);
    }

    void Relocate(void* base) { Set(ToPtr(base)); }
    void Unrelocate(void* base) { SetOffset(base, Get()); }

    u64 offset_or_ptr;
};

static_assert(sizeof(u64) >= sizeof(void*));

}  // namespace ore
