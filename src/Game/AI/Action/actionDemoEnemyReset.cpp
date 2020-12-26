#include "Game/AI/Action/actionDemoEnemyReset.h"

namespace uking::action {

DemoEnemyReset::DemoEnemyReset(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoEnemyReset::~DemoEnemyReset() = default;

bool DemoEnemyReset::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoEnemyReset::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoEnemyReset::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoEnemyReset::loadParams_() {}

void DemoEnemyReset::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
