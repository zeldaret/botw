#include "Game/AI/Action/actionStopASPlay.h"

namespace uking::action {

StopASPlay::StopASPlay(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

StopASPlay::~StopASPlay() = default;

void StopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void StopASPlay::leave_() {
    ActionWithPosAngReduce::leave_();
}

void StopASPlay::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    ActionWithPosAngReduce::loadParams_();
}

void StopASPlay::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
