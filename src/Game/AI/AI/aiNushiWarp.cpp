#include "Game/AI/AI/aiNushiWarp.h"

namespace uking::ai {

NushiWarp::NushiWarp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

NushiWarp::~NushiWarp() = default;

bool NushiWarp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void NushiWarp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void NushiWarp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void NushiWarp::loadParams_() {}

}  // namespace uking::ai
