#ifndef SEAD_RESOURCEMGR_H_
#define SEAD_RESOURCEMGR_H_

#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include <filedevice/seadFileDevice.h>
#include <heap/seadDisposer.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>

namespace sead
{
class Resource;
class DirectResource;
class ResourceFactory;
class Decompressor;

template <typename T>
class DirectResourceFactory;

class ResourceMgr
{
    SEAD_SINGLETON_DISPOSER(ResourceMgr)

public:
    struct CreateArg
    {
        u8* buffer = nullptr;
        u32 file_size = 0;
        u32 buffer_size = 0;
        bool need_unload = false;
        ResourceFactory* factory = nullptr;
        SafeString ext;
        Heap* heap = nullptr;
        s32 alignment = 0x20;
    };
#ifdef NNSDK
    static_assert(sizeof(CreateArg) == 0x40);
#endif

    struct LoadArg
    {
        SafeString path;
        Heap* instance_heap = nullptr;
        Heap* load_data_heap = nullptr;
        s32 instance_alignment = 0x20;
        s32 load_data_alignment = 0;
        u8* load_data_buffer = nullptr;
        u32 load_data_buffer_size = 0;
        s32 load_data_buffer_alignment = 0;
        ResourceFactory* factory = nullptr;
        FileDevice* device = nullptr;
        // Read chunk size.
        u32 div_size = 0;
        bool assert_on_alloc_fail = true;
        bool* has_tried_create_with_decomp = nullptr;
    };
#ifdef NNSDK
    static_assert(sizeof(LoadArg) == 0x58);
#endif

public:
    ResourceMgr();
    ~ResourceMgr();

    Resource* create(const CreateArg& arg);

    void registerFactory(ResourceFactory* factory, const SafeString& name);
    void unregisterFactory(ResourceFactory* factory);
    ResourceFactory* getDefaultFactory() const { return mDefaultResourceFactory; }
    /// Set the specified factory as the default factory. Its name is set to "".
    /// @param factory  If null, a dummy resource factory is set as the default factory.
    /// @returns the previous default factory
    ResourceFactory* setDefaultFactory(ResourceFactory* factory);
    ResourceFactory* findFactory(const SafeString& name);

    void registerDecompressor(Decompressor* decompressor, const SafeString& name);
    void unregisterDecompressor(Decompressor* decompressor);
    Decompressor* findDecompressor(const SafeString& name);

    Resource* tryLoad(const LoadArg& arg, const SafeString& factory_name,
                      Decompressor* decompressor);
    Resource* tryLoadWithoutDecomp(const LoadArg& arg);
    void unload(Resource* res);

private:
    typedef TList<ResourceFactory*> FactoryList;
    typedef TList<Decompressor*> DecompressorList;

    FactoryList mFactoryList;
    DecompressorList mDecompList;
    ResourceFactory* mNullResourceFactory = nullptr;
    ResourceFactory* mDefaultResourceFactory = nullptr;
};
#ifdef NNSDK
static_assert(sizeof(ResourceMgr) == 0x60);
#endif

}  // namespace sead

#endif  // SEAD_RESOURCEMGR_H_
