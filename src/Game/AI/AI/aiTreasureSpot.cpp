#include "Game/AI/AI/aiTreasureSpot.h"

namespace uking::ai {

TreasureSpot::TreasureSpot(const InitArg& arg) : CommonPickedItem(arg) {}

TreasureSpot::~TreasureSpot() = default;

bool TreasureSpot::init_(sead::Heap* heap) {
    return CommonPickedItem::init_(heap);
}

void TreasureSpot::enter_(ksys::act::ai::InlineParamPack* params) {
    CommonPickedItem::enter_(params);
}

void TreasureSpot::leave_() {
    CommonPickedItem::leave_();
}

void TreasureSpot::loadParams_() {
    CommonPickedItem::loadParams_();
    getStaticParam(&mGetAttKeyForGuardian_s, "GetAttKeyForGuardian");
    getMapUnitParam(&mTresasureSpotType_m, "TresasureSpotType");
}

}  // namespace uking::ai
