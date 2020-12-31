#include "Game/AI/AI/aiSiteBossSpearLifeSelector.h"

namespace uking::ai {

SiteBossSpearLifeSelector::SiteBossSpearLifeSelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SiteBossSpearLifeSelector::~SiteBossSpearLifeSelector() = default;

bool SiteBossSpearLifeSelector::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SiteBossSpearLifeSelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SiteBossSpearLifeSelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SiteBossSpearLifeSelector::loadParams_() {
    getStaticParam(&mPatternChangeLife2_s, "PatternChangeLife2");
    getStaticParam(&mPatternChangeLife3_s, "PatternChangeLife3");
}

}  // namespace uking::ai
