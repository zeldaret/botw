#include "Game/AI/AI/aiMiniGolemLifted.h"

namespace uking::ai {

MiniGolemLifted::MiniGolemLifted(const InitArg& arg) : EnemyLifted(arg) {}

MiniGolemLifted::~MiniGolemLifted() = default;

bool MiniGolemLifted::init_(sead::Heap* heap) {
    return EnemyLifted::init_(heap);
}

void MiniGolemLifted::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyLifted::enter_(params);
}

void MiniGolemLifted::leave_() {
    EnemyLifted::leave_();
}

void MiniGolemLifted::loadParams_() {
    EnemyLifted::loadParams_();
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

}  // namespace uking::ai
