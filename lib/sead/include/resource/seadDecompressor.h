#ifndef SEAD_DECOMPRESSOR_H_
#define SEAD_DECOMPRESSOR_H_

#include <basis/seadTypes.h>
#include <container/seadTList.h>
#include <heap/seadDisposer.h>
#include <prim/seadSafeString.h>
#include <resource/seadResource.h>
#include <resource/seadResourceMgr.h>

namespace sead
{
class Decompressor : public TListNode<Decompressor*>, public IDisposer
{
public:
    Decompressor(const SafeString& name) : TListNode<Decompressor*>(this), IDisposer(), mExt(name)
    {
    }

    virtual ~Decompressor()
    {
        if (ResourceMgr::instance() != NULL)
            ResourceMgr::instance()->unregisterDecompressor(this);
    }

    virtual u8* tryDecompFromDevice(const ResourceMgr::LoadArg& loadArg, Resource* resource,
                                    u32* outSize, u32* outAllocSize, bool* outAllocated) = 0;

    const SafeString& getName() const { return mExt; }
    void setName(const SafeString& name) { mExt = name; }

protected:
    FixedSafeString<32> mExt;
};

}  // namespace sead

#endif  // SEAD_DECOMPRESSOR_H_
