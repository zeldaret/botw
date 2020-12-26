#include "Game/AI/Action/actionInvisibleKorokMove.h"

namespace uking::action {

InvisibleKorokMove::InvisibleKorokMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

InvisibleKorokMove::~InvisibleKorokMove() = default;

bool InvisibleKorokMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void InvisibleKorokMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void InvisibleKorokMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void InvisibleKorokMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mIsBezier_d, "IsBezier");
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void InvisibleKorokMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
