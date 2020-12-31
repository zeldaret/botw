#include "Game/AI/AI/aiLOSFurthestHitPointFinder.h"

namespace uking::ai {

LOSFurthestHitPointFinder::LOSFurthestHitPointFinder(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LOSFurthestHitPointFinder::~LOSFurthestHitPointFinder() = default;

bool LOSFurthestHitPointFinder::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LOSFurthestHitPointFinder::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LOSFurthestHitPointFinder::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LOSFurthestHitPointFinder::loadParams_() {
    getStaticParam(&mMaxNumCheck_s, "MaxNumCheck");
    getStaticParam(&mCheckDistance_s, "CheckDistance");
    getStaticParam(&mOnlyCheckBehind_s, "OnlyCheckBehind");
    getStaticParam(&mUseActionB_s, "UseActionB");
}

}  // namespace uking::ai
