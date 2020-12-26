#include "Game/AI/Action/actionWarpMyHorse.h"

namespace uking::action {

WarpMyHorse::WarpMyHorse(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WarpMyHorse::~WarpMyHorse() = default;

bool WarpMyHorse::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WarpMyHorse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WarpMyHorse::leave_() {
    ksys::act::ai::Action::leave_();
}

void WarpMyHorse::loadParams_() {
    getDynamicParam(&mPositionX_d, "PositionX");
    getDynamicParam(&mPositionY_d, "PositionY");
    getDynamicParam(&mPositionZ_d, "PositionZ");
    getDynamicParam(&mDirection_d, "Direction");
}

void WarpMyHorse::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
