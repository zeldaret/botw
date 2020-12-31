#include "Game/AI/AI/aiDragonFireRoot.h"

namespace uking::ai {

DragonFireRoot::DragonFireRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonFireRoot::~DragonFireRoot() = default;

bool DragonFireRoot::init_(sead::Heap* heap) {
    return DragonRoot::init_(heap);
}

void DragonFireRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonFireRoot::leave_() {
    DragonRoot::leave_();
}

void DragonFireRoot::loadParams_() {
    DragonRoot::loadParams_();
}

}  // namespace uking::ai
