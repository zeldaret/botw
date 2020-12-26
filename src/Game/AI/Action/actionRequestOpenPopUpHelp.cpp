#include "Game/AI/Action/actionRequestOpenPopUpHelp.h"

namespace uking::action {

RequestOpenPopUpHelp::RequestOpenPopUpHelp(const InitArg& arg) : ksys::act::ai::Action(arg) {}

RequestOpenPopUpHelp::~RequestOpenPopUpHelp() = default;

bool RequestOpenPopUpHelp::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RequestOpenPopUpHelp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RequestOpenPopUpHelp::leave_() {
    ksys::act::ai::Action::leave_();
}

void RequestOpenPopUpHelp::loadParams_() {
    getDynamicParam(&mHelpType_d, "HelpType");
}

void RequestOpenPopUpHelp::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
