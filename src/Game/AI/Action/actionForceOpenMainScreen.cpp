#include "Game/AI/Action/actionForceOpenMainScreen.h"

namespace uking::action {

ForceOpenMainScreen::ForceOpenMainScreen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOpenMainScreen::~ForceOpenMainScreen() = default;

bool ForceOpenMainScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceOpenMainScreen::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ForceOpenMainScreen::leave_() {
    ksys::act::ai::Action::leave_();
}

void ForceOpenMainScreen::loadParams_() {}

void ForceOpenMainScreen::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
