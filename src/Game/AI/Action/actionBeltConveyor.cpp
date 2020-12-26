#include "Game/AI/Action/actionBeltConveyor.h"

namespace uking::action {

BeltConveyor::BeltConveyor(const InitArg& arg) : ksys::act::ai::Action(arg) {}

BeltConveyor::~BeltConveyor() = default;

bool BeltConveyor::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void BeltConveyor::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void BeltConveyor::leave_() {
    ksys::act::ai::Action::leave_();
}

void BeltConveyor::loadParams_() {
    getStaticParam(&mASRate_s, "ASRate");
    getStaticParam(&mIsReverse_s, "IsReverse");
    getStaticParam(&mASName_s, "ASName");
    getMapUnitParam(&mRotateSpeed_m, "RotateSpeed");
}

void BeltConveyor::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
