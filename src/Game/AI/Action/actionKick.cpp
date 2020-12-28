#include "Game/AI/Action/actionKick.h"

namespace uking::action {

Kick::Kick(const InitArg& arg) : ActionEx(arg) {}

Kick::~Kick() = default;

bool Kick::init_(sead::Heap* heap) {
    return ActionEx::init_(heap);
}

void Kick::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionEx::enter_(params);
}

void Kick::loadParams_() {
    getStaticParam(&mPower_s, "Power");
    getStaticParam(&mUpRate_s, "UpRate");
    getStaticParam(&mDirAngle_s, "DirAngle");
    getStaticParam(&mCanKickArea_s, "CanKickArea");
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getDynamicParam(&mTargetActor_d, "TargetActor");
}

void Kick::calc_() {
    ActionEx::calc_();
}

}  // namespace uking::action
