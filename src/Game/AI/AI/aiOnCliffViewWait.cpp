#include "Game/AI/AI/aiOnCliffViewWait.h"

namespace uking::ai {

OnCliffViewWait::OnCliffViewWait(const InitArg& arg) : ViewWait(arg) {}

OnCliffViewWait::~OnCliffViewWait() = default;

bool OnCliffViewWait::init_(sead::Heap* heap) {
    return ViewWait::init_(heap);
}

void OnCliffViewWait::enter_(ksys::act::ai::InlineParamPack* params) {
    ViewWait::enter_(params);
}

void OnCliffViewWait::leave_() {
    ViewWait::leave_();
}

void OnCliffViewWait::loadParams_() {
    ViewWait::loadParams_();
    getMapUnitParam(&mOnCliffTurn_m, "OnCliffTurn");
}

}  // namespace uking::ai
