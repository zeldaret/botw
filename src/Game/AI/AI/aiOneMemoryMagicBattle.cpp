#include "Game/AI/AI/aiOneMemoryMagicBattle.h"

namespace uking::ai {

OneMemoryMagicBattle::OneMemoryMagicBattle(const InitArg& arg) : OneMemoryMagicBattleBase(arg) {}

OneMemoryMagicBattle::~OneMemoryMagicBattle() = default;

bool OneMemoryMagicBattle::init_(sead::Heap* heap) {
    return OneMemoryMagicBattleBase::init_(heap);
}

void OneMemoryMagicBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    OneMemoryMagicBattleBase::enter_(params);
}

void OneMemoryMagicBattle::leave_() {
    OneMemoryMagicBattleBase::leave_();
}

void OneMemoryMagicBattle::loadParams_() {
    OneMemoryMagicBattleBase::loadParams_();
    getStaticParam(&mMemoryPartsName_s, "MemoryPartsName");
}

}  // namespace uking::ai
