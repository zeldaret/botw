#include "Game/AI/AI/aiShutterFence.h"

namespace uking::ai {

ShutterFence::ShutterFence(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

ShutterFence::~ShutterFence() = default;

bool ShutterFence::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void ShutterFence::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void ShutterFence::leave_() {
    ksys::act::ai::Ai::leave_();
}

void ShutterFence::loadParams_() {
    getStaticParam(&mASKeyName_On_s, "ASKeyName_On");
    getStaticParam(&mASKeyName_Off_s, "ASKeyName_Off");
}

}  // namespace uking::ai
