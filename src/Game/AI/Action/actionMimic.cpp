#include "Game/AI/Action/actionMimic.h"

namespace uking::action {

Mimic::Mimic(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

Mimic::~Mimic() = default;

void Mimic::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void Mimic::leave_() {
    ActionWithPosAngReduce::leave_();
}

void Mimic::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mMimicTime_s, "MimicTime");
    getStaticParam(&mMimicRate_s, "MimicRate");
    getStaticParam(&mMimicStartASName_s, "MimicStartASName");
    getStaticParam(&mMimicLoopASName_s, "MimicLoopASName");
    getStaticParam(&mMimicEndASName_s, "MimicEndASName");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

void Mimic::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
