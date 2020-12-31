#include "Game/AI/AI/aiKorokPinWheelRoot.h"

namespace uking::ai {

KorokPinWheelRoot::KorokPinWheelRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

KorokPinWheelRoot::~KorokPinWheelRoot() = default;

bool KorokPinWheelRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void KorokPinWheelRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void KorokPinWheelRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void KorokPinWheelRoot::loadParams_() {
    getStaticParam(&mRotSpd_s, "RotSpd");
    getStaticParam(&mLength_s, "Length");
}

}  // namespace uking::ai
