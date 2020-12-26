#include "Game/AI/Action/actionSiteBossChemicalPlus.h"

namespace uking::action {

SiteBossChemicalPlus::SiteBossChemicalPlus(const InitArg& arg) : ActionWithPosAngReduce(arg) {}

SiteBossChemicalPlus::~SiteBossChemicalPlus() = default;

bool SiteBossChemicalPlus::init_(sead::Heap* heap) {
    return ActionWithPosAngReduce::init_(heap);
}

void SiteBossChemicalPlus::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithPosAngReduce::enter_(params);
}

void SiteBossChemicalPlus::leave_() {
    ActionWithPosAngReduce::leave_();
}

void SiteBossChemicalPlus::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mIsDeleteAllChildDevice_s, "IsDeleteAllChildDevice");
    getStaticParam(&mIsSetCanGuardArrowFlag_s, "IsSetCanGuardArrowFlag");
    getStaticParam(&mChemicalLoopASName_s, "ChemicalLoopASName");
    getStaticParam(&mChmicalPlusASName_s, "ChmicalPlusASName");
}

void SiteBossChemicalPlus::calc_() {
    ActionWithPosAngReduce::calc_();
}

}  // namespace uking::action
