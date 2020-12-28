#include "Game/AI/Action/actionArmorBindNodeAction.h"

namespace uking::action {

ArmorBindNodeAction::ArmorBindNodeAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ArmorBindNodeAction::~ArmorBindNodeAction() = default;

void ArmorBindNodeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ArmorBindNodeAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void ArmorBindNodeAction::loadParams_() {
    getDynamicParam(&mBoneName_d, "BoneName");
    getDynamicParam(&mPosOffset_d, "PosOffset");
    getDynamicParam(&mRotOffsetXyz_d, "RotOffsetXyz");
}

void ArmorBindNodeAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
