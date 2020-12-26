#include "Game/AI/Action/actionOpenPorch.h"

namespace uking::action {

OpenPorch::OpenPorch(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenPorch::~OpenPorch() = default;

bool OpenPorch::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenPorch::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenPorch::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenPorch::loadParams_() {
    getDynamicParam(&mRockCategory_d, "RockCategory");
}

void OpenPorch::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
