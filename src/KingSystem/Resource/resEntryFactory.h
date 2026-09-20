#pragma once

#include <basis/seadNew.h>
#include <heap/seadHeapMgr.h>
#include <resource/seadResource.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class EntryFactoryBase : public sead::DirectResourceFactoryBase {
#ifdef MATCHING_HACK_NX_CLANG
public:
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<sead::DirectResourceFactoryBase> typeInfo;
        return &typeInfo;
    }
    static bool checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo)
        __attribute__((noinline));
    bool
    checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override {
        return checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override {
        return getRuntimeTypeInfoStatic();
    }
#else
    SEAD_RTTI_OVERRIDE(EntryFactoryBase, sead::DirectResourceFactoryBase)
#endif
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
#ifdef MATCHING_HACK_NX_CLANG
public:
    static const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfoStatic() {
        static const sead::RuntimeTypeInfo::Derive<EntryFactoryBase> typeInfo;
        return &typeInfo;
    }
    static bool
    checkDerivedRuntimeTypeInfoStatic(const sead::RuntimeTypeInfo::Interface* typeInfo) {
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo =
            EntryFactory<T>::getRuntimeTypeInfoStatic();
        if (typeInfo == clsTypeInfo)
            return true;
        return EntryFactoryBase::checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    bool
    checkDerivedRuntimeTypeInfo(const sead::RuntimeTypeInfo::Interface* typeInfo) const override {
        const sead::RuntimeTypeInfo::Interface* clsTypeInfo =
            EntryFactory<T>::getRuntimeTypeInfoStatic();
        if (typeInfo == clsTypeInfo)
            return true;
        return EntryFactoryBase::checkDerivedRuntimeTypeInfoStatic(typeInfo);
    }
    const sead::RuntimeTypeInfo::Interface* getRuntimeTypeInfo() const override {
        return getRuntimeTypeInfoStatic();
    }
#else
    SEAD_RTTI_OVERRIDE(EntryFactory<T>, EntryFactoryBase)
#endif
public:
    explicit EntryFactory(f32 size_multiplier = 1.0, u32 size_constant = 0)
        : EntryFactoryBase(size_multiplier, size_constant) {}

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
