#include "Game/AI/AI/aiBowlPin.h"

namespace uking::ai {

BowlPin::BowlPin(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

BowlPin::~BowlPin() = default;

bool BowlPin::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void BowlPin::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void BowlPin::leave_() {
    ksys::act::ai::Ai::leave_();
}

void BowlPin::loadParams_() {
    getStaticParam(&mDegree_s, "Degree");
}

}  // namespace uking::ai
