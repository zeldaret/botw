#include "Game/AI/Action/actionForkGanonBeastAppearHolyWall.h"

namespace uking::action {

ForkGanonBeastAppearHolyWall::ForkGanonBeastAppearHolyWall(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ForkGanonBeastAppearHolyWall::~ForkGanonBeastAppearHolyWall() = default;

bool ForkGanonBeastAppearHolyWall::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkGanonBeastAppearHolyWall::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkGanonBeastAppearHolyWall::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkGanonBeastAppearHolyWall::loadParams_() {
    getStaticParam(&mShowDist_s, "ShowDist");
    getStaticParam(&mAppearDist_s, "AppearDist");
    getStaticParam(&mEffectYOffset_s, "EffectYOffset");
    getStaticParam(&mUiDist_s, "UiDist");
    getStaticParam(&mKeyName_s, "KeyName");
    getStaticParam(&mBasePos_s, "BasePos");
}

void ForkGanonBeastAppearHolyWall::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
