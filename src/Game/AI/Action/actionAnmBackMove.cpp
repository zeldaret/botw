#include "Game/AI/Action/actionAnmBackMove.h"

namespace uking::action {

AnmBackMove::AnmBackMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmBackMove::~AnmBackMove() = default;

bool AnmBackMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmBackMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmBackMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmBackMove::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mASName_s, "ASName");
}

void AnmBackMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
