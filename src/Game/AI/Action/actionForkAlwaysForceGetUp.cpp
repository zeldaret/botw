#include "Game/AI/Action/actionForkAlwaysForceGetUp.h"

namespace uking::action {

ForkAlwaysForceGetUp::ForkAlwaysForceGetUp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkAlwaysForceGetUp::~ForkAlwaysForceGetUp() = default;

bool ForkAlwaysForceGetUp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkAlwaysForceGetUp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkAlwaysForceGetUp::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkAlwaysForceGetUp::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mRotSpdMin_s, "RotSpdMin");
    getStaticParam(&mRotSpdMax_s, "RotSpdMax");
    getStaticParam(&mIsUseCRBOffsetUnit_s, "IsUseCRBOffsetUnit");
    getAITreeVariable(&mCRBOffsetUnit_a, "CRBOffsetUnit");
}

void ForkAlwaysForceGetUp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
