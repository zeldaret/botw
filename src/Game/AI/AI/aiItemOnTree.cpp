#include "Game/AI/AI/aiItemOnTree.h"

namespace uking::ai {

ItemOnTree::ItemOnTree(const InitArg& arg) : ItemRoot(arg) {}

ItemOnTree::~ItemOnTree() = default;

bool ItemOnTree::init_(sead::Heap* heap) {
    return ItemRoot::init_(heap);
}

void ItemOnTree::enter_(ksys::act::ai::InlineParamPack* params) {
    ItemRoot::enter_(params);
}

void ItemOnTree::leave_() {
    ItemRoot::leave_();
}

void ItemOnTree::loadParams_() {
    ItemRoot::loadParams_();
    getStaticParam(&mFallPowerMin_s, "FallPowerMin");
    getStaticParam(&mFallPowerMax_s, "FallPowerMax");
    getStaticParam(&mFallOddsMin_s, "FallOddsMin");
    getStaticParam(&mFallOddsMax_s, "FallOddsMax");
    getStaticParam(&mFallIntervalRange_s, "FallIntervalRange");
    getStaticParam(&mFallCheckSpeedTh_s, "FallCheckSpeedTh");
    getStaticParam(&mAttOnTree_s, "AttOnTree");
    getStaticParam(&mAttOnGround_s, "AttOnGround");
}

}  // namespace uking::ai
