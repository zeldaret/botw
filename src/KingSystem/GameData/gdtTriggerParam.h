#pragma once

#include <basis/seadTypes.h>
#include <codec/seadHashCRC32.h>
#include <container/seadBuffer.h>
#include <container/seadObjArray.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <prim/seadStorageFor.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/GameData/gdtFlag.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class GameData;
}

namespace ksys::gdt {

class TriggerParam {
public:
    struct ResetEntry {
        sead::SizedEnum<FlagType::ValueType, u8> type;
        sead::SizedEnum<ResetType, u8> reset_type;
        s32 index;
    };
    KSYS_CHECK_SIZE_NX150(ResetEntry, 0x8);

    TriggerParam();

    void copyFromGameDataRes(res::GameData* gdata, sead::Heap* heap);
    void init(sead::Heap* heap);
    void destroyHeap();
    void allocBools(s32 size, sead::Heap* heap);
    void allocS32s(s32 size, sead::Heap* heap);
    void copyAllFlags(const TriggerParam& src, sead::Heap* heap, bool init_reset_data);
    void copyPermanentFlags(const TriggerParam& src, sead::Heap* heap);

    FlagType getFlagType(const sead::SafeString& name) const;

    // region Value getters (by hash)

    bool getBool(bool* value, s32 index, bool check_permissions) const;
    bool getS32(s32* value, s32 index, bool check_permissions) const;
    bool getF32(f32* value, s32 index, bool check_permissions) const;
    bool getStr(const char** value, s32 index, bool check_permissions) const;
    bool getStr64(const char** value, s32 index, bool check_permissions) const;
    bool getStr256(const char** value, s32 index, bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, s32 index, bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, s32 index, bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, s32 index, bool check_permissions) const;

