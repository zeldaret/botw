#include "Game/AI/Action/actionGuardianSearch.h"

namespace uking::action {

GuardianSearch::GuardianSearch(const InitArg& arg) : GuardianMoveTo(arg) {}

GuardianSearch::~GuardianSearch() = default;

bool GuardianSearch::init_(sead::Heap* heap) {
    return GuardianMoveTo::init_(heap);
}

void GuardianSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianMoveTo::enter_(params);
}

void GuardianSearch::leave_() {
    GuardianMoveTo::leave_();
}

void GuardianSearch::loadParams_() {
    GuardianMoveTo::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mLost_s, "Lost");
}

void GuardianSearch::calc_() {
    GuardianMoveTo::calc_();
}

}  // namespace uking::action
