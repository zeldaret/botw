#include "Game/AI/Action/actionForkGolemMaterialASPlay.h"

namespace uking::action {

ForkGolemMaterialASPlay::ForkGolemMaterialASPlay(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkGolemMaterialASPlay::~ForkGolemMaterialASPlay() = default;

bool ForkGolemMaterialASPlay::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGolemMaterialASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGolemMaterialASPlay::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGolemMaterialASPlay::loadParams_() {
    getStaticParam(&mTargetPartType_s, "TargetPartType");
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void ForkGolemMaterialASPlay::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
