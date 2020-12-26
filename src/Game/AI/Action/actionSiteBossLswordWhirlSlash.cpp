#include "Game/AI/Action/actionSiteBossLswordWhirlSlash.h"

namespace uking::action {

SiteBossLswordWhirlSlash::SiteBossLswordWhirlSlash(const InitArg& arg)
    : SiteBossLswordAtkWithChemical(arg) {}

SiteBossLswordWhirlSlash::~SiteBossLswordWhirlSlash() = default;

bool SiteBossLswordWhirlSlash::init_(sead::Heap* heap) {
    return SiteBossLswordAtkWithChemical::init_(heap);
}

void SiteBossLswordWhirlSlash::enter_(ksys::act::ai::InlineParamPack* params) {
    SiteBossLswordAtkWithChemical::enter_(params);
}

void SiteBossLswordWhirlSlash::leave_() {
    SiteBossLswordAtkWithChemical::leave_();
}

void SiteBossLswordWhirlSlash::loadParams_() {
    SiteBossLswordAtkWithChemical::loadParams_();
    getStaticParam(&mEmitChangeDist_s, "EmitChangeDist");
    getStaticParam(&mCircleEmitOffset_s, "CircleEmitOffset");
}

void SiteBossLswordWhirlSlash::calc_() {
    SiteBossLswordAtkWithChemical::calc_();
}

}  // namespace uking::action
