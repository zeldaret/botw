#include "Game/AI/Action/actionHopFlyByTriggers.h"

namespace uking::action {

HopFlyByTriggers::HopFlyByTriggers(const InitArg& arg) : ksys::act::ai::Action(arg) {}

HopFlyByTriggers::~HopFlyByTriggers() = default;

bool HopFlyByTriggers::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void HopFlyByTriggers::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void HopFlyByTriggers::leave_() {
    ksys::act::ai::Action::leave_();
}

void HopFlyByTriggers::loadParams_() {
    getStaticParam(&mXZSpeedMax_s, "XZSpeedMax");
    getStaticParam(&mHopAccRatio_s, "HopAccRatio");
    getStaticParam(&mASName_s, "ASName");
}

void HopFlyByTriggers::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
