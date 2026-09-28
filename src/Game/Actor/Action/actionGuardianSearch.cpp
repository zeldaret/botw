#include "Game/Actor/Action/actionGuardianSearch.h"

namespace uking::action {

GuardianSearch::GuardianSearch(const InitArg& arg) : GuardianActionBase(arg) {}

GuardianSearch::~GuardianSearch() = default;

bool GuardianSearch::init_(sead::Heap* heap) {
    return GuardianActionBase::init_(heap);
}

void GuardianSearch::enter_(ksys::act::ai::InlineParamPack* params) {
    GuardianActionBase::enter_(params);
}

void GuardianSearch::leave_() {
    GuardianActionBase::leave_();
}

void GuardianSearch::loadParams_() {
    GuardianActionBase::loadParams_();
    getStaticParam(&mWaitFrame_s, "WaitFrame");
    getStaticParam(&mLost_s, "Lost");
}

void GuardianSearch::calc_() {
    GuardianActionBase::calc_();
}

}  // namespace uking::action
