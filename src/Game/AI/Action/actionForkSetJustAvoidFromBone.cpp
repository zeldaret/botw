#include "Game/AI/Action/actionForkSetJustAvoidFromBone.h"

namespace uking::action {

ForkSetJustAvoidFromBone::ForkSetJustAvoidFromBone(const InitArg& arg) : ForkSetJustAvoid(arg) {}

ForkSetJustAvoidFromBone::~ForkSetJustAvoidFromBone() = default;

bool ForkSetJustAvoidFromBone::init_(sead::Heap* heap) {
    return ForkSetJustAvoid::init_(heap);
}

void ForkSetJustAvoidFromBone::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkSetJustAvoid::enter_(params);
}

void ForkSetJustAvoidFromBone::leave_() {
    ForkSetJustAvoid::leave_();
}

void ForkSetJustAvoidFromBone::loadParams_() {
    ForkSetJustAvoid::loadParams_();
    getStaticParam(&mTransBaseBoneName_s, "TransBaseBoneName");
    getStaticParam(&mRotBaseBoneName_s, "RotBaseBoneName");
    getStaticParam(&mBaseDir_s, "BaseDir");
}

void ForkSetJustAvoidFromBone::calc_() {
    ForkSetJustAvoid::calc_();
}

}  // namespace uking::action
