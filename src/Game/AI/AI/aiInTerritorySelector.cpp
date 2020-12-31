#include "Game/AI/AI/aiInTerritorySelector.h"

namespace uking::ai {

InTerritorySelector::InTerritorySelector(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

InTerritorySelector::~InTerritorySelector() = default;

void InTerritorySelector::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void InTerritorySelector::leave_() {
    ksys::act::ai::Ai::leave_();
}

void InTerritorySelector::loadParams_() {
    getStaticParam(&mTerritoryArea_s, "TerritoryArea");
}

}  // namespace uking::ai
