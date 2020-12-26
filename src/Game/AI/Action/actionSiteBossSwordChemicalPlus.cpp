#include "Game/AI/Action/actionSiteBossSwordChemicalPlus.h"

namespace uking::action {

SiteBossSwordChemicalPlus::SiteBossSwordChemicalPlus(const InitArg& arg)
    : ActionWithPosAngReduce(arg) {}

SiteBossSwordChemicalPlus::~SiteBossSwordChemicalPlus() = default;

bool SiteBossSwordChemicalPlus::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SiteBossSwordChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void SiteBossSwordChemicalPlus::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SiteBossSwordChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
}

void SiteBossSwordChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
