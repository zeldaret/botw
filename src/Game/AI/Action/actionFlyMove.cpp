#include "Game/AI/Action/actionFlyMove.h"

namespace uking::action {

FlyMove::FlyMove(const InitArg& arg) : FlyMoveBase(arg) {}

FlyMove::~FlyMove() = default;

bool FlyMove::init_(sead::Heap* heap) {
    return FlyMoveBase::init_(heap);
}

void FlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    FlyMoveBase::enter_(params);
}

void FlyMove::leave_() {
    FlyMoveBase::leave_();
}

void FlyMove::loadParams_() {
    FlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void FlyMove::calc_() {
    FlyMoveBase::calc_();
}

}  // namespace uking::action
