#include "Game/AI/AI/aiCastleLynelBattle.h"

namespace uking::ai {

CastleLynelBattle::CastleLynelBattle(const InitArg& arg) : LynelBattle(arg) {}

CastleLynelBattle::~CastleLynelBattle() = default;

bool CastleLynelBattle::init_(sead::Heap* heap) {
    return LynelBattle::init_(heap);
}

void CastleLynelBattle::enter_(ksys::act::ai::InlineParamPack* params) {
    LynelBattle::enter_(params);
}

void CastleLynelBattle::leave_() {
    LynelBattle::leave_();
}

void CastleLynelBattle::loadParams_() {
    LynelBattle::loadParams_();
}

}  // namespace uking::ai
