#include "Game/AI/Action/actionNPCLerpAction.h"

namespace uking::action {

NPCLerpAction::NPCLerpAction(const InitArg& arg) : ksys::act::ai::Action(arg) {}

NPCLerpAction::~NPCLerpAction() = default;

void NPCLerpAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCLerpAction::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCLerpAction::loadParams_() {
    getStaticParam(&mRotateSpeed_s, "RotateSpeed");
    getStaticParam(&mArriveDist_s, "ArriveDist");
    getStaticParam(&mIsRotateByRot_s, "IsRotateByRot");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getDynamicParam(&mTargetRot_d, "TargetRot");
}

void NPCLerpAction::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
