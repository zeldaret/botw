#include "Game/AI/Action/actionDemoDelete.h"

namespace uking::action {

DemoDelete::DemoDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DemoDelete::~DemoDelete() = default;

bool DemoDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoDelete::loadParams_() {}

void DemoDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
