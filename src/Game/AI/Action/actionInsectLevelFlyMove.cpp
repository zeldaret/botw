#include "Game/AI/Action/actionInsectLevelFlyMove.h"

namespace uking::action {

InsectLevelFlyMove::InsectLevelFlyMove(const InitArg& arg) : LevelFlyMove(arg) {}

InsectLevelFlyMove::~InsectLevelFlyMove() = default;

bool InsectLevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMove::init_(heap);
}

void InsectLevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMove::enter_(params);
}

void InsectLevelFlyMove::leave_() {
    LevelFlyMove::leave_();
}

void InsectLevelFlyMove::loadParams_() {
    LevelFlyMove::loadParams_();
    getStaticParam(&mReduceSpeedRateWithWind_s, "ReduceSpeedRateWithWind");
    getStaticParam(&mWindVelocityLimit4Reduce_s, "WindVelocityLimit4Reduce");
}

void InsectLevelFlyMove::calc_() {
    LevelFlyMove::calc_();
}

}  // namespace uking::action
