#include "Game/AI/Action/actionOnetimeStopASSyncPlay.h"

namespace uking::action {

OnetimeStopASSyncPlay::OnetimeStopASSyncPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeStopASSyncPlay::~OnetimeStopASSyncPlay() = default;

bool OnetimeStopASSyncPlay::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void OnetimeStopASSyncPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void OnetimeStopASSyncPlay::leave_() {
    OnetimeStopASPlay::leave_();
}

void OnetimeStopASSyncPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mSyncASSlot_s, "SyncASSlot");
    getStaticParam(&mSyncASSequenceBank_s, "SyncASSequenceBank");
    getStaticParam(&mSyncASName_s, "SyncASName");
}

void OnetimeStopASSyncPlay::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
