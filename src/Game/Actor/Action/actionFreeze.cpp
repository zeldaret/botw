#include "Game/Actor/Action/actionFreeze.h"

namespace uking::action {

Freeze::Freeze(const InitArg& arg) : StopBase(arg) {}

Freeze::~Freeze() = default;

bool Freeze::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void Freeze::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Freeze::leave_() {
    StopBase::leave_();
}

void Freeze::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mIsChangeInAir_s, "IsChangeInAir");
    getStaticParam(&mTransBoneKey_s, "TransBoneKey");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Freeze::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
