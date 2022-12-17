#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

void nxargs::init(sead::Heap* heap) {
    sead::Heap* nxargsheap = sead::ExpHeap::create(
        0x13E8, "nxargsHeap", heap, 8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    auto* data = new (nxargsheap) u8[0x1000];
    size_t unknown;

    while (nn::oe::TryPopLaunchParameter(&unknown, data, 0x1000)) {
        {
            sead::FixedSafeString<5> inputmagic("");
            inputmagic.format("%s", reinterpret_cast<char*>(data));
            if (inputmagic != "BotW")
                continue;
        }
        using sead::BitUtil::bitCastPtr;
        mResField4 = bitCastPtr<u16>(data, 4);
        mResField6 = bitCastPtr<u8>(data, 6);
        mType = bitCastPtr<ArgsType>(data, 7);
        if (mType == ArgsType::CreateActors) {
            mNumEntries = bitCastPtr<u8>(data, 0xC);
            nxargs::allocEntries(heap, data);
        } else {
            mType = ArgsType::None;
        }
        break;
    }
    nxargsheap->destroy();
}

void nxargs::allocEntries(sead::Heap* heap, const u8* data) {
    const s32 size = mNumEntries;

    if (mNumEntries == 0)
        return;
    mEntries.allocBufferAssert(size, heap);

    using sead::BitUtil::bitCastPtr;
    u32 offset = 0x10;
    for (u8 i = 0; i < mNumEntries; i++) {
        LaunchParamEntry* currEntry = &mEntries[i];
        currEntry->actorNameHash = bitCastPtr<u32>(data, offset + 0);
        currEntry->dropActorNameHash = bitCastPtr<u32>(data, offset + 4);
        currEntry->positionOffset.x = bitCastPtr<f32>(data, offset + 8);
        currEntry->positionOffset.y = bitCastPtr<f32>(data, offset + 0xc);
        currEntry->positionOffset.z = bitCastPtr<f32>(data, offset + 0x10);
        currEntry->rotation.x = bitCastPtr<f32>(data, offset + 0x14);
        currEntry->rotation.y = bitCastPtr<f32>(data, offset + 0x18);
        currEntry->rotation.z = bitCastPtr<f32>(data, offset + 0x1c);
        currEntry->velocity.x = bitCastPtr<f32>(data, offset + 0x20);
        currEntry->velocity.y = bitCastPtr<f32>(data, offset + 0x24);
        currEntry->velocity.z = bitCastPtr<f32>(data, offset + 0x28);
        currEntry->flags = bitCastPtr<LaunchParamFlag>(data, offset + 0x2c);
        s64 numConditions = bitCastPtr<u8>(data, offset + 0x2d);
        currEntry->numConditions = numConditions;
        offset += 0x30;

        if (numConditions > 0) {
            currEntry->conditions.allocBufferAssert(numConditions, heap);
            for (u8 j = 0; j < currEntry->numConditions; j++) {
                LaunchParamEntryCondition* currCondition = &currEntry->conditions[j];
                currCondition->flagNameHash = bitCastPtr<u32>(data, offset);
                currCondition->flagDataType =
                    bitCastPtr<LaunchParamEntryConditionDataType>(data, offset + 4);
                currCondition->operation =
                    bitCastPtr<ActorEntryConditionOperation>(data, offset + 5);
                currCondition->rhsValue = bitCastPtr<f32>(data, offset + 8);
                offset += 0xc;
            }
        }
    }
}

// todo: placeholder to hide the warning in tools/check
void nxargs::handleArgs() {}

}  // namespace ksys