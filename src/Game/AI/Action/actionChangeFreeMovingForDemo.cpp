#include "Game/AI/Action/actionChangeFreeMovingForDemo.h"

namespace uking::action {

ChangeFreeMovingForDemo::ChangeFreeMovingForDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangeFreeMovingForDemo::~ChangeFreeMovingForDemo() = default;

bool ChangeFreeMovingForDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeFreeMovingForDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeFreeMovingForDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeFreeMovingForDemo::loadParams_() {
    getDynamicParam(&mSetFreeMoving_d, "SetFreeMoving");
}

void ChangeFreeMovingForDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
