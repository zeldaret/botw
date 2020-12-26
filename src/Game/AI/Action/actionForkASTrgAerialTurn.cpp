#include "Game/AI/Action/actionForkASTrgAerialTurn.h"

namespace uking::action {

ForkASTrgAerialTurn::ForkASTrgAerialTurn(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForkASTrgAerialTurn::~ForkASTrgAerialTurn() = default;

bool ForkASTrgAerialTurn::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForkASTrgAerialTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForkASTrgAerialTurn::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForkASTrgAerialTurn::loadParams_() {
    getStaticParam(&mPosStayRatio_s, "PosStayRatio");
    getStaticParam(&mRotStayRatio_s, "RotStayRatio");
    getStaticParam(&mAngSpd_s, "AngSpd");
    getDynamicParam(&mTargetPos_d, "TargetPos");
    getStaticParam(&mIsOnASEventChangeable_s, "IsOnASEventChangeable");
    getStaticParam(&mIsUpdateRotSpd_s, "IsUpdateRotSpd");
}

void ForkASTrgAerialTurn::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
