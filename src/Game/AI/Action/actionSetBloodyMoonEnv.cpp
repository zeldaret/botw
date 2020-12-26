#include "Game/AI/Action/actionSetBloodyMoonEnv.h"

namespace uking::action {

SetBloodyMoonEnv::SetBloodyMoonEnv(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SetBloodyMoonEnv::~SetBloodyMoonEnv() = default;

bool SetBloodyMoonEnv::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SetBloodyMoonEnv::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SetBloodyMoonEnv::leave_() {
    ksys::act::ai::Action::leave_();
}

void SetBloodyMoonEnv::loadParams_() {}

void SetBloodyMoonEnv::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
