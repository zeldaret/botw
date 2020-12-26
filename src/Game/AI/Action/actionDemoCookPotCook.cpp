#include "Game/AI/Action/actionDemoCookPotCook.h"

namespace uking::action {

DemoCookPotCook::DemoCookPotCook(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoCookPotCook::~DemoCookPotCook() = default;

bool DemoCookPotCook::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoCookPotCook::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoCookPotCook::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoCookPotCook::loadParams_() {
    getStaticParam(&mMaterialTargetBone_s, "MaterialTargetBone");
    getStaticParam(&mFairyTargetBone_s, "FairyTargetBone");
    getDynamicParam(&mIsSuccess_d, "IsSuccess");
    getAITreeVariable(&mCurrentCookResultHolder_a, "CurrentCookResultHolder");
}

void DemoCookPotCook::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
