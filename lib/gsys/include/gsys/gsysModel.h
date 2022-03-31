#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadPtrArray.h>
#include <heap/seadDisposer.h>
#include <hostio/seadHostIONode.h>
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

    // For internal use.
    void add_(IModelAccesssHandle* handle) const;
    void remove_(IModelAccesssHandle* handle) const;
    sead::CriticalSection& getCS() const { return mCS; }

private:
    sead::Buffer<ModelInfo> mUnitPool;
    /// Indices into this array are called "model unit access indices".
    sead::PtrArray<ModelInfo> mUnitAccess;
    u8 _48[0x140 - 0x48];
    mutable sead::CriticalSection mCS;
    u8 _180[0x2b8 - 0x180];
};

}  // namespace gsys
