#include "Game/AI/Action/actionDungeonRotate.h"

namespace uking::action {

DungeonRotate::DungeonRotate(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotate::~DungeonRotate() = default;

bool DungeonRotate::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotate::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DungeonRotate::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotate::loadParams_() {
    DungeonRotateBase::loadParams_();
    getMapUnitParam(&mDgnRotDir_m, "DgnRotDir");
}

void DungeonRotate::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
