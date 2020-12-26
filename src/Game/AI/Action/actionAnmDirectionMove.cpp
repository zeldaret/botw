#include "Game/AI/Action/actionAnmDirectionMove.h"

namespace uking::action {

AnmDirectionMove::AnmDirectionMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmDirectionMove::~AnmDirectionMove() = default;

bool AnmDirectionMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmDirectionMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmDirectionMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmDirectionMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mUsereachableCheck_s, "UsereachableCheck");
    getStaticParam(&mASName_s, "ASName");
}

void AnmDirectionMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
