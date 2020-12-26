#include "Game/AI/Action/actionHorseDie.h"

namespace uking::action {

HorseDie::HorseDie(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HorseDie::~HorseDie() = default;

bool HorseDie::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HorseDie::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HorseDie::leave_() {
    ksys::act::ai::Action::leave_();
}

void HorseDie::loadParams_() {
    getStaticParam(&mDyingFrames_s, "DyingFrames");
    getStaticParam(&mCheckIfStable_s, "CheckIfStable");
    getStaticParam(&mASName_s, "ASName");
}

void HorseDie::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
