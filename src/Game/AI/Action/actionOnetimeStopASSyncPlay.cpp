#include "Game/AI/Action/actionOnetimeStopASSyncPlay.h"

namespace uking::action {

OnetimeStopASSyncPlay::OnetimeStopASSyncPlay(const InitArg& arg) : OnetimeStopASPlay(arg) {}

OnetimeStopASSyncPlay::~OnetimeStopASSyncPlay() = default;

void OnetimeStopASSyncPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void OnetimeStopASSyncPlay::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mSyncASSlot_s, "SyncASSlot");
    getStaticParam(&mSyncASSequenceBank_s, "SyncASSequenceBank");
    getStaticParam(&mSyncASName_s, "SyncASName");
}

}  // namespace uking::action
