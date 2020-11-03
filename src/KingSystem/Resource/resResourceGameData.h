#pragma once

#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <resource/seadResource.h>
#include "KingSystem/GameData/gdtFlag.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::res {

class GameData : public sead::DirectResource {
public:
    static void loadDebugData(gdt::FlagDebugData* data, const al::ByamlIter& iter);
    static void loadFlagProperties(gdt::FlagProperties* properties, const al::ByamlIter& iter);

    GameData();
    ~GameData() override;
    void doCreate_(u8* buffer, u32 values_iter, sead::Heap* heap) override;

    s32 getField14() const { return _14; }

    sead::Buffer<gdt::FlagBool>& getBoolFlags() { return mBoolFlags; }
    sead::Buffer<gdt::FlagS32>& getS32Flags() { return mS32Flags; }
    sead::Buffer<gdt::FlagF32>& getF32Flags() { return mF32Flags; }
    sead::Buffer<gdt::FlagString>& getStringFlags() { return mStringFlags; }
    sead::Buffer<gdt::FlagString64>& getString64Flags() { return mString64Flags; }
    sead::Buffer<gdt::FlagString256>& getString256Flags() { return mString256Flags; }
    sead::Buffer<gdt::FlagVector2f>& getVector2fFlags() { return mVector2fFlags; }
    sead::Buffer<gdt::FlagVector3f>& getVector3fFlags() { return mVector3fFlags; }
    sead::Buffer<gdt::FlagVector4f>& getVector4fFlags() { return mVector4fFlags; }
    sead::PtrArray<gdt::FlagBoolArray>& getBoolArrayFlags() { return mBoolArrayFlags; }
    sead::PtrArray<gdt::FlagS32Array>& getS32ArrayFlags() { return mS32ArrayFlags; }
    sead::PtrArray<gdt::FlagF32Array>& getF32ArrayFlags() { return mF32ArrayFlags; }
    sead::PtrArray<gdt::FlagStringArray>& getStringArrayFlags() { return mStringArrayFlags; }
    sead::PtrArray<gdt::FlagString64Array>& getString64ArrayFlags() { return mString64ArrayFlags; }
    sead::PtrArray<gdt::FlagString256Array>& getString256ArrayFlags() {
        return mString256ArrayFlags;
    }
    sead::PtrArray<gdt::FlagVector2fArray>& getVector2fArrayFlags() { return mVector2fArrayFlags; }
    sead::PtrArray<gdt::FlagVector3fArray>& getVector3fArrayFlags() { return mVector3fArrayFlags; }
    sead::PtrArray<gdt::FlagVector4fArray>& getVector4fArrayFlags() { return mVector4fArrayFlags; }

    const sead::Buffer<gdt::FlagBool>& getBoolFlags() const { return mBoolFlags; }
    const sead::Buffer<gdt::FlagS32>& getS32Flags() const { return mS32Flags; }
    const sead::Buffer<gdt::FlagF32>& getF32Flags() const { return mF32Flags; }
    const sead::Buffer<gdt::FlagString>& getStringFlags() const { return mStringFlags; }
    const sead::Buffer<gdt::FlagString64>& getString64Flags() const { return mString64Flags; }
    const sead::Buffer<gdt::FlagString256>& getString256Flags() const { return mString256Flags; }
    const sead::Buffer<gdt::FlagVector2f>& getVector2fFlags() const { return mVector2fFlags; }
    const sead::Buffer<gdt::FlagVector3f>& getVector3fFlags() const { return mVector3fFlags; }
    const sead::Buffer<gdt::FlagVector4f>& getVector4fFlags() const { return mVector4fFlags; }
    const sead::PtrArray<gdt::FlagBoolArray>& getBoolArrayFlags() const { return mBoolArrayFlags; }
    const sead::PtrArray<gdt::FlagS32Array>& getS32ArrayFlags() const { return mS32ArrayFlags; }
    const sead::PtrArray<gdt::FlagF32Array>& getF32ArrayFlags() const { return mF32ArrayFlags; }

    const sead::PtrArray<gdt::FlagStringArray>& getStringArrayFlags() const {
        return mStringArrayFlags;
    }
    const sead::PtrArray<gdt::FlagString64Array>& getString64ArrayFlags() const {
        return mString64ArrayFlags;
    }
    const sead::PtrArray<gdt::FlagString256Array>& getString256ArrayFlags() const {
        return mString256ArrayFlags;
    }
    const sead::PtrArray<gdt::FlagVector2fArray>& getVector2fArrayFlags() const {
        return mVector2fArrayFlags;
    }
    const sead::PtrArray<gdt::FlagVector3fArray>& getVector3fArrayFlags() const {
        return mVector3fArrayFlags;
    }
    const sead::PtrArray<gdt::FlagVector4fArray>& getVector4fArrayFlags() const {
        return mVector4fArrayFlags;
    }

    static constexpr size_t cLoadDataAlignment = 4;

private:
    s32 _14 = -1;

    sead::Buffer<gdt::FlagBool> mBoolFlags;
    sead::Buffer<gdt::FlagS32> mS32Flags;
    sead::Buffer<gdt::FlagF32> mF32Flags;
    sead::Buffer<gdt::FlagString> mStringFlags;
    sead::Buffer<gdt::FlagString64> mString64Flags;
    sead::Buffer<gdt::FlagString256> mString256Flags;
    sead::Buffer<gdt::FlagVector2f> mVector2fFlags;
    sead::Buffer<gdt::FlagVector3f> mVector3fFlags;
    sead::Buffer<gdt::FlagVector4f> mVector4fFlags;

    sead::PtrArray<gdt::FlagBoolArray> mBoolArrayFlags;
    sead::PtrArray<gdt::FlagS32Array> mS32ArrayFlags;
    sead::PtrArray<gdt::FlagF32Array> mF32ArrayFlags;
    sead::PtrArray<gdt::FlagStringArray> mStringArrayFlags;
    sead::PtrArray<gdt::FlagString64Array> mString64ArrayFlags;
    sead::PtrArray<gdt::FlagString256Array> mString256ArrayFlags;
    sead::PtrArray<gdt::FlagVector2fArray> mVector2fArrayFlags;
    sead::PtrArray<gdt::FlagVector3fArray> mVector3fArrayFlags;
    sead::PtrArray<gdt::FlagVector4fArray> mVector4fArrayFlags;
};
KSYS_CHECK_SIZE_NX150(GameData, 0x140);

}  // namespace ksys::res
