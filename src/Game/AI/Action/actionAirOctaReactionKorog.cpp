#include "Game/AI/Action/actionAirOctaReactionKorog.h"

namespace uking::action {

AirOctaReactionKorog::AirOctaReactionKorog(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AirOctaReactionKorog::~AirOctaReactionKorog() = default;

bool AirOctaReactionKorog::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AirOctaReactionKorog::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AirOctaReactionKorog::leave_() {
    ksys::act::ai::Action::leave_();
}

void AirOctaReactionKorog::loadParams_() {
    getStaticParam(&mEndState_s, "EndState");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mAS_s, "AS");
}

void AirOctaReactionKorog::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
