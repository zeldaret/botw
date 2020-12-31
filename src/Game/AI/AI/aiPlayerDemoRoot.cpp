#include "Game/AI/AI/aiPlayerDemoRoot.h"

namespace uking::ai {

PlayerDemoRoot::PlayerDemoRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PlayerDemoRoot::~PlayerDemoRoot() = default;

bool PlayerDemoRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void PlayerDemoRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PlayerDemoRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void PlayerDemoRoot::loadParams_() {}

}  // namespace uking::ai
