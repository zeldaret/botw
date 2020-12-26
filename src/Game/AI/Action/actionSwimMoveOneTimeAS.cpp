#include "Game/AI/Action/actionSwimMoveOneTimeAS.h"

namespace uking::action {

SwimMoveOneTimeAS::SwimMoveOneTimeAS(const InitArg& arg) : SwimMoveBase(arg) {}

SwimMoveOneTimeAS::~SwimMoveOneTimeAS() = default;

bool SwimMoveOneTimeAS::init_(sead::Heap* heap) {
    return SwimMoveBase::init_(heap);
}

void SwimMoveOneTimeAS::enter_(ksys::act::ai::InlineParamPack* params) {
    SwimMoveBase::enter_(params);
}

void SwimMoveOneTimeAS::leave_() {
    SwimMoveBase::leave_();
}

void SwimMoveOneTimeAS::loadParams_() {
    SwimMoveBase::loadParams_();
    getStaticParam(&mIsIgnoreSameKey_s, "IsIgnoreSameKey");
    getStaticParam(&mASName_s, "ASName");
}

void SwimMoveOneTimeAS::calc_() {
    SwimMoveBase::calc_();
}

}  // namespace uking::action
