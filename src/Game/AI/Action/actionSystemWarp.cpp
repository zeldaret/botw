#include "Game/AI/Action/actionSystemWarp.h"

namespace uking::action {

SystemWarp::SystemWarp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemWarp::~SystemWarp() = default;

bool SystemWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemWarp::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemWarp::loadParams_() {
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SystemWarp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
