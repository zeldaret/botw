#include "Game/Actor/Action/actionSiteBossChemicalPlus.h"

namespace uking::action {

SiteBossChemicalPlus::SiteBossChemicalPlus(const InitArg& arg) : StopBase(arg) {}

SiteBossChemicalPlus::~SiteBossChemicalPlus() = default;

bool SiteBossChemicalPlus::init_(sead::Heap* heap) {
    return StopBase::init_(heap);
}

void SiteBossChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    StopBase::enter_(params);
}

void SiteBossChemicalPlus::leave_() {
    StopBase::leave_();
}

void SiteBossChemicalPlus::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mIsDeleteAllChildDevice_s, "IsDeleteAllChildDevice");
    getStaticParam(&mIsSetCanGuardArrowFlag_s, "IsSetCanGuardArrowFlag");
    getStaticParam(&mChemicalLoopASName_s, "ChemicalLoopASName");
    getStaticParam(&mChmicalPlusASName_s, "ChmicalPlusASName");
}

void SiteBossChemicalPlus::calc_() {
    StopBase::calc_();
}

}  // namespace uking::action
