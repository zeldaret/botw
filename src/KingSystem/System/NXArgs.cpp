#include "KingSystem/System/NXArgs.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(nxargs)

// WIP
void nxargs::init(sead::Heap* heap) {
    sead::SafeString heapname = "nxargsHeap";
    sead::Heap* nxargsheap = nullptr;
    const u64 sizeofargs = 0x1000;
    //auto* unk = nullptr;

    nxargsheap = sead::ExpHeap::create(0x13E8, heapname, heap, (u32)8,
                                       sead::ExpHeap::HeapDirection::cHeapDirection_Reverse, false);
    nxargs::ResLaunchParamData* reslaunchdata = new (nxargsheap) nxargs::ResLaunchParamData;

    if (!nn::oe::TryPopLaunchParameter(nullptr, reslaunchdata, sizeofargs))
        return;
    for (int len; len++; len < 1000) {
        sead::FixedSafeString<5> inputmagic;
        sead::SafeString expectedmagic = "\00";
        u64 *unk;

        inputmagic = expectedmagic;

        inputmagic.format("%s", reslaunchdata->header.magic);
        expectedmagic = "BotW";
        bool isMagicMatch = (inputmagic.cstr() == expectedmagic.cstr());
        if (isMagicMatch)
            break;
        bool poplaunchparamresult = nn::oe::TryPopLaunchParameter(unk, reslaunchdata, sizeofargs);
        if (poplaunchparamresult)
            break;
    }
    this->mResField4 = reslaunchdata->header._4;
    this->mResField6 = reslaunchdata->header._6;
    argstype type = reslaunchdata->header.type;
    this->mType = type;
    if (type == argstype::TypeCreateActors) {
        this->mNumEntries = reslaunchdata->header.numentries;
        nxargs::allocEntries(heap, reslaunchdata);
    } else {
        this->mType = argstype::TypeNone;
    }
    heap->destroy();
}

void nxargs::allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data) {
    nxargs::LaunchParamEntry* currEntry;
    int i;
    int offset = 0;
    u8 numEntries = this->mNumEntries;
    if (this->mNumEntries) {
        u64 entriesshifted = numEntries << 6;
        nxargs::LaunchParamEntry* launchparams = new (heap, std::nothrow) nxargs::LaunchParamEntry;
        if (launchparams) {
            if (((((entriesshifted - 0x40) >> 6) + 1) & 3) != 0) {  // temp
                ;
            } else {
                ;
            }
        }
        if (this->mNumEntries) {
            offset = 0x10;
            for (i - 0; i < this->mNumEntries; i++) {
                if (this->mEntries.getSize() <= i)
                    currEntry = this->mEntries.getBufferPtr();
                else
                    ;
                //type mismatch here, fix this later
                // currEntry->mActorNameHash = data->mActorNameHash;
                // currEntry->mDropActorNameHash = data->mDropActorNameHash;
                // currEntry->mPositionOffset.x = data->mPositionOffset.x;
                // currEntry->mPositionOffset.y = data->mPositionOffset.y;
                // currEntry->mPositionOffset.z = data->mPositionOffset.z;
                // currEntry->mRotate.x = data->mPositionOffset.x;
                // currEntry->mRotate.y = data->mPositionOffset.y;
                // currEntry->mRotate.z = data->mPositionOffset.z;
                // currEntry->mVelocity.x = data->mVelocity.x;
                // currEntry->mVelocity.y = data->mVelocity.y;
                // currEntry->mVelocity.z = data->mVelocity.z;
                // currEntry->mFlags = data->mFlags;
            }
        }
    }
}

// NONMATCHING: this function checks bools that don't exist in this decomp yet
void nxargs::handleArgs() {
    sead::SafeString stagetype;
    if (this->mHasHandledArgs)  // todo
        return;
    if (this->mType == argstype::TypeNone) {
        return;
    }
    stagetype = ksys::StageInfo::getCurrentMapType();
    if (stagetype.cstr() == "TitleMenu" || stagetype.cstr() == "STAGESELECT" ||
        stagetype.cstr() == "\00")
        return;
    if (ksys::gdt::getFlag_IsGet_PlayerStole2(false) && ksys::StageInfo::sIsMainField) {
        ;
    }
    
}

}  // namespace ksys