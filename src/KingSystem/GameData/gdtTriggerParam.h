#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <container/seadSafeArray.h>
#include <prim/seadStorageFor.h>
#include <prim/seadTypedBitFlag.h>
#include "KingSystem/GameData/gdtFlag.h"
#include "KingSystem/Utils/Types.h"

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

private:
    enum class Flag : u8 {

    };

    sead::TypedBitFlag<Flag>& getFlags() { return *mFlags.data(); }
    const sead::TypedBitFlag<Flag>& getFlags() const { return *mFlags.data(); }
    sead::SafeArray<sead::CriticalSection, 3>& getCriticalSections() {
        return *mCriticalSections.data();
    }

    u32 mResourceFlags = 0;

    sead::PtrArray<FlagBool> mBoolFlags;
    sead::PtrArray<FlagS32> mS32Flags;
    sead::PtrArray<FlagF32> mF32Flags;
    sead::PtrArray<FlagString> mStringFlags;
    sead::PtrArray<FlagString64> mString64Flags;
    sead::PtrArray<FlagString256> mString256Flags;
    sead::PtrArray<FlagVector2f> mVector2fFlags;
    sead::PtrArray<FlagVector3f> mVector3fFlags;
    sead::PtrArray<FlagVector4f> mVector4fFlags;

    sead::PtrArray<FlagBoolArray> mBoolArrayFlags;
    sead::PtrArray<FlagS32Array> mS32ArrayFlags;
    sead::PtrArray<FlagF32Array> mF32ArrayFlags;
    sead::PtrArray<FlagStringArray> mStringArrayFlags;
    sead::PtrArray<FlagString64Array> mString64ArrayFlags;
    sead::PtrArray<FlagString256Array> mString256ArrayFlags;
    sead::PtrArray<FlagVector2fArray> mVector2fArrayFlags;
    sead::PtrArray<FlagVector3fArray> mVector3fArrayFlags;
    sead::PtrArray<FlagVector4fArray> mVector4fArrayFlags;

    // FIXME
    sead::PtrArray<FlagBool> mUnkArray0;
    sead::PtrArray<FlagBool> mUnkArray1;
    sead::PtrArray<FlagBool> mUnkArray2;
    sead::PtrArray<FlagBool> mUnkArray3;
    sead::PtrArray<FlagBool> mUnkArray4;
    sead::PtrArray<FlagBool> mUnkArray5;
    sead::PtrArray<FlagBool> mUnkArray6;
    sead::PtrArray<FlagBool> mUnkArray7;
    sead::PtrArray<FlagBool> mUnkArray8;
    sead::PtrArray<FlagBool> mUnkArray9;
    sead::PtrArray<FlagBool> mUnkArray10;
    sead::PtrArray<FlagBool> mUnkArray11;
    sead::PtrArray<FlagBool> mUnkArray12;
    sead::PtrArray<FlagBool> mUnkArray13;
    sead::PtrArray<FlagBool> mUnkArray14;
    sead::PtrArray<FlagBool> mUnkArray15;
    sead::PtrArray<FlagBool> mUnkArray16;
    sead::PtrArray<FlagBool> mUnkArray17;
    sead::PtrArray<FlagBool> mUnkArray18;
    sead::PtrArray<FlagBool> mUnkArray19;
    sead::PtrArray<FlagBool> mUnkArray20;
    sead::Buffer<ResetEntry> mResetEntries;
    sead::PtrArray<FlagBool> mRevivalRandomBools;

    sead::Heap* mHeap = nullptr;

    sead::SafeArray<s32, 33> mCounts;
    sead::StorageFor<sead::SafeArray<sead::CriticalSection, 3>> mCriticalSections{};
    sead::StorageFor<sead::TypedBitFlag<Flag>> mFlags;
};
KSYS_CHECK_SIZE_NX150(TriggerParam, 0x3f0);

}  // namespace ksys::gdt
