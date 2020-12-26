#include "Game/AI/Action/actionHorseSwimAction.h"

namespace uking::action {

HorseSwimAction::HorseSwimAction(const InitArg& arg) : HorseSwim(arg) {}

HorseSwimAction::~HorseSwimAction() = default;

bool HorseSwimAction::init_(sead::Heap* heap) {
    return HorseSwim::init_(heap);
}

void HorseSwimAction::enter_(ksys::act::ai::InlineParamPack* params) {
    HorseSwim::enter_(params);
}

void HorseSwimAction::leave_() {
    HorseSwim::leave_();
}

void HorseSwimAction::loadParams_() {
    HorseSwim::loadParams_();
    getStaticParam(&mLandSearchRadius_s, "LandSearchRadius");
    getStaticParam(&mLandSearchNormalCos_s, "LandSearchNormalCos");
    getStaticParam(&mLandSearchMinArea_s, "LandSearchMinArea");
    getStaticParam(&mLandSearchIntervalFrames_s, "LandSearchIntervalFrames");
    getStaticParam(&mResolvePenetrationRadiusScale_s, "ResolvePenetrationRadiusScale");
    getStaticParam(&mResolvePenetrationSearchRadius_s, "ResolvePenetrationSearchRadius");
}

void HorseSwimAction::calc_() {
    HorseSwim::calc_();
}

}  // namespace uking::action
