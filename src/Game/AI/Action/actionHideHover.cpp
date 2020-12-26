#include "Game/AI/Action/actionHideHover.h"

namespace uking::action {

HideHover::HideHover(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HideHover::~HideHover() = default;

bool HideHover::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HideHover::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HideHover::leave_() {
    ksys::act::ai::Action::leave_();
}

void HideHover::loadParams_() {
    getStaticParam(&mTimer_s, "Timer");
    getStaticParam(&mEffectName_s, "EffectName");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsKeepLifeGage_s, "IsKeepLifeGage");
}

void HideHover::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
