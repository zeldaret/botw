#include "Game/AI/Action/actionAnimalASPlayWithLegTurn.h"

namespace uking::action {

AnimalASPlayWithLegTurn::AnimalASPlayWithLegTurn(const InitArg& arg) : ForkAnimalASPlay(arg) {}

AnimalASPlayWithLegTurn::~AnimalASPlayWithLegTurn() = default;

bool AnimalASPlayWithLegTurn::init_(sead::Heap* heap) {
    return ForkAnimalASPlay::init_(heap);
}

void AnimalASPlayWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkAnimalASPlay::enter_(params);
}

void AnimalASPlayWithLegTurn::leave_() {
    ForkAnimalASPlay::leave_();
}

void AnimalASPlayWithLegTurn::loadParams_() {
    ForkAnimalASPlay::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnimalASPlayWithLegTurn::calc_() {
    ForkAnimalASPlay::calc_();
}

}  // namespace uking::action
