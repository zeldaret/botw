#include "Game/AI/Action/actionNoCountDead.h"

namespace uking::action {

NoCountDead::NoCountDead(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NoCountDead::~NoCountDead() = default;

bool NoCountDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NoCountDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NoCountDead::leave_() {
    ksys::act::ai::Action::leave_();
}

void NoCountDead::loadParams_() {
    getStaticParam(&mIsFadeout_s, "IsFadeout");
}

void NoCountDead::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
