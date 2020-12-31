#include "Game/AI/AI/aiOnCliffSurfaceSelect.h"

namespace uking::ai {

OnCliffSurfaceSelect::OnCliffSurfaceSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

OnCliffSurfaceSelect::~OnCliffSurfaceSelect() = default;

bool OnCliffSurfaceSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void OnCliffSurfaceSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void OnCliffSurfaceSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void OnCliffSurfaceSelect::loadParams_() {
    getMapUnitParam(&mOnCliff_m, "OnCliff");
    getAITreeVariable(&mIsCliffFreeze_a, "IsCliffFreeze");
}

}  // namespace uking::ai
