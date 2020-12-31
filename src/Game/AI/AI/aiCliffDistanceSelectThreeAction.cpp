#include "Game/AI/AI/aiCliffDistanceSelectThreeAction.h"

namespace uking::ai {

CliffDistanceSelectThreeAction::CliffDistanceSelectThreeAction(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

CliffDistanceSelectThreeAction::~CliffDistanceSelectThreeAction() = default;

bool CliffDistanceSelectThreeAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CliffDistanceSelectThreeAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CliffDistanceSelectThreeAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CliffDistanceSelectThreeAction::loadParams_() {
    getStaticParam(&mCheckDist_s, "CheckDist");
    getStaticParam(&mNearCliffDist_s, "NearCliffDist");
}

}  // namespace uking::ai
