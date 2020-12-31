#include "Game/AI/AI/aiMasterSwordRoot.h"

namespace uking::ai {

MasterSwordRoot::MasterSwordRoot(const InitArg& arg) : WeaponRootAI(arg) {}

MasterSwordRoot::~MasterSwordRoot() = default;

bool MasterSwordRoot::init_(sead::Heap* heap) {
    return WeaponRootAI::init_(heap);
}

void MasterSwordRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    WeaponRootAI::enter_(params);
}

void MasterSwordRoot::leave_() {
    WeaponRootAI::leave_();
}

void MasterSwordRoot::loadParams_() {
    WeaponRootAI::loadParams_();
    getAITreeVariable(&mMagicCreateUnit_a, "MagicCreateUnit");
}

}  // namespace uking::ai
