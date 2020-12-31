#include "Game/AI/AI/aiGiantArmorRoot.h"

namespace uking::ai {

GiantArmorRoot::GiantArmorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GiantArmorRoot::~GiantArmorRoot() = default;

bool GiantArmorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GiantArmorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GiantArmorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GiantArmorRoot::loadParams_() {}

}  // namespace uking::ai
