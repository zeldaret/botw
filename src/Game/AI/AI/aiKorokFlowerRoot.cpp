#include "Game/AI/AI/aiKorokFlowerRoot.h"

namespace uking::ai {

KorokFlowerRoot::KorokFlowerRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokFlowerRoot::~KorokFlowerRoot() = default;

bool KorokFlowerRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokFlowerRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokFlowerRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokFlowerRoot::loadParams_() {
    getMapUnitParam(&mIsNoAppearEffect_m, "IsNoAppearEffect");
    getMapUnitParam(&mIsLastKorokFlower_m, "IsLastKorokFlower");
}

}  // namespace uking::ai
