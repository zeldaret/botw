#include "Game/AI/Action/actionStartHeartDemo.h"

namespace uking::action {

StartHeartDemo::StartHeartDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartHeartDemo::~StartHeartDemo() = default;

bool StartHeartDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartHeartDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartHeartDemo::leave_() {
    ksys::act::ai::Action::leave_();
}

void StartHeartDemo::loadParams_() {}

void StartHeartDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
