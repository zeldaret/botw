#include "Game/AI/Action/actionHoverPredictVacuumShoot.h"

namespace uking::action {

HoverPredictVacuumShoot::HoverPredictVacuumShoot(const InitArg& arg) : PredictVacuumShoot(arg) {}

HoverPredictVacuumShoot::~HoverPredictVacuumShoot() = default;

bool HoverPredictVacuumShoot::init_(sead::Heap* heap) {
    return PredictVacuumShoot::init_(heap);
}

void HoverPredictVacuumShoot::enter_(ksys::act::ai::InlineParamPack* params) {
    PredictVacuumShoot::enter_(params);
}

void HoverPredictVacuumShoot::leave_() {
    PredictVacuumShoot::leave_();
}

void HoverPredictVacuumShoot::loadParams_() {
    PredictVacuumShoot::loadParams_();
}

void HoverPredictVacuumShoot::calc_() {
    PredictVacuumShoot::calc_();
}

}  // namespace uking::action
