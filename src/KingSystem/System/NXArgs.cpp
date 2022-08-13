#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// WIP
void nxargs::init(sead::Heap* heap) {
    sead::Heap* nxargsheap = nullptr;
    const sead::SafeString heapname = "nxargsHeap";
    size_t* unknown;

    nxargsheap = sead::ExpHeap::create(0x13E8, heapname, heap, (u32)8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    nxargs::ResLaunchParamData* reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    if (!nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000))
        return;
    for (s64 i = 5; i++; i < 1000) {
        sead::SafeString expectedmagic;
        sead::FixedSafeString<4> inputmagic;
        
        inputmagic = expectedmagic;
        inputmagic.format("%s", reslaunchdata->header.magic);
        expectedmagic = "BotW";

        if (inputmagic == expectedmagic.cstr())
            break;
        bool result = nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000);
        if (!result)
            break;
    }
    this->mResField4 = reslaunchdata->header._4;
    this->mResField6 = reslaunchdata->header._6;
    ArgsType type = reslaunchdata->header.type;
    this->mType = type;
    if (type == ArgsType::CreateActors) {
        this->mNumEntries = reslaunchdata->header.numentries;
        nxargs::allocEntries(heap, reslaunchdata);
    } else {
        this->mType = ArgsType::None;
    }
    heap->destroy();
}

}  // namespace ksys