#include "Game/AI/Action/actionAnmDrivenHoverBase.h"

namespace uking::action {

AnmDrivenHoverBase::AnmDrivenHoverBase(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDrivenHoverBase::~AnmDrivenHoverBase() = default;

bool AnmDrivenHoverBase::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmDrivenHoverBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmDrivenHoverBase::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDrivenHoverBase::loadParams_() {
    getStaticParam(&mMoveYLimit_s, "MoveYLimit");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mASName_s, "ASName");
    getDynamicParam(&mBaseHeight_d, "BaseHeight");
}

void AnmDrivenHoverBase::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
