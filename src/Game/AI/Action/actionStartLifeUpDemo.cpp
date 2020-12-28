#include "Game/AI/Action/actionStartLifeUpDemo.h"

namespace uking::action {

StartLifeUpDemo::StartLifeUpDemo(const InitArg& arg) : ksys::act::ai::Action(arg) {}

StartLifeUpDemo::~StartLifeUpDemo() = default;

bool StartLifeUpDemo::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void StartLifeUpDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void StartLifeUpDemo::loadParams_() {}

void StartLifeUpDemo::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
