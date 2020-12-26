#include "Game/AI/Action/actionASPlaySimpleAnmDriven.h"

namespace uking::action {

ASPlaySimpleAnmDriven::ASPlaySimpleAnmDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ASPlaySimpleAnmDriven::~ASPlaySimpleAnmDriven() = default;

bool ASPlaySimpleAnmDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ASPlaySimpleAnmDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ASPlaySimpleAnmDriven::leave_() {
    ksys::act::ai::Action::leave_();
}

void ASPlaySimpleAnmDriven::loadParams_() {
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mResetTransBoneOnLeave_s, "ResetTransBoneOnLeave");
    getStaticParam(&mASName_s, "ASName");
}

void ASPlaySimpleAnmDriven::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
