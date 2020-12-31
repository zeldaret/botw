#include "Game/AI/AI/aiBeeBattle.h"

namespace uking::ai {

BeeBattle::BeeBattle(const InitArg& arg) : EnemyBattle(arg) {}

BeeBattle::~BeeBattle() = default;

bool BeeBattle::init_(sead::Heap* heap) {
    return EnemyBattle::init_(heap);
}

void BeeBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyBattle::enter_(params);
}

void BeeBattle::leave_() {
    EnemyBattle::leave_();
}

void BeeBattle::loadParams_() {
    EnemyBattle::loadParams_();
}

}  // namespace uking::ai
