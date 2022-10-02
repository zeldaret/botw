#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// NONMATCHING - some instructions rearranged
void nxargs::init(sead::Heap* heap) {
    size_t unknown;
    sead::Heap* nxargsheap = sead::ExpHeap::create(
        0x13E8, "nxargsHeap", heap, 8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    auto* reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    while (nn::oe::TryPopLaunchParameter(&unknown, reslaunchdata, sizeof(*reslaunchdata))) {
        sead::FixedSafeString<5> inputmagic("");
        inputmagic.format("%s", reslaunchdata->header.magic);
        if (inputmagic != "BotW")
            continue;
        mResField4 = reslaunchdata->header._4;
        mResField6 = reslaunchdata->header._6;
        mType = reslaunchdata->header.type;
        if (mType == ArgsType::CreateActors) {
            mNumEntries = reslaunchdata->header.numentries;
            nxargs::allocEntries(heap, reslaunchdata);
        } else {
            mType = ArgsType::None;
        }
        break;
    }
    nxargsheap->destroy();
}

void nxargs::allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data) {
    const s32 size = mNumEntries;

    if (mNumEntries == 0)
        return;
    LaunchParamEntry* allEntries = new (heap, 8, std::nothrow) LaunchParamEntry[size];
    allEntries->flags = LaunchParamFlag::none;
    mEntries.setBuffer(mNumEntries, allEntries);

    for (u8 i = 0; i < mNumEntries; i++) {
        LaunchParamEntry* currEntry = &mEntries[i];
        currEntry->actorNameHash = data->entrydata(i).actorNameHash;
        currEntry->dropActorNameHash = data->entrydata(i).dropActorNameHash;
        currEntry->positionOffset.x = data->entrydata(i).positionOffset.x;
        currEntry->positionOffset.y = data->entrydata(i).positionOffset.y;
        currEntry->positionOffset.z = data->entrydata(i).positionOffset.z;
        currEntry->rotation.x = data->entrydata(i).rotation.x;
        currEntry->rotation.y = data->entrydata(i).rotation.y;
        currEntry->rotation.z = data->entrydata(i).rotation.z;
        currEntry->velocity.x = data->entrydata(i).velocity.x;
        currEntry->velocity.y = data->entrydata(i).velocity.y;
        currEntry->velocity.z = data->entrydata(i).velocity.z;
        currEntry->flags = data->entrydata(i).flags;
        s64 numConditions = data->entrydata(i).numConditions;
        currEntry->numConditions = numConditions;

        if (numConditions != 0) {
            LaunchParamEntryCondition* subEntries = new (heap, 8, std::nothrow) LaunchParamEntryCondition[numConditions];
            currEntry->conditions.setBuffer(numConditions, subEntries);
            if (currEntry->numConditions) {
                for (u8 j = 0; j < currEntry->numConditions; j++) {
                    LaunchParamEntryCondition* currCondition = &currEntry->conditions[j];
                    currCondition->flagnamehash = data->entrydata(i).conditions(j).flagnamehash;
                    currCondition->flagdatatype = data->entrydata(i).conditions(j).flagdatatype;
                    currCondition->operation = data->entrydata(i).conditions(j).operation;
                    currCondition->rhsvalue = data->entrydata(i).conditions(j).rhsvalue;
                }
            }
        }
    }
}

}  // namespace ksys