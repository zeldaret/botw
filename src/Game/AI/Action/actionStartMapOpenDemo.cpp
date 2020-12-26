#include "Game/AI/Action/actionStartMapOpenDemo.h"

namespace uking::action {

StartMapOpenDemo::StartMapOpenDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartMapOpenDemo::~StartMapOpenDemo() = default;

bool StartMapOpenDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartMapOpenDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartMapOpenDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartMapOpenDemo::loadParams_() {
    getDynamicParam(&mIsPlayerClose_d, "IsPlayerClose");
}

void StartMapOpenDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
