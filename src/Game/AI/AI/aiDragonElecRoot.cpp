#include "Game/AI/AI/aiDragonElecRoot.h"

namespace uking::ai {

DragonElecRoot::DragonElecRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonElecRoot::~DragonElecRoot() = default;

bool DragonElecRoot::init_(sead::Heap* heap) {
    return DragonRoot::init_(heap);
}

void DragonElecRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonElecRoot::leave_() {
    DragonRoot::leave_();
}

void DragonElecRoot::loadParams_() {
    DragonRoot::loadParams_();
}

}  // namespace uking::ai
