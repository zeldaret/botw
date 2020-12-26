#include "Game/AI/Action/actionRestartStageFromGameOver.h"

namespace uking::action {

RestartStageFromGameOver::RestartStageFromGameOver(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

RestartStageFromGameOver::~RestartStageFromGameOver() = default;

bool RestartStageFromGameOver::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void RestartStageFromGameOver::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void RestartStageFromGameOver::leave_() {
    ksys::act::ai::Action::leave_();
}

void RestartStageFromGameOver::loadParams_() {}

void RestartStageFromGameOver::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
