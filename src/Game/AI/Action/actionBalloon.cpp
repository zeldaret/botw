#include "Game/AI/Action/actionBalloon.h"

namespace uking::action {

Balloon::Balloon(const InitArg& arg) : BalloonBase(arg) {}

Balloon::~Balloon() = default;

bool Balloon::init_(sead::Heap* heap) {
    return BalloonBase::init_(heap);
}

void Balloon::enter_(ksys::act::ai::InlineParamPack* params) {
    BalloonBase::enter_(params);
}

void Balloon::leave_() {
    BalloonBase::leave_();
}

void Balloon::loadParams_() {
    BalloonBase::loadParams_();
    getStaticParam(&mLength_s, "Length");
    getStaticParam(&mRopeActorName_s, "RopeActorName");
    getMapUnitParam(&mRopeHungActOffset_m, "RopeHungActOffset");
}

void Balloon::calc_() {
    BalloonBase::calc_();
}

}  // namespace uking::action
