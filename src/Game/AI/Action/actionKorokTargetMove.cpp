#include "Game/AI/Action/actionKorokTargetMove.h"

namespace uking::action {

KorokTargetMove::KorokTargetMove(const InitArg& arg) : ksys::act::ai::Action(arg) {}

KorokTargetMove::~KorokTargetMove() = default;

bool KorokTargetMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void KorokTargetMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void KorokTargetMove::leave_() {
    ksys::act::ai::Action::leave_();
}

void KorokTargetMove::loadParams_() {
    getDynamicParam(&mSpeed_d, "Speed");
    getDynamicParam(&mIsBezier_d, "IsBezier");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getMapUnitParam(&mIsTargetWarp_m, "IsTargetWarp");
}

void KorokTargetMove::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
