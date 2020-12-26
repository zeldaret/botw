#include "Game/AI/Action/actionOnetimeStopASPlay.h"

namespace uking::action {

OnetimeStopASPlay::OnetimeStopASPlay(const InitArg& arg) : ActionWithAS(arg) {}

OnetimeStopASPlay::~OnetimeStopASPlay() = default;

bool OnetimeStopASPlay::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void OnetimeStopASPlay::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void OnetimeStopASPlay::leave_() {
    ActionWithAS::leave_();
}

void OnetimeStopASPlay::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsIgnoreSame_s, "IsIgnoreSame");
    getStaticParam(&mASName_s, "ASName");
}

void OnetimeStopASPlay::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
