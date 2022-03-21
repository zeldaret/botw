#pragma once

#include <array>
#include <basis/seadRawPrint.h>
#include <basis/seadTypes.h>
#include <prim/seadTypedBitFlag.h>
#include "agl/Utils/aglResCommon.h"

namespace sead {
template <typename Key, typename Value>
class TreeMap;
}

namespace agl::utl {

struct ResParameterData {
    constexpr u32 getParameterNameHash() const { return name_hash; }
    constexpr u32 getOffset() const { return 4 * (offset_and_type & 0xFFFFFF); }
    constexpr u32 getType() const { return offset_and_type >> 24; }

    u32 name_hash;
    u32 offset_and_type;
};
static_assert(sizeof(ResParameterData) == 0x8);

struct ResParameter {
    ResParameterData* ptr() const { return mPtr; }
    u8* ptrBytes() const { return reinterpret_cast<u8*>(mPtr); }

    u32 getParameterNameHash() const { return ptr()->getParameterNameHash(); }

    template <typename T>
    T* getData() const {
        return reinterpret_cast<T*>(ptrBytes() + ptr()->getOffset());
    }

    /// Get the data size in bytes.
    size_t getDataSize() const;

    template <typename T>
    bool copyData(T* out) const;

    /// Get the number of elements in the buffer.
    /// @warning Only valid for buffer types.
    size_t getBufferSize() const {
        return *reinterpret_cast<u32*>(ptrBytes() + ptr()->getOffset() - 4);
    }

    ResParameterData* mPtr;
};

struct ResParameterObjData {
    constexpr u32 getParameterObjNameHash() const { return name_hash; }
    constexpr u32 getParametersOffset() const { return 4 * u16(param_offset_and_num); }
    constexpr u16 getNumParameters() const { return param_offset_and_num >> 16; }
    constexpr bool hasParameters() const { return getNumParameters() != 0; }

    u32 name_hash;
    u32 param_offset_and_num;
};
static_assert(sizeof(ResParameterObjData) == 8);

struct ResParameterObj {
    class Iterator {
    public:
        Iterator(ResParameterData* ptr, s32 idx) : mIdx(idx), mPtr(ptr) {}
        bool operator==(const Iterator& rhs) const { return getIndex() == rhs.getIndex(); }
        bool operator!=(const Iterator& rhs) const { return !operator==(rhs); }
        s32 getIndex() const { return mIdx; }
        ResParameter getParam() const { return {mPtr}; }
        ResParameter operator*() const { return getParam(); }
        Iterator& operator++() {
            ++mIdx;
            ++mPtr;
            return *this;
        }

    private:
        s32 mIdx;
        ResParameterData* mPtr;
    };

    Iterator begin() const {
        if (!ptr()->hasParameters())
            return {nullptr, 0};
        return {reinterpret_cast<ResParameterData*>(ptrBytes() + ptr()->getParametersOffset()), 0};
    }
    Iterator end() const { return {nullptr, s32(ptr()->getNumParameters())}; }

    explicit operator bool() const { return ptr() != nullptr; }
    ResParameterObjData* ptr() const { return mPtr; }
    u8* ptrBytes() const { return reinterpret_cast<u8*>(mPtr); }

    u32 getParameterObjNameHash() const { return ptr()->getParameterObjNameHash(); }
    s32 getNum() const { return ptr()->getNumParameters(); }

    /// Get a parameter by index. The index must be valid.
    ResParameter getResParameter(s32 index) const {
        SEAD_ASSERT(0 <= index && index < getNum());
        return getResParameter(index, ptr()->getParametersOffset());
    }

    ResParameter getResParameter(s32 index, u32 offset) const {
        return {reinterpret_cast<ResParameterData*>(ptrBytes() + offset +
                                                    sizeof(ResParameterData) * index)};
    }

    template <typename T>
    T* getParameterData(s32 index) const {
        return getResParameter(index).getData<T>();
    }

    /// @returns the index of the specified parameter, or -1 if not found.
    s32 searchIndex(u32 param_hash) const;

    ResParameterObjData* mPtr;
};

struct ResParameterListData {
    constexpr u32 getParameterListNameHash() const { return name_hash; }
    constexpr u32 getListsOffset() const { return 4 * u16(list_offset_and_num); }
    constexpr u32 getObjectsOffset() const { return 4 * u16(obj_offset_and_num); }
    constexpr u32 getNumLists() const { return list_offset_and_num >> 16; }
    constexpr s32 getNumObjects() const { return obj_offset_and_num >> 16; }
    constexpr bool hasLists() const { return getNumLists() != 0; }
    constexpr bool hasObjects() const { return getNumObjects() != 0; }

