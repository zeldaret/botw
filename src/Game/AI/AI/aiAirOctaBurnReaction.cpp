#include "Game/AI/AI/aiAirOctaBurnReaction.h"

namespace uking::ai {

AirOctaBurnReaction::AirOctaBurnReaction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AirOctaBurnReaction::~AirOctaBurnReaction() = default;

bool AirOctaBurnReaction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AirOctaBurnReaction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AirOctaBurnReaction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AirOctaBurnReaction::loadParams_() {
    getStaticParam(&mDisconnectTime_s, "DisconnectTime");
    getStaticParam(&mDisconnectRandTime_s, "DisconnectRandTime");
    getStaticParam(&mSingleBurnTime_s, "SingleBurnTime");
    getStaticParam(&mChangeRandTime_s, "ChangeRandTime");
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
