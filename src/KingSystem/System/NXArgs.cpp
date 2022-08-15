#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// WIP
void nxargs::init(sead::Heap* heap) {
    nxargs::ResLaunchParamData* reslaunchdata;
    sead::Heap* nxargsheap = nullptr;
    size_t* unknown;

    nxargsheap = sead::ExpHeap::create(0x13E8, "nxargsHeap", heap, 8,
                                       sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    if (nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000)) {
        for (s64 i = 5; ++i;) {  // this isn't correct but it generates the best result
            sead::SafeString expectedmagic;
            sead::FixedSafeString<4> inputmagic;

            inputmagic = expectedmagic;
            inputmagic.format("%s", reslaunchdata->header.magic);
            expectedmagic = "BotW";

            if (inputmagic == expectedmagic.cstr())
                break;
            if (!nn::oe::TryPopLaunchParameter(unknown, reslaunchdata, 0x1000))
                break;
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

void nxargs::allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data) {
    LaunchParamEntry* allEntries;
    LaunchParamEntry* currEntry;
    LaunchParamEntryCondition* currSubEntry;
    LaunchParamEntryCondition* actual_data;
    u64 numEntries = mNumEntries;
    if (mNumEntries == 0)
        return;
    u64 size = numEntries << 6;
    allEntries = new (heap, std::nothrow) LaunchParamEntry;
    if (!allEntries)
        return;
    //if ((((((size - 0x40) >> 6) + 1) & 3) != 0)) {
    //    LaunchParamEntry* launchparams2 = launchparams;
    //}
    //else {
    //    ;
    //}
    //if ( (size - 0x40) >= 0xC0 ) {
    //    
    //}
    if (!mNumEntries)
        return;
    for (u8 i = 0; i < mNumEntries; i++) {
        if (mEntries.getSize() <= i)
            currEntry = mEntries.getBufferPtr();
        else
            currEntry = &mEntries.getBufferPtr()[i];
            
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
        u64 numSubEntries;
        currEntry->mNumConditions = numSubEntries;

        if (!mNumEntries)
            return;
        LaunchParamEntryCondition* subEntries = new (heap, std::nothrow) LaunchParamEntryCondition;
        if (subEntries) {
            actual_data = currEntry->mConditions.getBufferPtr();
            actual_data = subEntries;
        }
        if (currEntry->mNumConditions) {
            for (u8 j = 0; j < currEntry->mNumConditions;) {
                s32 _19 = j++;
                if (currEntry->mConditions.getSize() <= _19) {
                    currSubEntry = currEntry->mConditions.getBufferPtr();
                }
                else {
                    currSubEntry = &currEntry->mConditions.getBufferPtr()[_19];
                }
                    
                currSubEntry->flagnamehash = data->entrydata->mConditions.getBufferPtr()->flagnamehash;
                currSubEntry->flagdatatype = data->entrydata->mConditions.getBufferPtr()->flagdatatype;
                currSubEntry->operation = data->entrydata->mConditions.getBufferPtr()->operation;
                currSubEntry->rhsvalue = data->entrydata->mConditions.getBufferPtr()->rhsvalue;
            }
        }
    }
}

}  // namespace ksys