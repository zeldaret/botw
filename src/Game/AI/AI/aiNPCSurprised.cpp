#include "Game/AI/AI/aiNPCSurprised.h"

namespace uking::ai {

NPCSurprised::NPCSurprised(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NPCSurprised::~NPCSurprised() = default;

bool NPCSurprised::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NPCSurprised::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NPCSurprised::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NPCSurprised::loadParams_() {
    getDynamicParam(&mTerrorLayer_d, "TerrorLayer");
    getDynamicParam(&mIsNeedUnEquipWeapon_d, "IsNeedUnEquipWeapon");
    getDynamicParam(&mTerrorEmitter_d, "TerrorEmitter");
}

}  // namespace uking::ai
