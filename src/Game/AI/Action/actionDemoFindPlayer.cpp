#include "Game/AI/Action/actionDemoFindPlayer.h"

namespace uking::action {

DemoFindPlayer::DemoFindPlayer(const InitArg& arg) : TimeredASPlay(arg) {}

DemoFindPlayer::~DemoFindPlayer() = default;

void DemoFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void DemoFindPlayer::loadParams_() {
    TimeredASPlay::loadParams_();
}

}  // namespace uking::action
