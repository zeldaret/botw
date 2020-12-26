#include "Game/AI/Action/actionAddNoUseTerritoryCounter.h"

namespace uking::action {

AddNoUseTerritoryCounter::AddNoUseTerritoryCounter(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

AddNoUseTerritoryCounter::~AddNoUseTerritoryCounter() = default;

bool AddNoUseTerritoryCounter::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void AddNoUseTerritoryCounter::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void AddNoUseTerritoryCounter::leave_() {
    ksys::act::ai::Action::leave_();
}

void AddNoUseTerritoryCounter::loadParams_() {
    getStaticParam(&mCounter_s, "Counter");
    getStaticParam(&mCamDist_s, "CamDist");
    getMapUnitParam(&mTerritoryArea_m, "TerritoryArea");
    getAITreeVariable(&mIsUseTerritory_a, "IsUseTerritory");
}

void AddNoUseTerritoryCounter::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
