#include <filedevice/seadFileDeviceMgr.h>
#include <math/seadMathCalcCommon.h>
#include <prim/seadPtrUtil.h>
#include <resource/seadResource.h>

namespace sead
{
Resource::Resource() = default;

Resource::~Resource() = default;

DirectResource::DirectResource() = default;

DirectResource::~DirectResource()
{
    if (mSettingFlag.isOnBit(0))
        delete[] mRawData;
}

s32 DirectResource::getLoadDataAlignment() const
{
    return 4;
}

void DirectResource::doCreate_(u8*, u32, Heap*) {}

void DirectResource::create(u8* buffer, u32 bufferSize, u32 allocSize, bool allocated, Heap* heap)
{
    if (mRawData)
    {
        SEAD_ASSERT_MSG(false, "read twice");
        return;
    }

    mRawData = buffer;
    mRawSize = bufferSize;
    mBufferSize = allocSize;

    mSettingFlag.changeBit(0, allocated);

    doCreate_(buffer, bufferSize, heap);
}

ResourceFactory::~ResourceFactory()
{
    auto* mgr = ResourceMgr::instance();
    if (mgr == nullptr)
        return;

    mgr->unregisterFactory(this);
    if (mgr->getDefaultFactory() == this)
        mgr->setDefaultFactory(nullptr);
}

Resource* DirectResourceFactoryBase::create(const ResourceMgr::CreateArg& createArg)
{
    DirectResource* resource = newResource_(createArg.heap, createArg.alignment);
    if (resource == nullptr)
    {
        SEAD_ASSERT_MSG(false, "resource new failed.");
        return nullptr;
    }

    if (!PtrUtil::isAligned(createArg.buffer, resource->getLoadDataAlignment()))
    {
        SEAD_ASSERT_MSG(false, "buffer alignment invalid: %p, %d", createArg.buffer,
                        resource->getLoadDataAlignment());
        delete resource;
        return nullptr;
    }

    resource->create(createArg.buffer, createArg.file_size, createArg.buffer_size,
                     createArg.need_unload, createArg.heap);
    return resource;
}

Resource* DirectResourceFactoryBase::tryCreate(const ResourceMgr::LoadArg& loadArg)
{
    DirectResource* resource = newResource_(loadArg.instance_heap, loadArg.instance_alignment);
    if (resource == nullptr)
        return nullptr;

    FileDevice::LoadArg fileLoadArg;
    u8* data;

    fileLoadArg.path = loadArg.path;
    fileLoadArg.buffer = loadArg.load_data_buffer;
    fileLoadArg.buffer_size = loadArg.load_data_buffer_size;
    fileLoadArg.buffer_size_alignment = loadArg.load_data_buffer_alignment;
    fileLoadArg.heap = loadArg.load_data_heap;
    fileLoadArg.div_size = loadArg.div_size;
    fileLoadArg.assert_on_alloc_fail = loadArg.assert_on_alloc_fail;

    if (loadArg.load_data_alignment != 0)
        fileLoadArg.alignment = loadArg.load_data_alignment;
    else
        fileLoadArg.alignment =
            Mathi::sign(loadArg.instance_alignment) * resource->getLoadDataAlignment();

    if (loadArg.device != NULL)
        data = loadArg.device->tryLoad(fileLoadArg);
    else
        data = FileDeviceMgr::instance()->tryLoad(fileLoadArg);

    if (data == NULL)
    {
        delete resource;
        return NULL;
    }

    resource->create(data, fileLoadArg.read_size, fileLoadArg.roundup_size, fileLoadArg.need_unload,
                     loadArg.instance_heap);
    return resource;
}

Resource* DirectResourceFactoryBase::tryCreateWithDecomp(const ResourceMgr::LoadArg& loadArg,
                                                         Decompressor* decompressor)
{
    DirectResource* resource = newResource_(loadArg.instance_heap, loadArg.instance_alignment);
    if (resource == NULL)
        return NULL;

    u32 outSize = 0;
    u32 outAllocSize = 0;
    bool outAllocated = false;

    u8* data = decompressor->tryDecompFromDevice(loadArg, resource, &outSize, &outAllocSize,
                                                 &outAllocated);

    if (!data)
    {
        delete resource;
        return nullptr;
    }

    resource->create(data, outSize, outAllocSize, outAllocated, loadArg.instance_heap);
    return resource;
}

}  // namespace sead
