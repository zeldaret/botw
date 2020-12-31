#include "Game/AI/AI/aiBirdDead.h"

namespace uking::ai {

BirdDead::BirdDead(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BirdDead::~BirdDead() = default;

bool BirdDead::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BirdDead::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BirdDead::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BirdDead::loadParams_() {
    getStaticParam(&mGravityScale_s, "GravityScale");
}

}  // namespace uking::ai
