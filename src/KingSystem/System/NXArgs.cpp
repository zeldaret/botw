#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// WIP
void nxargs::init(sead::Heap* heap) {
    nxargs::ResLaunchParamData* reslaunchdata;
    sead::Heap* nxargsheap = nullptr;
    size_t* unknown;

    nxargsheap = sead::ExpHeap::create(0x13E8, "nxargsHeap", heap, 8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    if (nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000)) {
        for (s64 i = 5; i < 1000; ++i) { // this isn't correct but it generates the best result
            sead::SafeString expectedmagic;
            sead::FixedSafeString<4> inputmagic;

            inputmagic = expectedmagic;
            inputmagic.format("%s", reslaunchdata->header.magic);
            expectedmagic = "BotW";

            if (inputmagic == expectedmagic.cstr())
                break;
            else {
                bool result = nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000);
                if (!result)
                    break;
            }
        }
        mResField4 = reslaunchdata->header._4;
        mResField6 = reslaunchdata->header._6;
        ArgsType type = reslaunchdata->header.type;
        mType = type;
        if (type == ArgsType::CreateActors) {
            mNumEntries = reslaunchdata->header.numentries;
            nxargs::allocEntries(nxargsheap, reslaunchdata);
        } else {
            mType = ArgsType::None;
        }
    }
    heap->destroy();
}

}  // namespace ksys