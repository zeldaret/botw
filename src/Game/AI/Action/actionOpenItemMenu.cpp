#include "Game/AI/Action/actionOpenItemMenu.h"

namespace uking::action {

OpenItemMenu::OpenItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemMenu::~OpenItemMenu() = default;

bool OpenItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemMenu::loadParams_() {
    getDynamicParam(&mMenuType_d, "MenuType");
}

}  // namespace uking::action
