#include "Game/AI/AI/aiRodRoot.h"

namespace uking::ai {

RodRoot::RodRoot(const InitArg& arg) : WeaponRootAI(arg) {}

RodRoot::~RodRoot() = default;

bool RodRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void RodRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
}

void RodRoot::leave_() {
    WeaponRootAI::leave_();
}

void RodRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

}  // namespace uking::ai
