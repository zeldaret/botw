#include "Game/Actor/Action/actionGiantArmorAction.h"

namespace uking::action {

GiantArmorAction::GiantArmorAction(const InitArg& arg) : StopBase(arg) {}

GiantArmorAction::~GiantArmorAction() = default;

bool GiantArmorAction::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void GiantArmorAction::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void GiantArmorAction::leave_() {
    StopBase::leave_();
}

void GiantArmorAction::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mUseRestart_s, "UseRestart");
    getStaticParam(&mStartAS_s, "StartAS");
    getStaticParam(&mLoopAS_s, "LoopAS");
    getStaticParam(&mEndAS_s, "EndAS");
}

void GiantArmorAction::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
