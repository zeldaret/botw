#include "Game/AI/Action/actionFreeze.h"

namespace uking::action {

Freeze::Freeze(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Freeze::~Freeze() = default;

bool Freeze::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void Freeze::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Freeze::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Freeze::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsChangeInAir_s, "IsChangeInAir");
    getStaticParam(&mTransBoneKey_s, "TransBoneKey");
    getAITreeVariable(&mIsKeepFreeze_a, "IsKeepFreeze");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void Freeze::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
