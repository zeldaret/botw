#include "hostio/seadHostIOReflexible.h"
#include "basis/seadRawPrint.h"
#include "heap/seadHeap.h"
#include "heap/seadHeapMgr.h"
#include "prim/seadMemUtil.h"

namespace sead::hostio
{
namespace
{
struct ReflexibleStringCopy
{
    Heap* heap;
    char string_data;
};
}  // namespace

Reflexible::Reflexible()
{
    setNodeName("");
    setNodeMeta("");
}

Reflexible::Reflexible(Heap* heap, IDisposer::HeapNullOption heap_null_option)
    : NodeEventListener(heap, heap_null_option)
{
    setNodeName("");
    setNodeMeta("");
}

void Reflexible::setNodeName(const SafeString& name)
{
    if (mName != name.cstr() && mAllocFlg.isOn(u8(AllocFlg::Name)))
        safeDelete_(AllocFlg::Name);

    SEAD_ASSERT_MSG(!MemUtil::isStack(name.cstr()), "%p is in stack", name.cstr());
    mName = name.cstr();
}

void Reflexible::setNodeNameCopyString(const SafeString& name, Heap* heap)
{
    mName = createStringBuffer_(AllocFlg::Name, name, heap);
}

void Reflexible::setNodeMeta(const SafeString& meta)
{
    if (mMeta != meta.cstr() && mAllocFlg.isOn(u8(AllocFlg::Meta)))
        safeDelete_(AllocFlg::Meta);

    SEAD_ASSERT_MSG(!MemUtil::isStack(meta.cstr()), "%p is in stack", meta.cstr());
    mMeta = meta.cstr();
}

void Reflexible::setNodeMetaCopyString(const SafeString& meta, Heap* heap)
{
    mMeta = createStringBuffer_(AllocFlg::Meta, meta, heap);
}

void Reflexible::safeDelete_(Reflexible::AllocFlg flag)
{
    if (!mAllocFlg.isOn(u8(flag)))
        return;

    const char* string = nullptr;
    if (flag == AllocFlg::Name)
        string = mName;
    else if (flag == AllocFlg::Meta)
        string = mMeta;

    mAllocFlg.reset(u8(flag));

    if (string)
    {
        auto pair = reinterpret_cast<ReflexibleStringCopy*>(uintptr_t(string) - sizeof(void*));
        pair->heap->free(pair);
    }
}

const char* Reflexible::createStringBuffer_(Reflexible::AllocFlg flag, const SafeString& name,
                                            Heap* heap)
{
    safeDelete_(flag);

    const s32 name_len = name.calcLength();

    if (!heap)
        heap = HeapMgr::instance()->getCurrentHeap();

    SEAD_ASSERT(heap);

    auto pair = static_cast<ReflexibleStringCopy*>(heap->alloc(name_len + 1 + sizeof(Heap*)));
    pair->heap = heap;
    // Copy the string into the buffer and terminate it.
    MemUtil::copy(&pair->string_data, name.cstr(), name_len);
    (&pair->string_data)[name_len] = 0;

    mAllocFlg.set(u8(flag));
    return &pair->string_data;
}

void Reflexible::disposeHostIOImpl_()
{
    safeDelete_(AllocFlg::Name);
    safeDelete_(AllocFlg::Meta);
}
}  // namespace sead::hostio
