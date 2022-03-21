#include <basis/seadRawPrint.h>
#include <filedevice/seadPath.h>
#include <heap/seadHeapMgr.h>
#include <resource/seadResource.h>
#include <resource/seadResourceMgr.h>

namespace sead
{
SEAD_SINGLETON_DISPOSER_IMPL(ResourceMgr)

ResourceMgr::ResourceMgr()
{
    if (HeapMgr::sInstancePtr == NULL)
    {
        SEAD_ASSERT_MSG(false, "ResourceMgr need HeapMgr");
        return;
    }

    mNullResourceFactory =
        new (HeapMgr::sInstancePtr->findContainHeap(this)) DirectResourceFactory<DirectResource>();
    mDefaultResourceFactory = mNullResourceFactory;
    registerFactory(mNullResourceFactory, "");
}

ResourceMgr::~ResourceMgr()
{
    if (mNullResourceFactory == NULL)
        return;

    delete mNullResourceFactory;
    mNullResourceFactory = NULL;
}

// NON_MATCHING: tail call for factory->create
Resource* ResourceMgr::create(const ResourceMgr::CreateArg& arg)
{
    if (!arg.buffer)
    {
        SEAD_ASSERT_MSG(false, "buffer null");
        return nullptr;
    }
    if (arg.file_size == 0)
    {
        SEAD_ASSERT_MSG(false, "file_size is 0");
        return nullptr;
    }
    if (arg.buffer_size == 0)
    {
        SEAD_ASSERT_MSG(false, "buffer_size is 0");
        return nullptr;
    }

    if (arg.factory)
        return arg.factory->create(arg);

    auto* factory = findFactory(arg.ext);
    if (factory)
        return factory->create(arg);

    SEAD_ASSERT_MSG(false, "factory not found: %s", arg.ext.cstr());
    return nullptr;
}

void ResourceMgr::registerFactory(ResourceFactory* factory, const SafeString& name)
{
    factory->setExt(name);

    mFactoryList.pushBack(factory);
}

ResourceFactory* ResourceMgr::setDefaultFactory(ResourceFactory* factory)
{
    ResourceFactory* const previous_default = mDefaultResourceFactory;

    if (!factory)
        factory = mNullResourceFactory;

    mDefaultResourceFactory = factory;
    registerFactory(factory, "");

    return previous_default;
}

ResourceFactory* ResourceMgr::findFactory(const SafeString& name)
{
    for (auto& factory : mFactoryList)
        if (factory->getExt() == name)
            return factory;

    return mDefaultResourceFactory;
}

void ResourceMgr::registerDecompressor(Decompressor* decompressor, const SafeString& name)
{
    if (!name.isEqual(SafeString::cEmptyString))
        decompressor->setName(name);

    mDecompList.pushBack(decompressor);
}

void ResourceMgr::unregisterFactory(ResourceFactory* factory)
{
    mFactoryList.erase(factory);
}

void ResourceMgr::unregisterDecompressor(Decompressor* decompressor)
{
    mDecompList.erase(decompressor);
}

Decompressor* ResourceMgr::findDecompressor(const SafeString& name)
{
    for (auto& decompressor : mDecompList)
        if (decompressor->getName() == name)
            return decompressor;

    return nullptr;
}

Resource* ResourceMgr::tryLoad(const ResourceMgr::LoadArg& arg, const SafeString& factory_name,
                               Decompressor* decompressor)
{
    SafeString actual_factory_name;
    FixedSafeString<32> ext;

    if (!decompressor)
    {
        if (!Path::getExt(&ext, arg.path))
        {
            SEAD_ASSERT_MSG(false, "no file extension");
            return nullptr;
        }

        decompressor = findDecompressor(ext);
    }

    if (decompressor)
        actual_factory_name = factory_name;
    else
        actual_factory_name = ext;

    auto* factory = arg.factory;
    if (!factory)
    {
        factory = findFactory(actual_factory_name);
        SEAD_ASSERT(factory);
    }

    if (arg.has_tried_create_with_decomp)
        *arg.has_tried_create_with_decomp = decompressor;

    if (decompressor)
        return factory->tryCreateWithDecomp(arg, decompressor);
    return factory->tryCreate(arg);
}

Resource* ResourceMgr::tryLoadWithoutDecomp(const ResourceMgr::LoadArg& arg)
{
    auto* factory = arg.factory;
    if (!factory)
    {
        FixedSafeString<32> ext;
        if (Path::getExt(&ext, arg.path))
        {
            factory = findFactory(ext);
            SEAD_ASSERT(factory);
        }
        else
        {
            factory = mDefaultResourceFactory;
        }
    }
    return factory->tryCreate(arg);
}

void ResourceMgr::unload(Resource* res)
{
    if (res)
        delete res;
}
}  // namespace sead
