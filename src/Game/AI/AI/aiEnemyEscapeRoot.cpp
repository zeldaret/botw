#include "Game/AI/AI/aiEnemyEscapeRoot.h"

namespace uking::ai {

EnemyEscapeRoot::EnemyEscapeRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

EnemyEscapeRoot::~EnemyEscapeRoot() = default;

void EnemyEscapeRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void EnemyEscapeRoot::loadParams_() {}

}  // namespace uking::ai
