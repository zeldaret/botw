#include "Game/AI/Action/actionBolt.h"

namespace uking::action {

Bolt::Bolt(const InitArg& arg) : ksys::act::ai::Action(arg) {}

Bolt::~Bolt() = default;

bool Bolt::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void Bolt::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void Bolt::leave_() {
    ksys::act::ai::Action::leave_();
}

void Bolt::loadParams_() {
    getMapUnitParam(&mIsNoBindAlive_m, "IsNoBindAlive");
}

void Bolt::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
