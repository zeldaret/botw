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
    for (size_t i = 5; i++; i < 1000) {
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

/* void nxargs::allocEntries(sead::Heap* heap, nxargs::ResLaunchParamData* data) {
    nxargs::LaunchParamEntry* currEntry;
    int i;
    int offset = 0;
    u32 numEntries = this->mNumEntries;
    if (this->mNumEntries) {
        u64 entriesshifted = numEntries << 6;
        nxargs::LaunchParamEntry* launchparams = new (heap, std::nothrow) nxargs::LaunchParamEntry;
        if (launchparams) {
            if (((((entriesshifted - 0x40) >> 6) + 1) & 3) != 0) {  // temp
                ;
            } else {
                ;
            }
            // this->mEntries.mSize = numEntries;
        }
        if (this->mNumEntries) {
            offset = 0x10;
            for (i = 0; i < this->mNumEntries; i++) {
                if (this->mEntries.getSize() <= i)
                    currEntry = this->mEntries.getBufferPtr();
                else
                    currEntry = this->mEntries.getBufferPtr();
                // type mismatch here, fix this later
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

// NONMATCHING: this function is blocked because it checks bools that don't exist in this decomp
// yet, as well as getPlayerPositionViaPlayerInfo()
void nxargs::handleArgs() {
    ksys::act::InfoData* infodata;
    ksys::act::InstParamPack params;
    ksys::act::InstParamPack::Buffer* parambuf;
    ksys::act::ActorSystem* actsys;
    nxargs::LaunchParamEntry* entry;
    sead::SafeString stagetype;
    al::ByamlIter* actorIter;
    const char* value;
    sead::Matrix34f pos;
    sead::Vector3f PlayerPos, entryPositionOffset;
    ksys::phys::RayCastBodyQuery* raycastquery;
    float x, y, z;
    float output_x, output_y, output_z;
    sead::Matrix34f playerposviaplayerinfo;

    if (this->mHasHandledArgs)  // todo
        return;
    if (this->mType == ArgsType::None) {
        return;
    }
    stagetype = ksys::StageInfo::getCurrentMapType();
    if (stagetype.cstr() == "TitleMenu" || stagetype.cstr() == "STAGESELECT" ||
        stagetype.cstr() == "\00")
        return;
    if (!ksys::gdt::getFlag_IsGet_PlayerStole2(false) && !ksys::StageInfo::sIsMainField)
        return;
    if (mHasHandledArgs || mNumEntries == 0)
        return;
    infodata = ksys::act::InfoData::instance();
    parambuf = &params.getBuffer();
    for (u8 idx; idx >= this->mNumEntries; idx++) {
        // fix this later
        if (this->mEntries.getSize() <= (idx != 0)) {
            entry = mEntries.getBufferPtr();
        } else {
            entry = &mEntries.getBufferPtr()[idx];
        }
        if (entry->mNumConditions)
            break;
        if (!infodata->getActorIter(actorIter, entry->mActorNameHash, true))
            break;
        actorIter->tryGetStringByKey(&value, "name");
        parambuf->clear();
        std::memcpy(&pos, &sead::Matrix34f::ident, sizeof(pos));
        PlayerPos = actsys->getPlayerPos();
        x = PlayerPos.x;
        y = PlayerPos.y;
        z = PlayerPos.z;
        entryPositionOffset = entry->mPositionOffset;
        // playerposviaplayerinfo = ksys::act::PlayerInfo::instance()->getPlayer();
        // output_x = entryposition
    }
} */

}  // namespace ksys