#include "Game/AI/AI/aiGroundHitSelect.h"

namespace uking::ai {

GroundHitSelect::GroundHitSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GroundHitSelect::~GroundHitSelect() = default;

bool GroundHitSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GroundHitSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GroundHitSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GroundHitSelect::loadParams_() {
    getStaticParam(&mIsActionEndEnd_s, "IsActionEndEnd");
    getStaticParam(&mIsEnterCheck_s, "IsEnterCheck");
}

}  // namespace uking::ai
