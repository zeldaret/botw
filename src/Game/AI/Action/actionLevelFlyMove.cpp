#include "Game/AI/Action/actionLevelFlyMove.h"

namespace uking::action {

LevelFlyMove::LevelFlyMove(const InitArg& arg) : LevelFlyMoveBase(arg) {}

bool LevelFlyMove::init_(sead::Heap* heap) {
    return LevelFlyMoveBase::init_(heap);
}

void LevelFlyMove::enter_(ksys::act::ai::InlineParamPack* params) {
    LevelFlyMoveBase::enter_(params);
}

void LevelFlyMove::leave_() {
    LevelFlyMoveBase::leave_();
}

void LevelFlyMove::loadParams_() {
    LevelFlyMoveBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void LevelFlyMove::calc_() {
    LevelFlyMoveBase::calc_();
}

}  // namespace uking::action
