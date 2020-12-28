#include "Game/AI/Action/actionForceOpenMainScreen.h"

namespace uking::action {

ForceOpenMainScreen::ForceOpenMainScreen(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ForceOpenMainScreen::~ForceOpenMainScreen() = default;

bool ForceOpenMainScreen::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ForceOpenMainScreen::loadParams_() {}

}  // namespace uking::action
