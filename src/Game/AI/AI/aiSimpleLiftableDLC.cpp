#include "Game/AI/AI/aiSimpleLiftableDLC.h"

namespace uking::ai {

SimpleLiftableDLC::SimpleLiftableDLC(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

SimpleLiftableDLC::~SimpleLiftableDLC() = default;

bool SimpleLiftableDLC::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void SimpleLiftableDLC::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void SimpleLiftableDLC::leave_() {
    ksys::act::ai::Ai::leave_();
}

void SimpleLiftableDLC::loadParams_() {
    getStaticParam(&mScaleToLiftUp_s, "ScaleToLiftUp");
}

}  // namespace uking::ai
