#include "Game/AI/AI/aiAirOctaBoardBurn.h"

namespace uking::ai {

AirOctaBoardBurn::AirOctaBoardBurn(const InitArg& arg) : SeqTwoAction(arg) {}

AirOctaBoardBurn::~AirOctaBoardBurn() = default;

bool AirOctaBoardBurn::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void AirOctaBoardBurn::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void AirOctaBoardBurn::leave_() {
    SeqTwoAction::leave_();
}

void AirOctaBoardBurn::loadParams_() {
    SeqTwoAction::loadParams_();
    getAITreeVariable(&mAirOctaDataMgr_a, "AirOctaDataMgr");
}

}  // namespace uking::ai
