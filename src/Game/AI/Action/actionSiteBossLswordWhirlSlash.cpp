#include "Game/AI/Action/actionSiteBossLswordWhirlSlash.h"

namespace uking::action {

SiteBossLswordWhirlSlash::SiteBossLswordWhirlSlash(const InitArg& arg)
    : SiteBossLswordAtkWithChemical(arg) {}

SiteBossLswordWhirlSlash::~SiteBossLswordWhirlSlash() = default;

void SiteBossLswordWhirlSlash::loadParams_() {
    SiteBossLswordAtkWithChemical::loadParams_();
    getStaticParam(&mEmitChangeDist_s, "EmitChangeDist");
    getStaticParam(&mCircleEmitOffset_s, "CircleEmitOffset");
}

void SiteBossLswordWhirlSlash::calc_() {
    SiteBossLswordAtkWithChemical::calc_();
}

}  // namespace uking::action
