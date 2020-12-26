#include "Game/AI/Action/actionCloseArmorProcessing.h"

namespace uking::action {

CloseArmorProcessing::CloseArmorProcessing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseArmorProcessing::~CloseArmorProcessing() = default;

bool CloseArmorProcessing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseArmorProcessing::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CloseArmorProcessing::leave_() {
    ksys::act::ai::Action::leave_();
}

void CloseArmorProcessing::loadParams_() {}

void CloseArmorProcessing::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
