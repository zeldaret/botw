#ifndef SEAD_SZS_DECOMPRESSOR_H_
#define SEAD_SZS_DECOMPRESSOR_H_

#include <basis/seadTypes.h>
#include <resource/seadDecompressor.h>
#include <resource/seadResource.h>
#include <resource/seadResourceMgr.h>

namespace sead
{
class SZSDecompressor : public Decompressor
{
public:
    enum Step
    {
        cStepNormal = 0,
        cStepShort = 1,
        cStepLong = 2,
    };

    struct DecompContext
    {
        DecompContext();
        DecompContext(void* dst);

        void initialize(void* dst);

        __attribute__((always_inline)) bool doCopy(u32 n)
        {
            if (u32(this->destCount) < n)
            {
                if (this->forceDestCount == 0)
                    return false;

                n = this->destCount & 0xFFFF;
            }

            this->destCount -= n;

            do
            {
                *this->destp = *(this->destp - this->lzOffset);
                this->destp += 1;
            } while (--n != 0);

            this->step = SZSDecompressor::cStepNormal;
            return true;
        }

        u8* destp;
        s32 destCount;
        s32 forceDestCount;
        u8 flagMask;
        u8 flags;
        u8 packHigh;
        Step step;
        u16 lzOffset;
        u8 headerSize;
    };

public:
    SZSDecompressor(u32 workSize, u8* workBuffer);
    virtual ~SZSDecompressor() {}

    virtual u8* tryDecompFromDevice(const ResourceMgr::LoadArg& loadArg, Resource* resource,
                                    u32* outSize, u32* outAllocSize, bool* outAllocated);

    static u32 getDecompAlignment(const void* src);
    static u32 getDecompSize(const void* src);
    static s32 readHeader_(DecompContext* context, const u8* src, u32 srcSize);
    static s32 streamDecomp(DecompContext* context, const void* src, u32 srcSize);
    static s32 decomp(void* dst, u32 dstSize, const void* src, u32 srcSize);

    u32 mWorkSize;
    u8* mWorkBuffer;
};

}  // namespace sead

#endif  // SEAD_SZS_DECOMPRESSOR_H_
