#include "Game/AI/Action/actionDemoFindPlayer.h"

namespace uking::action {

DemoFindPlayer::DemoFindPlayer(const InitArg& arg) : TimeredASPlay(arg) {}

DemoFindPlayer::~DemoFindPlayer() = default;

bool DemoFindPlayer::init_(sead::Heap* heap) {
    return TimeredASPlay::init_(heap);
}

void DemoFindPlayer::enter_(ksys::act::ai::InlineParamPack* params) {
    TimeredASPlay::enter_(params);
}

void DemoFindPlayer::leave_() {
    TimeredASPlay::leave_();
}

void DemoFindPlayer::loadParams_() {
    TimeredASPlay::loadParams_();
}

void DemoFindPlayer::calc_() {
    TimeredASPlay::calc_();
}

}  // namespace uking::action
