#include "Game/AI/Action/actionAnmDrivenHoverTurn.h"

namespace uking::action {

AnmDrivenHoverTurn::AnmDrivenHoverTurn(const InitArg& arg) : AnmDrivenHoverBase(arg) {}

AnmDrivenHoverTurn::~AnmDrivenHoverTurn() = default;

bool AnmDrivenHoverTurn::init_(sead::Heap* heap) {
    return AnmDrivenHoverBase::init_(heap);
}

void AnmDrivenHoverTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    AnmDrivenHoverBase::enter_(params);
}

void AnmDrivenHoverTurn::leave_() {
    AnmDrivenHoverBase::leave_();
}

void AnmDrivenHoverTurn::loadParams_() {
    AnmDrivenHoverBase::loadParams_();
    getStaticParam(&mRotSpeed_s, "RotSpeed");
    getStaticParam(&mBaseRotRatio_s, "BaseRotRatio");
    getStaticParam(&mRotAccRatio_s, "RotAccRatio");
    getStaticParam(&mFinRotate_s, "FinRotate");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void AnmDrivenHoverTurn::calc_() {
    AnmDrivenHoverBase::calc_();
}

}  // namespace uking::action
