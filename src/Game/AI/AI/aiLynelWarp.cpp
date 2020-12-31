#include "Game/AI/AI/aiLynelWarp.h"

namespace uking::ai {

LynelWarp::LynelWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LynelWarp::~LynelWarp() = default;

bool LynelWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LynelWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LynelWarp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LynelWarp::loadParams_() {}

}  // namespace uking::ai
