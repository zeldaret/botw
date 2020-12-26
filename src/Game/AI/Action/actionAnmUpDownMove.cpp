#include "Game/AI/Action/actionAnmUpDownMove.h"

namespace uking::action {

AnmUpDownMove::AnmUpDownMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

AnmUpDownMove::~AnmUpDownMove() = default;

bool AnmUpDownMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AnmUpDownMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AnmUpDownMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void AnmUpDownMove::loadParams_() {
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotReduceRatio_s, "RotReduceRatio");
    getStaticParam(&mAccRatio_s, "AccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void AnmUpDownMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
