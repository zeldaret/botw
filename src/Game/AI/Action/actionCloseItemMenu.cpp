#include "Game/AI/Action/actionCloseItemMenu.h"

namespace uking::action {

CloseItemMenu::CloseItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseItemMenu::~CloseItemMenu() = default;

bool CloseItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseItemMenu::loadParams_() {}

}  // namespace uking::action
