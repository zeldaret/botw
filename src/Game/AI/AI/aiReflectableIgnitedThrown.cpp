#include "Game/AI/AI/aiReflectableIgnitedThrown.h"

namespace uking::ai {

ReflectableIgnitedThrown::ReflectableIgnitedThrown(const InitArg& arg) : ReflectableThrown(arg) {}

ReflectableIgnitedThrown::~ReflectableIgnitedThrown() = default;

bool ReflectableIgnitedThrown::init_(sead::Heap* heap) {
    return ReflectableThrown::init_(heap);
}

void ReflectableIgnitedThrown::enter_(ksys::act::ai::InlineParamPack* params) {
    ReflectableThrown::enter_(params);
}

void ReflectableIgnitedThrown::leave_() {
    ReflectableThrown::leave_();
}

void ReflectableIgnitedThrown::loadParams_() {
    ReflectableThrown::loadParams_();
}

}  // namespace uking::ai
