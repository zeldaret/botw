#include "Game/Actor/AI/aiOneMemoryMagicBattle.h"

namespace uking::ai {

OneMemoryMagicBattle::OneMemoryMagicBattle(const InitArg& arg) : MagicBattle(arg) {}

OneMemoryMagicBattle::~OneMemoryMagicBattle() = default;

bool OneMemoryMagicBattle::init_(sead::Heap* heap) {
    return MagicBattle::init_(heap);
}

void OneMemoryMagicBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    MagicBattle::enter_(params);
}

void OneMemoryMagicBattle::leave_() {
    MagicBattle::leave_();
}

void OneMemoryMagicBattle::loadParams_() {
    MagicBattle::loadParams_();
    getStaticParam(&mMemoryPartsName_s, "MemoryPartsName");
}

}  // namespace uking::ai
