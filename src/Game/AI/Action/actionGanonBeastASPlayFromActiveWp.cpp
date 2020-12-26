#include "Game/AI/Action/actionGanonBeastASPlayFromActiveWp.h"

namespace uking::action {

GanonBeastASPlayFromActiveWp::GanonBeastASPlayFromActiveWp(const InitArg& arg)
    : ForkASPlayBase(arg) {}

GanonBeastASPlayFromActiveWp::~GanonBeastASPlayFromActiveWp() = default;

bool GanonBeastASPlayFromActiveWp::init_(sead::Heap* heap) {
    return ForkASPlayBase::init_(heap);
}

void GanonBeastASPlayFromActiveWp::enter_(ksys::act::ai::InlineParamPack* params) {
    ForkASPlayBase::enter_(params);
}

void GanonBeastASPlayFromActiveWp::leave_() {
    ForkASPlayBase::leave_();
}

void GanonBeastASPlayFromActiveWp::loadParams_() {
    ForkASPlayBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
}

void GanonBeastASPlayFromActiveWp::calc_() {
    ForkASPlayBase::calc_();
}

}  // namespace uking::action
