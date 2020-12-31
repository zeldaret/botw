#include "Game/AI/AI/aiEnemyFortressMgrTag.h"

namespace uking::ai {

EnemyFortressMgrTag::EnemyFortressMgrTag(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyFortressMgrTag::~EnemyFortressMgrTag() = default;

bool EnemyFortressMgrTag::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void EnemyFortressMgrTag::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyFortressMgrTag::leave_() {
    ksys::act::ai::Ai::leave_();
}

void EnemyFortressMgrTag::loadParams_() {
    getStaticParam(&mCheckInterval_s, "CheckInterval");
    getStaticParam(&mChangePer_s, "ChangePer");
    getAITreeVariable(&mRegistedActorUnit_a, "RegistedActorUnit");
}

}  // namespace uking::ai
