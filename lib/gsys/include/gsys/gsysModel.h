#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadOffsetList.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
#include <math/seadMatrix.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>

namespace gsys {

class IModelAccesssHandle;
class ModelBone;
class ModelUnit;

class ModelInfo {
public:
    ModelUnit* mModelUnit;
    void* _8;
    void* _10;
    u32 _18;
    s16 mAccessIndex;
    u8 _1e;
    void* _20;
    void* _28;
    u32 _30;
    u32 _34;
};

// TODO
class Model : public sead::IDisposer, public sead::hostio::Node {
public:
    Model();
    ~Model() override;

    sead::PtrArray<ModelInfo>& getUnits() { return mUnitAccess; }
    const sead::PtrArray<ModelInfo>& getUnits() const { return mUnitAccess; }

    const sead::Matrix34f& getMatrix() const { return mMatrix; }
    const sead::Vector3f& getScale() const { return _88; }

    void setBoneLocalMatrix(const BoneAccessKey& key, const sead::Matrix34f& matrix,
                            const sead::Vector3f& scale);

    // For internal use.
    void add_(IModelAccesssHandle* handle) const;
    void remove_(IModelAccesssHandle* handle) const;
    sead::CriticalSection& getCS() const { return mCS; }

private:
    sead::Buffer<ModelInfo> mUnitPool;
    /// Indices into this array are called "model unit access indices".
    sead::PtrArray<ModelInfo> mUnitAccess;
    sead::PtrArray<ModelInfo> _48;
    sead::Matrix34f mMatrix = sead::Matrix34f::ident;
    sead::Vector3f _88 = sead::Vector3f::ones;
    sead::Vector3f _94 = sead::Vector3f::ones;
    bool _a0 = true;
    bool _a1 = false;
    bool _a2 = true;
    bool _a3 = false;
    u16 mNumModels = 0;
    u8 _a6[0x140 - 0xa6];
    mutable sead::CriticalSection mCS;
    sead::OffsetList<IModelAccesssHandle> mHandleList;
    sead::FixedSafeString<256> mName{"名称未設定"};
    u8 _2b0[0x2b8 - 0x2b0];
};

}  // namespace gsys
