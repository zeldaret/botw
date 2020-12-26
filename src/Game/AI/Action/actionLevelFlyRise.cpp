#include "Game/AI/Action/actionLevelFlyRise.h"

namespace uking::action {

LevelFlyRise::LevelFlyRise(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LevelFlyRise::~LevelFlyRise() = default;

bool LevelFlyRise::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LevelFlyRise::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LevelFlyRise::leave_() {
    ksys::act::ai::Action::leave_();
}

void LevelFlyRise::loadParams_() {
    getStaticParam(&mHeight_s, "Height");
    getStaticParam(&mSpeed_s, "Speed");
    getStaticParam(&mPosReduceRatio_s, "PosReduceRatio");
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mASName_s, "ASName");
}

void LevelFlyRise::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
