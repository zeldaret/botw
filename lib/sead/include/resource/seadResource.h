#ifndef SEAD_RESOURCE_H_
#define SEAD_RESOURCE_H_

#include <basis/seadNew.h>
#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadBitFlag.h>
#include <resource/seadDecompressor.h>
#include <resource/seadResourceMgr.h>

namespace sead
{
class Resource
{
public:
    SEAD_RTTI_BASE(Resource)

    Resource();
    virtual ~Resource();
};

class DirectResource : public Resource
{
    SEAD_RTTI_OVERRIDE(DirectResource, Resource)

public:
    DirectResource();
    ~DirectResource() override;

    virtual s32 getLoadDataAlignment() const;
    virtual void doCreate_(u8* buffer, u32 bufferSize, Heap* heap);

    void create(u8* buffer, u32 bufferSize, u32 allocSize, bool allocated, Heap* heap);

    u8* getRawData() const { return mRawData; }
    u32 getRawSize() const { return mRawSize; }
    u32 getBufferSize() const { return mBufferSize; }

    static constexpr size_t cLoadDataAlignment = 4;

protected:
    u8* mRawData = 0;
    u32 mRawSize = 0;
    u32 mBufferSize = 0;
    BitFlag32 mSettingFlag;
};

class ResourceFactory : public TListNode<ResourceFactory*>, public IDisposer
{
    SEAD_RTTI_BASE(ResourceFactory)
public:
    ResourceFactory() : TListNode<ResourceFactory*>(this), IDisposer(), mExt() {}

    virtual ~ResourceFactory();

    virtual Resource* tryCreate(const ResourceMgr::LoadArg& loadArg) = 0;
    virtual Resource* tryCreateWithDecomp(const ResourceMgr::LoadArg& loadArg,
                                          Decompressor* decompressor) = 0;
    virtual Resource* create(const ResourceMgr::CreateArg& createArg) = 0;

    const SafeString& getExt() const { return mExt; }
    void setExt(const SafeString& ext) { mExt = ext; }

protected:
    FixedSafeString<32> mExt;
};

class DirectResourceFactoryBase : public ResourceFactory
{
    SEAD_RTTI_OVERRIDE(DirectResourceFactoryBase, ResourceFactory)
public:
    DirectResourceFactoryBase() : ResourceFactory() {}

    ~DirectResourceFactoryBase() override {}

    Resource* create(const ResourceMgr::CreateArg& createArg) override;
    Resource* tryCreate(const ResourceMgr::LoadArg& loadArg) override;
    Resource* tryCreateWithDecomp(const ResourceMgr::LoadArg& loadArg,
                                  Decompressor* decompressor) override;
    virtual DirectResource* newResource_(Heap* heap, s32 alignment) = 0;
};

template <typename T>
class DirectResourceFactory : public DirectResourceFactoryBase
{
    SEAD_RTTI_OVERRIDE(DirectResourceFactory<T>, DirectResourceFactoryBase)
public:
    DirectResourceFactory() : DirectResourceFactoryBase() {}

    ~DirectResourceFactory() override {}

    DirectResource* newResource_(Heap* heap, s32 alignment) override
    {
        return new (heap, alignment) T;
    }
};

}  // namespace sead

#endif  // SEAD_RESOURCE_H_
