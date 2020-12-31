#include "Game/AI/AI/aiGiantArmorAsWeakPoint.h"

namespace uking::ai {

GiantArmorAsWeakPoint::GiantArmorAsWeakPoint(const InitArg& arg) : GiantArmorRoot(arg) {}

GiantArmorAsWeakPoint::~GiantArmorAsWeakPoint() = default;

bool GiantArmorAsWeakPoint::init_(sead::Heap* heap) {
    return GiantArmorRoot::init_(heap);
}

void GiantArmorAsWeakPoint::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantArmorRoot::enter_(params);
}

void GiantArmorAsWeakPoint::leave_() {
    GiantArmorRoot::leave_();
}

void GiantArmorAsWeakPoint::loadParams_() {
    GiantArmorRoot::loadParams_();
}

}  // namespace uking::ai
