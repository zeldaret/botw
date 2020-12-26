#include "Game/AI/Action/actionCreateDragonChallengeXLink.h"

namespace uking::action {

CreateDragonChallengeXLink::CreateDragonChallengeXLink(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateDragonChallengeXLink::~CreateDragonChallengeXLink() = default;

bool CreateDragonChallengeXLink::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateDragonChallengeXLink::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CreateDragonChallengeXLink::leave_() {
    ksys::act::ai::Action::leave_();
}

void CreateDragonChallengeXLink::loadParams_() {
    getDynamicParam(&mXLinkHandleIndex_d, "XLinkHandleIndex");
}

void CreateDragonChallengeXLink::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
