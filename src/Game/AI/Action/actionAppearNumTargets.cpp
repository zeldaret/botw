#include "Game/AI/Action/actionAppearNumTargets.h"

namespace uking::action {

AppearNumTargets::AppearNumTargets(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AppearNumTargets::~AppearNumTargets() = default;

bool AppearNumTargets::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AppearNumTargets::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AppearNumTargets::leave_() {
    ksys::act::ai::Action::leave_();
}

void AppearNumTargets::loadParams_() {
    getDynamicParam(&mGameDataIntTargetCounter_d, "GameDataIntTargetCounter");
}

void AppearNumTargets::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
