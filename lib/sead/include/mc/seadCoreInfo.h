#pragma once

#include <nn/os.h>

#include <basis/seadTypes.h>
#include <prim/seadBitFlag.h>
#include <prim/seadEnum.h>

namespace sead
{
#line 46
SEAD_ENUM(CoreId, cMain, cSub1, cSub2, cSub3, cSub4, cSub5, cSub6, cSub7, cSub8, cSub9, cSub10,
          cSub11, cSub12, cSub13, cSub14, cSub15, cSub16, cSub17, cSub18, cSub19, cSub20, cSub21,
          cSub22, cSub23, cSub24, cSub25, cSub26, cSub27, cSub28, cSub29, cSub30, cSub31, cSub32,
          cUndef)

class CoreIdMask
{
public:
    CoreIdMask() = default;
    explicit CoreIdMask(CoreId id) { mMask = makeCoreMask_(id); }
    explicit CoreIdMask(CoreId id1, CoreId id2)
    {
        mMask |= makeCoreMask_(id1);
        mMask |= makeCoreMask_(id2);
    }
    explicit CoreIdMask(CoreId id1, CoreId id2, CoreId id3)
    {
        mMask |= makeCoreMask_(id1);
        mMask |= makeCoreMask_(id2);
        mMask |= makeCoreMask_(id3);
    }

    void set(u32 mask) volatile { mMask = mask; }
    operator u32() const volatile { return mMask; }

    volatile CoreIdMask& OR(CoreId id) volatile
    {
        setOn(id);
        return *this;
    }

    bool isOn(const CoreId& id) const volatile { return (mMask & makeCoreMask_(id)) != 0; }
    void setOff(CoreId id) volatile { mMask &= ~makeCoreMask_(id); }
    void setOn(CoreId id) volatile { mMask |= makeCoreMask_(id); }
    void clear() volatile { mMask = 0; }
    u32 countOnBits() const;

protected:
    static u32 makeCoreMask_(CoreId id) { return 1u << u32(int(id)); }

    // It seems that mMask is a u32 and not a BitFlag32 because this class is intended to be
    // volatile, and BitFlag isn't compatible with volatile...
    u32 mMask = 0;
};

class CoreInfo
{
public:
    static void configure();
    static void dump();

    static u32 getNumCores() { return sNumCores; }
    static u32 getPlatformMainCoreId() { return sPlatformCoreId[0]; }
    static u32 getPlatformCoreId(CoreId id) { return sPlatformCoreId[id]; }

    static CoreId getCurrentCoreId()
    {
#ifdef NNSDK
        // Based on the BotW implementation
        const auto number = nn::os::GetTlsValue(sCoreNumberTlsSlot);
        if (number)
            return number - 1;
        return nn::os::GetCurrentCoreNumber();
#else
#error "Unknown platform"
#endif
    }

    static u32 getPlatformMask(CoreId id);

    static CoreId getCoreIdFromPlatformCoreId(u32 idx)
    {
        // XXX: Is this correct?
        return sCoreIdFromPlatformCoreIdTable[idx];
    }

    static CoreIdMask getMaskAll()
    {
        // Based on the implementation of CoreInfo::dump
        CoreIdMask mask;
        mask.set((1u << sNumCores) - 1);
        return mask;
    }

    static CoreIdMask getMaskSubAll()
    {
        // Based on the implementation of CoreInfo::dump
        CoreIdMask mask;
        mask.set(u32(getMaskAll()) - 1);
        return mask;
    }

#ifdef NNSDK
    static nn::os::TlsSlot getCoreNumberTlsSlot() { return sCoreNumberTlsSlot; }
#endif

protected:
    static u32 sNumCores;
    static u32 sPlatformCoreId[32];
    static CoreId sCoreIdFromPlatformCoreIdTable[32];
#ifdef NNSDK
    static nn::os::TlsSlot sCoreNumberTlsSlot;
#endif
};

}  // namespace sead
