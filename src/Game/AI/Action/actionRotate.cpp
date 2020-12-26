#include "Game/AI/Action/actionRotate.h"

namespace uking::action {

Rotate::Rotate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Rotate::~Rotate() = default;

bool Rotate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Rotate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Rotate::leave_() {
    ksys::act::ai::Action::leave_();
}

void Rotate::loadParams_() {
    getStaticParam(&mIsReturn_s, "IsReturn");
    getMapUnitParam(&mRotAxis_m, "RotAxis");
    getMapUnitParam(&mTiltAngle_m, "TiltAngle");
    getMapUnitParam(&mTiltAngularSpeed_m, "TiltAngularSpeed");
}

void Rotate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
