#include "Game/AI/Action/actionOpenItemMenu.h"

namespace uking::action {

OpenItemMenu::OpenItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

OpenItemMenu::~OpenItemMenu() = default;

bool OpenItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void OpenItemMenu::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void OpenItemMenu::leave_() {
    ksys::act::ai::Action::leave_();
}

void OpenItemMenu::loadParams_() {
    getDynamicParam(&mMenuType_d, "MenuType");
}

void OpenItemMenu::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
