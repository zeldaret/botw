#include "Game/AI/Action/actionCreateDragonChallengeXLink.h"

namespace uking::action {

CreateDragonChallengeXLink::CreateDragonChallengeXLink(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

CreateDragonChallengeXLink::~CreateDragonChallengeXLink() = default;

bool CreateDragonChallengeXLink::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CreateDragonChallengeXLink::loadParams_() {
    getDynamicParam(&mXLinkHandleIndex_d, "XLinkHandleIndex");
}

}  // namespace uking::action
