#include "Game/AI/Action/actionCloseItemMenu.h"

namespace uking::action {

CloseItemMenu::CloseItemMenu(const InitArg& arg) : ksys::act::ai::Action(arg) {}

CloseItemMenu::~CloseItemMenu() = default;

bool CloseItemMenu::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void CloseItemMenu::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void CloseItemMenu::leave_() {
    ksys::act::ai::Action::leave_();
}

void CloseItemMenu::loadParams_() {}

void CloseItemMenu::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
