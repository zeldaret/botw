#include "Game/AI/Action/actionCurseRRematchCount.h"

namespace uking::action {

CurseRRematchCount::CurseRRematchCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CurseRRematchCount::~CurseRRematchCount() = default;

bool CurseRRematchCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CurseRRematchCount::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CurseRRematchCount::leave_() {
    ksys::act::ai::Action::leave_();
}

void CurseRRematchCount::loadParams_() {
    getDynamicParam(&mRematchCount_d, "RematchCount");
    getDynamicParam(&mCurseRType_d, "CurseRType");
    getDynamicParam(&mGameDataStringCounterName_d, "GameDataStringCounterName");
}

void CurseRRematchCount::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
