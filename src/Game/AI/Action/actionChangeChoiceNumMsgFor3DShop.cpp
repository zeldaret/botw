#include "Game/AI/Action/actionChangeChoiceNumMsgFor3DShop.h"

namespace uking::action {

ChangeChoiceNumMsgFor3DShop::ChangeChoiceNumMsgFor3DShop(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ChangeChoiceNumMsgFor3DShop::~ChangeChoiceNumMsgFor3DShop() = default;

bool ChangeChoiceNumMsgFor3DShop::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangeChoiceNumMsgFor3DShop::loadParams_() {}

}  // namespace uking::action
