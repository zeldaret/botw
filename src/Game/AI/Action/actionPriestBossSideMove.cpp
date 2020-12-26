#include "Game/AI/Action/actionPriestBossSideMove.h"

namespace uking::action {

PriestBossSideMove::PriestBossSideMove(const InitArg& arg) : MoveBase(arg) {}

PriestBossSideMove::~PriestBossSideMove() = default;

bool PriestBossSideMove::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void PriestBossSideMove::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void PriestBossSideMove::leave_() {
    MoveBase::leave_();
}

void PriestBossSideMove::loadParams_() {
    MoveBase::loadParams_();
    getStaticParam(&mRotDir_s, "RotDir");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossSideMove::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
