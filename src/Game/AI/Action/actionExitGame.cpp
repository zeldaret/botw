#include "Game/AI/Action/actionExitGame.h"

namespace uking::action {

ExitGame::ExitGame(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ExitGame::~ExitGame() = default;

bool ExitGame::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ExitGame::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ExitGame::leave_() {
    ksys::act::ai::Action::leave_();
}

void ExitGame::loadParams_() {
    getDynamicParam(&mShowLogo_d, "ShowLogo");
}

void ExitGame::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