    u32 name_hash;
    u32 list_offset_and_num;
    u32 obj_offset_and_num;
};
static_assert(sizeof(ResParameterListData) == 0xc);

struct ResParameterList {
    class ListIterator {
    public:
        ListIterator(ResParameterListData* ptr, s32 idx) : mIdx(idx), mPtr(ptr) {}
        bool operator==(const ListIterator& rhs) const { return getIndex() == rhs.getIndex(); }
        bool operator!=(const ListIterator& rhs) const { return !operator==(rhs); }
        s32 getIndex() const { return mIdx; }
        ResParameterList getList() const { return {mPtr}; }
        ResParameterList operator*() const { return getList(); }
        ListIterator& operator++() {
            ++mIdx;
            ++mPtr;
            return *this;
        }

    private:
        s32 mIdx;
        ResParameterListData* mPtr;
    };

    ListIterator listBegin() const {
        if (!ptr()->hasLists())
            return {nullptr, 0};
        return {reinterpret_cast<ResParameterListData*>(ptrBytes() + ptr()->getListsOffset()), 0};
    }
    ListIterator listEnd() const { return {nullptr, s32(ptr()->getNumLists())}; }

    class ObjIterator {
    public:
        ObjIterator(ResParameterObjData* ptr, s32 idx) : mIdx(idx), mPtr(ptr) {}
        bool operator==(const ObjIterator& rhs) const { return getIndex() == rhs.getIndex(); }
        bool operator!=(const ObjIterator& rhs) const { return !operator==(rhs); }
        s32 getIndex() const { return mIdx; }
        ResParameterObj getObj() const { return {mPtr}; }
        ResParameterObj operator*() const { return getObj(); }
        ObjIterator& operator++() {
            ++mIdx;
            ++mPtr;
            return *this;
        }

    private:
        s32 mIdx;
        ResParameterObjData* mPtr;
    };

    ObjIterator objBegin() const {
        if (!ptr()->hasObjects())
            return {nullptr, 0};
        return {reinterpret_cast<ResParameterObjData*>(ptrBytes() + ptr()->getObjectsOffset()), 0};
    }
    ObjIterator objEnd() const { return {nullptr, s32(ptr()->getNumObjects())}; }

    explicit operator bool() const { return ptr() != nullptr; }
    ResParameterListData* ptr() const { return mPtr; }
    u8* ptrBytes() const { return reinterpret_cast<u8*>(mPtr); }

    u32 getParameterListNameHash() const { return ptr()->getParameterListNameHash(); }
    s32 getResParameterListNum() const { return ptr()->getNumLists(); }
    s32 getResParameterObjNum() const { return ptr()->getNumObjects(); }

    /// Get a parameter list by index. The index must be valid.
    ResParameterList getResParameterList(s32 index) const {
        SEAD_ASSERT(0 <= index && index < getResParameterListNum());
        return getResParameterList(index, ptr()->getListsOffset());
    }

    ResParameterList getResParameterList(s32 index, u32 offset) const {
        return {reinterpret_cast<ResParameterListData*>(ptrBytes() + offset +
                                                        sizeof(ResParameterListData) * index)};
    }

    /// Get a parameter object by index. The index must be valid.
    ResParameterObj getResParameterObj(s32 index) const {
        SEAD_ASSERT(0 <= index && index < getResParameterObjNum());
        return getResParameterObj(index, ptr()->getObjectsOffset());
    }

    ResParameterObj getResParameterObj(s32 index, u32 offset) const {
        return {reinterpret_cast<ResParameterObjData*>(ptrBytes() + offset +
                                                       sizeof(ResParameterObjData) * index)};
    }

    /// @returns the index of the specified list, or -1 if not found.
    s32 searchListIndex(u32 list_hash) const;

    /// @returns the index of the specified object, or -1 if not found.
    s32 searchObjIndex(u32 obj_hash) const;

    void dump(s32, const sead::TreeMap<u32, const char*>* name_table) const;

    ResParameterListData* mPtr;
};

constexpr std::array<char, 4> HeaderMagic = {{'A', 'A', 'M', 'P'}};

enum class ResParameterArchiveFlag : u32 {
    LittleEndian = 1 << 0,
    Utf8 = 1 << 1,
};

struct ResParameterArchiveData {
    static u32 getVersion() { return 2; }
    static u32 getSignature() { return 'AAMP'; }

    std::array<char, 4> magic;
    u32 version;
    sead::TypedBitFlag<ResParameterArchiveFlag> flags;
    u32 file_size;
    u32 pio_version;
    /// Offset to parameter IO (relative to 0x30)
    u32 offset_to_pio;
    /// Number of lists (including parameter IO)
    u32 num_lists;
    u32 num_objects;
    u32 num_parameters;
    u32 data_section_size;
    u32 string_section_size;
    u32 unk_section_size;
};
static_assert(sizeof(ResParameterArchiveData) == 0x30);

struct ResParameterArchive : ResCommon<ResParameterArchiveData> {
    ResParameterArchive() = default;
    explicit ResParameterArchive(const void* p_data);

    ResParameterList getRootList() const {
        return {reinterpret_cast<ResParameterListData*>(
            ptrBytes() + sizeof(ResParameterArchiveData) + mPtr->offset_to_pio)};
    }
};

}  // namespace agl::utl
