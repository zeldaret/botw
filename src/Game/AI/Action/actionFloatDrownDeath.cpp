#include "Game/AI/Action/actionFloatDrownDeath.h"

namespace uking::action {

FloatDrownDeath::FloatDrownDeath(const InitArg& arg) : ksys::act::ai::Action(arg) {}

FloatDrownDeath::~FloatDrownDeath() = default;

bool FloatDrownDeath::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void FloatDrownDeath::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void FloatDrownDeath::leave_() {
    ksys::act::ai::Action::leave_();
}

void FloatDrownDeath::loadParams_() {
    getStaticParam(&mFloatDepth_s, "FloatDepth");
    getStaticParam(&mFloatSpeed_s, "FloatSpeed");
    getStaticParam(&mASName_s, "ASName");
}

void FloatDrownDeath::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
