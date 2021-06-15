#pragma once

#include <basis/seadNew.h>
#include <heap/seadHeapMgr.h>
#include <resource/seadResource.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class EntryFactoryBase : public sead::DirectResourceFactoryBase {
    SEAD_RTTI_OVERRIDE(EntryFactoryBase, sead::DirectResourceFactoryBase)
public:
    explicit EntryFactoryBase(f32 size_multiplier = 1.0, u32 size_constant = 0)
        : mSizeMultiplier(size_multiplier), mSizeConstant(size_constant) {}
    ~EntryFactoryBase() override { ; }

    virtual u32 getResourceSize() const;
    virtual u32 getLoadDataAlignment() const;

    f32 getSizeMultiplier() const { return mSizeMultiplier; }
    u32 getSizeConstant() const { return mSizeConstant; }

protected:
    f32 mSizeMultiplier;
    u32 mSizeConstant;
};
KSYS_CHECK_SIZE_NX150(EntryFactoryBase, 0x80);

template <typename T>
class EntryFactory : public EntryFactoryBase {
    SEAD_RTTI_OVERRIDE(EntryFactory<T>, EntryFactoryBase)
public:
    using EntryFactoryBase::EntryFactoryBase;

    u32 getResourceSize() const override { return sizeof(T); }
    u32 getLoadDataAlignment() const override { return T::cLoadDataAlignment; }

    sead::DirectResource* newResource_(sead::Heap* heap_, s32 alignment) override {
        sead::Heap* heap = util::getHeapOrCurrentHeap(heap_);
        sead::ScopedCurrentHeapSetter setter{heap};
        return new (heap, alignment, std::nothrow_t{}) T;
    }

protected:
    // XXX: What is this used for?
    T mResource;
};

EntryFactory<Resource>& getDefaultResourceFactory();

}  // namespace ksys::res
