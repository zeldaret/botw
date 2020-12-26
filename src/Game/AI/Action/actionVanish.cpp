#include "Game/AI/Action/actionVanish.h"

namespace uking::action {

Vanish::Vanish(const InitArg& arg) : TimeredASPlay(arg) {}

Vanish::~Vanish() = default;

bool Vanish::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void Vanish::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void Vanish::leave_() {
    TimeredASPlay::leave_();
}

void Vanish::loadParams_() {
    TimeredASPlay::loadParams_();
    getStaticParam(&mDieType_s, "DieType");
    getStaticParam(&mNoDrop_s, "NoDrop");
}

void Vanish::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action
