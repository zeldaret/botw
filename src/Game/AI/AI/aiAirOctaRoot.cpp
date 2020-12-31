#include "Game/AI/AI/aiAirOctaRoot.h"

namespace uking::ai {

AirOctaRoot::AirOctaRoot(const InitArg& arg) : Fork2AI(arg) {}

AirOctaRoot::~AirOctaRoot() = default;

bool AirOctaRoot::init_(sead::Heap* heap) {
    return Fork2AI::init_(heap);
}

void AirOctaRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    Fork2AI::enter_(params);
}

void AirOctaRoot::leave_() {
    Fork2AI::leave_();
}

void AirOctaRoot::loadParams_() {
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
