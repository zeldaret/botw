#include "Game/AI/AI/aiMagneGearRoot.h"

namespace uking::ai {

MagneGearRoot::MagneGearRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

MagneGearRoot::~MagneGearRoot() = default;

bool MagneGearRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void MagneGearRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void MagneGearRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void MagneGearRoot::loadParams_() {}

}  // namespace uking::ai
