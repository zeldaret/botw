#include "Game/AI/Action/actionRequestOpenPopUpHelp.h"

namespace uking::action {

RequestOpenPopUpHelp::RequestOpenPopUpHelp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestOpenPopUpHelp::~RequestOpenPopUpHelp() = default;

bool RequestOpenPopUpHelp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestOpenPopUpHelp::loadParams_() {
    getDynamicParam(&mHelpType_d, "HelpType");
}

}  // namespace uking::action
