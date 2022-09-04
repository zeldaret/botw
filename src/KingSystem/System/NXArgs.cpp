#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// NONMATCHING - some instructions rearranged
void nxargs::init(sead::Heap* heap) {
    sead::Heap* nxargsheap = sead::ExpHeap::create(
        0x13E8, "nxargsHeap", heap, 8, sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    auto* reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;
    size_t unknown;

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
    if (allEntries) {
        if (mNumEntries != 0) {
            if (allEntries->mNumConditions != 0) {
                allEntries->mFlags = LaunchParamFlag::_0;
                allEntries->mConditions.freeBuffer();
            }
        }
    }

    LaunchParamEntryCondition pdata = allEntries->mConditions[3];
    if (size != 0xF8) {
        pdata.flagdatatype = LaunchParamEntryConditionDataType::None;
        pdata.flagnamehash = 0;
        pdata.operation = ActorEntryConditionOperation::None;
        pdata.rhsvalue = 0;
    }
    mEntries.setBuffer(mNumEntries, allEntries);

    if (!mNumEntries)
        return;
    for (u8 i = 0; i < mNumEntries; i++) {
        LaunchParamEntry* currEntry = &mEntries[i];
        currEntry->mActorNameHash = data->entrydata->mActorNameHash;
        currEntry->mDropActorNameHash = data->entrydata->mDropActorNameHash;
        currEntry->mPositionOffset.x = data->entrydata->mPositionOffset.x;
        currEntry->mPositionOffset.y = data->entrydata->mPositionOffset.y;
        currEntry->mPositionOffset.z = data->entrydata->mPositionOffset.z;
        currEntry->mRotate.x = data->entrydata->mRotate.x;
        currEntry->mRotate.y = data->entrydata->mRotate.y;
        currEntry->mRotate.z = data->entrydata->mRotate.z;
        currEntry->mVelocity.x = data->entrydata->mVelocity.x;
        currEntry->mVelocity.y = data->entrydata->mVelocity.y;
        currEntry->mVelocity.z = data->entrydata->mVelocity.z;
        currEntry->mFlags = data->entrydata->mFlags;
        u64 numSubEntries = data->entrydata->mNumConditions;
        currEntry->mNumConditions = numSubEntries;

        if (numSubEntries != 0) {
            LaunchParamEntryCondition* subEntries =
                new (heap, 8, std::nothrow) LaunchParamEntryCondition[numSubEntries];
            if (subEntries != nullptr)
                currEntry->mConditions.setBuffer(numSubEntries, subEntries);
            if (currEntry->mNumConditions) {
                for (u8 j = 0; j < currEntry->mNumConditions; j++) {
                    LaunchParamEntryCondition* currSubEntry = &currEntry->mConditions[j];

                    currSubEntry->flagnamehash = data->entrydata->mConditions.get(j)->flagnamehash;
                    currSubEntry->flagdatatype = data->entrydata->mConditions.get(j)->flagdatatype;
                    currSubEntry->operation = data->entrydata->mConditions.get(j)->operation;
                    currSubEntry->rhsvalue = data->entrydata->mConditions.get(j)->rhsvalue;
                }
            }
        }
    }
}

}  // namespace ksys