#include "Game/AI/Action/actionCurseRRematchCount.h"

namespace uking::action {

CurseRRematchCount::CurseRRematchCount(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CurseRRematchCount::~CurseRRematchCount() = default;

bool CurseRRematchCount::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CurseRRematchCount::loadParams_() {
    getDynamicParam(&mRematchCount_d, "RematchCount");
    getDynamicParam(&mCurseRType_d, "CurseRType");
    getDynamicParam(&mGameDataStringCounterName_d, "GameDataStringCounterName");
}

}  // namespace uking::action
