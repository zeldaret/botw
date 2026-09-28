#include "Game/Actor/Action/actionStopASPlay.h"

namespace uking::action {

StopASPlay::StopASPlay(const InitArg& arg) : StopBase(arg) {}

StopASPlay::~StopASPlay() = default;

void StopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void StopASPlay::leave_() {
    StopBase::leave_();
}

void StopASPlay::loadParams_() {
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    StopBase::loadParams_();
}

void StopASPlay::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
