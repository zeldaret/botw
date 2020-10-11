#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadOffsetList.h>
#include <heap/seadExpHeap.h>
#include <heap/seadHeap.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/System/StringBoard.h"
#include "KingSystem/Utils/Types.h"

namespace ksys {

namespace res {
class ResourceUnit;
}
namespace util {
class DualHeap;
}

class OverlayArena {
public:
    struct InitArg {
        bool set_flag_1 = false;
        bool set_flag_8 = false;
        bool use_best_fit_alloc_mode = false;
        u8 _3 = false;
        bool set_flag_10 = true;
        bool set_flag_20 = false;
        u8 _6 = 1;
        u32 alignment = 8;
        u32 size = 0;
        f32 min_free_percentage = 0.0;
        sead::Heap* heap = nullptr;
        sead::Heap* heap2 = nullptr;
        sead::SafeString name;
    };
    KSYS_CHECK_SIZE_NX150(InitArg, 0x38);

    OverlayArena();
    virtual ~OverlayArena();

    bool init(const InitArg& arg);
    void stubbed();
    void updateFlag8(bool on);

    void clearUnits();
    bool isFlag1Set() const;
    bool hasNoUnits() const;
    s32 getNumUnits() const;

    void destroy();

    bool isFlag10Set() const;
    bool isFlag8Set() const;

    /// Checks whether this arena is running out of memory.
    /// This will also update the panic blood moon reason for the ProductReporter if needed.
    /// @return whether the arena is running OOM.
    bool checkIsOom() const;

    util::DualHeap* makeDualHeap(u32 size, const sead::SafeString& name,
                                 sead::Heap::HeapDirection direction, res::ResourceUnit* unit,
                                 bool x);

    void addSize(s32 size);
    void addSize2(s32 size);

    sead::Heap* getHeap() const { return mHeap; }
    sead::Heap* getHeap2() const { return mHeap2; }
    static constexpr size_t getListNodeOffset() { return offsetof(OverlayArena, mListNode); }

private:
    friend class OverlayArenaSystem;

    enum class Flag : u8 {
        _1 = 0x1,
        _2 = 0x2,
        _4 = 0x4,
        _8 = 0x8,
        _10 = 0x10,
        _20 = 0x20,
    };

    void setBloodyMoonReasonForOom_() const;

    bool x_1(s32 size);

    sead::ListNode mListNode;
    sead::TypedBitFlag<Flag> mFlags = [] {
        decltype(mFlags) flags;
        flags.set(Flag::_2);
        flags.set(Flag::_4);
        return flags;
    }();
    sead::ExpHeap* mHeap = nullptr;
    f32 mMinFreePercentage = 0.0;
    sead::Heap* mHeap2 = nullptr;
    sead::OffsetList<res::ResourceUnit> mUnits;
    sead::OffsetList<res::ResourceUnit> mUnits2;  // TODO: rename
    sead::CriticalSection mCS;
    size_t mUsage2 = 0;
    void* _b0 = nullptr;
    s32 mSize = 0;
    s32 mUsage1 = 0;
    u32 mHeapFreeSize = 0;
    u32 _c4 = 0;
    u32 _c8 = 0;
    u32 _cc = 0;
    u32 mHeapSize = 0;
    sead::SafeString mHeapName;
    f32 mUsagePercentage = 0.0;
    StringBoard mStringBoard;
    u8 _f8 = 0;
};
KSYS_CHECK_SIZE_NX150(OverlayArena, 0x100);

}  // namespace ksys
