#include "Game/AI/AI/aiCircleMove.h"

namespace uking::ai {

CircleMove::CircleMove(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

CircleMove::~CircleMove() = default;

bool CircleMove::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void CircleMove::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void CircleMove::leave_() {
    ksys::act::ai::Ai::leave_();
}

void CircleMove::loadParams_() {
    getStaticParam(&mDirection_s, "Direction");
    getStaticParam(&mRadius_s, "Radius");
    getStaticParam(&mRadiusMargin_s, "RadiusMargin");
    getStaticParam(&mSpeed_s, "Speed");
}

}  // namespace uking::ai
