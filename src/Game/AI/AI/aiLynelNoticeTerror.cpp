#include "Game/AI/AI/aiLynelNoticeTerror.h"

namespace uking::ai {

LynelNoticeTerror::LynelNoticeTerror(const InitArg& arg) : EnemyNoticeTerror(arg) {}

LynelNoticeTerror::~LynelNoticeTerror() = default;

bool LynelNoticeTerror::init_(sead::Heap* heap) {
    return EnemyNoticeTerror::init_(heap);
}

void LynelNoticeTerror::enter_(ksys::act::ai::InlineParamPack* params) {
    EnemyNoticeTerror::enter_(params);
}

void LynelNoticeTerror::leave_() {
    EnemyNoticeTerror::leave_();
}

void LynelNoticeTerror::loadParams_() {
    EnemyNoticeTerror::loadParams_();
}

}  // namespace uking::ai
