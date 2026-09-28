#include "Game/Actor/Action/actionMimic.h"

namespace uking::action {

Mimic::Mimic(const InitArg& arg) : StopBase(arg) {}

Mimic::~Mimic() = default;

void Mimic::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void Mimic::leave_() {
    StopBase::leave_();
}

void Mimic::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mMimicTime_s, "MimicTime");
    getStaticParam(&mMimicRate_s, "MimicRate");
    getStaticParam(&mMimicStartASName_s, "MimicStartASName");
    getStaticParam(&mMimicLoopASName_s, "MimicLoopASName");
    getStaticParam(&mMimicEndASName_s, "MimicEndASName");
    getAITreeVariable(&mMimicryMaterial_a, "MimicryMaterial");
    getAITreeVariable(&mIsStartResetMimicry_a, "IsStartResetMimicry");
}

void Mimic::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
