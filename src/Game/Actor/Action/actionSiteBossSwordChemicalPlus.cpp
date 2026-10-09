#include "Game/Actor/Action/actionSiteBossSwordChemicalPlus.h"

namespace uking::action {

SiteBossSwordChemicalPlus::SiteBossSwordChemicalPlus(const InitArg& arg) : StopBase(arg) {}

SiteBossSwordChemicalPlus::~SiteBossSwordChemicalPlus() = default;

bool SiteBossSwordChemicalPlus::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void SiteBossSwordChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void SiteBossSwordChemicalPlus::leave_() {
    StopBase::leave_();
}

void SiteBossSwordChemicalPlus::loadParams_() {
    StopBase::loadParams_();
}

void SiteBossSwordChemicalPlus::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
