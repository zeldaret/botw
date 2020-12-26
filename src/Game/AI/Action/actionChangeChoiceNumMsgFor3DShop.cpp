#include "Game/AI/Action/actionChangeChoiceNumMsgFor3DShop.h"

namespace uking::action {

ChangeChoiceNumMsgFor3DShop::ChangeChoiceNumMsgFor3DShop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ChangeChoiceNumMsgFor3DShop::~ChangeChoiceNumMsgFor3DShop() = default;

bool ChangeChoiceNumMsgFor3DShop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeChoiceNumMsgFor3DShop::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ChangeChoiceNumMsgFor3DShop::leave_() {
    ksys::act::ai::Action::leave_();
}

void ChangeChoiceNumMsgFor3DShop::loadParams_() {}

void ChangeChoiceNumMsgFor3DShop::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