    bool getBool(bool* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getS32(s32* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getF32(f32* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr64(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getStr256(const char** value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, s32 array_index, s32 index, bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, s32 array_index, s32 index, bool check_permissions) const;

    // endregion

    // region Value getters (by name)

    bool getBool(bool* value, const sead::SafeString& name, bool check_permissions) const;
    bool getBool2(bool* value, const sead::SafeString& name, bool check_permissions) const;
    bool getS32(s32* value, const sead::SafeString& name, bool check_permissions) const;
    bool getF32(f32* value, const sead::SafeString& name, bool check_permissions) const;
    bool getStr(const char** value, const sead::SafeString& name, bool check_permissions) const;
    bool getStr64(const char** value, const sead::SafeString& name, bool check_permissions) const;
    bool getStr256(const char** value, const sead::SafeString& name, bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, const sead::SafeString& name,
                  bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, const sead::SafeString& name,
                  bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, const sead::SafeString& name,
                  bool check_permissions) const;

    bool getBool(bool* value, const sead::SafeString& name, s32 index,
                 bool check_permissions) const;
    bool getS32(s32* value, const sead::SafeString& name, s32 index, bool check_permissions) const;
    bool getF32(f32* value, const sead::SafeString& name, s32 index, bool check_permissions) const;
    bool getStr(const char** value, const sead::SafeString& name, s32 index,
                bool check_permissions) const;
    bool getStr64(const char** value, const sead::SafeString& name, s32 index,
                  bool check_permissions) const;
    bool getStr256(const char** value, const sead::SafeString& name, s32 index,
                   bool check_permissions) const;
    bool getVec2f(sead::Vector2f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions) const;
    bool getVec3f(sead::Vector3f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions) const;
    bool getVec4f(sead::Vector4f* value, const sead::SafeString& name, s32 index,
                  bool check_permissions) const;

    // endregion

    // region Index getters (by hash)

    s32 getBoolIdx(u32 name) const;
    s32 getS32Idx(u32 name) const;
    s32 getF32Idx(u32 name) const;
    s32 getStrIdx(u32 name) const;
    s32 getStr64Idx(u32 name) const;
    s32 getStr256Idx(u32 name) const;
    s32 getVec2fIdx(u32 name) const;
    s32 getVec3fIdx(u32 name) const;
    s32 getVec4fIdx(u32 name) const;
    s32 getBoolArrayIdx(u32 name) const;
    s32 getS32ArrayIdx(u32 name) const;
    s32 getF32ArrayIdx(u32 name) const;
    s32 getStrArrayIdx(u32 name) const;
    s32 getStr64ArrayIdx(u32 name) const;
    s32 getStr256ArrayIdx(u32 name) const;
    s32 getVec2fArrayIdx(u32 name) const;
    s32 getVec3fArrayIdx(u32 name) const;
    s32 getVec4fArrayIdx(u32 name) const;

    // endregion

    // region Index getters (by name)

    s32 getBoolIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getBoolIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getS32Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getS32Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getF32Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getF32Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStrIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStrIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr64Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr64Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr256Idx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr256Idx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec2fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec2fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec3fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec3fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec4fIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec4fIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getBoolArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getBoolArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getS32ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getS32ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getF32ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getF32ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStrArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStrArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr64ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr64ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getStr256ArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getStr256ArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec2fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec2fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec3fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec3fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }
    s32 getVec4fArrayIdx(const sead::SafeString& name) const {
        return name.isEmpty() ? -1 : getVec4fArrayIdx(sead::HashCRC32::calcStringHash(name));
    }

    // endregion

    // region Array size getters

    bool getBoolArraySize(s32* size, s32 index) const;
    bool getS32ArraySize(s32* size, s32 index) const;
    bool getF32ArraySize(s32* size, s32 index) const;
    bool getStrArraySize(s32* size, s32 index) const;
    bool getStr64ArraySize(s32* size, s32 index) const;
    bool getStr256ArraySize(s32* size, s32 index) const;
    bool getVec2fArraySize(s32* size, s32 index) const;
    bool getVec3fArraySize(s32* size, s32 index) const;
    bool getVec4fArraySize(s32* size, s32 index) const;

    bool getBoolArraySizeByHash(s32* size, u32 name) const;
    bool getS32ArraySizeByHash(s32* size, u32 name) const;
    bool getF32ArraySizeByHash(s32* size, u32 name) const;
    bool getStrArraySizeByHash(s32* size, u32 name) const;
    bool getStr64ArraySizeByHash(s32* size, u32 name) const;
    bool getStr256ArraySizeByHash(s32* size, u32 name) const;
    bool getVec2fArraySizeByHash(s32* size, u32 name) const;
    bool getVec3fArraySizeByHash(s32* size, u32 name) const;
    bool getVec4fArraySizeByHash(s32* size, u32 name) const;

    bool getS32ArraySize(s32* size, const sead::SafeString& name) const;
    bool getStr64ArraySize(s32* size, const sead::SafeString& name) const;
    bool getVec3fArraySize(s32* size, const sead::SafeString& name) const;

    // endregion

    bool getMinValueForS32(s32* min, const sead::SafeString& name) const;
    bool getMaxValueForS32(s32* max, const sead::SafeString& name) const;

private:
    enum class BitFlag : u8 {

    };

    void allocCombinedFlagArrays(sead::Heap* heap);
    void updateBoolFlagCounts();
    void initResetData(sead::Heap* heap);
    void initRevivalRandomBools(sead::Heap* heap);

    sead::TypedBitFlag<BitFlag>& getBitFlags() { return *mBitFlags.data(); }
    const sead::TypedBitFlag<BitFlag>& getBitFlags() const { return *mBitFlags.data(); }
    sead::SafeArray<sead::CriticalSection, 3>& getCriticalSections() {
        return *mCriticalSections.data();
    }

    u32 mResourceFlags = 0;

    sead::PtrArray<FlagBase> mBoolFlags;
    sead::PtrArray<FlagBase> mS32Flags;
    sead::PtrArray<FlagBase> mF32Flags;
    sead::PtrArray<FlagBase> mStringFlags;
    sead::PtrArray<FlagBase> mString64Flags;
    sead::PtrArray<FlagBase> mString256Flags;
    sead::PtrArray<FlagBase> mVector2fFlags;
    sead::PtrArray<FlagBase> mVector3fFlags;
    sead::PtrArray<FlagBase> mVector4fFlags;

    sead::PtrArray<sead::PtrArray<FlagBase>> mBoolArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mS32ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mF32ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mStringArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mString64ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mString256ArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector2fArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector3fArrayFlags;
    sead::PtrArray<sead::PtrArray<FlagBase>> mVector4fArrayFlags;

    sead::StorageFor<sead::SafeArray<sead::Buffer<ResetEntry>, 3>> mUnkArray{};

    sead::ObjArray<FlagBase> mCombinedBoolFlags;
    sead::ObjArray<FlagBase> mCombinedS32Flags;
    sead::ObjArray<FlagBase> mCombinedF32Flags;
    sead::ObjArray<FlagBase> mCombinedStringFlags;
    sead::ObjArray<FlagBase> mCombinedString64Flags;
    sead::ObjArray<FlagBase> mCombinedString256Flags;
    sead::ObjArray<FlagBase> mCombinedVector2fFlags;
    sead::ObjArray<FlagBase> mCombinedVector3fFlags;
    sead::ObjArray<FlagBase> mCombinedVector4fFlags;

    sead::Buffer<ResetEntry> mResetEntries;
    sead::PtrArray<FlagBool> mRevivalRandomBools;

    sead::Heap* mHeap = nullptr;

    sead::SafeArray<s32, 18> mCounts;
    sead::SafeArray<s32, 15> mNumBoolFlagsPerCategory;
    sead::StorageFor<sead::SafeArray<sead::CriticalSection, 3>> mCriticalSections{};
    sead::StorageFor<sead::TypedBitFlag<BitFlag>> mBitFlags;
};
KSYS_CHECK_SIZE_NX150(TriggerParam, 0x3f0);

}  // namespace ksys::gdt
