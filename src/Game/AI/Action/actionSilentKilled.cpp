#include "Game/AI/Action/actionSilentKilled.h"

namespace uking::action {

SilentKilled::SilentKilled(const InitArg& arg) : Ragdoll(arg) {}

SilentKilled::~SilentKilled() = default;

bool SilentKilled::init_(sead::Heap* heap) {
    return Ragdoll::init_(heap);
}

void SilentKilled::enter_(ksys::act::ai::InlineParamPack* params) {
    Ragdoll::enter_(params);
}

void SilentKilled::leave_() {
    Ragdoll::leave_();
}

void SilentKilled::loadParams_() {
    Ragdoll::loadParams_();
}

void SilentKilled::calc_() {
    Ragdoll::calc_();
}

}  // namespace uking::action
