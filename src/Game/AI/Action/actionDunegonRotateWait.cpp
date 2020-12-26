#include "Game/AI/Action/actionDunegonRotateWait.h"

namespace uking::action {

DunegonRotateWait::DunegonRotateWait(const InitArg& arg) : DungeonRotateBase(arg) {}

DunegonRotateWait::~DunegonRotateWait() = default;

bool DunegonRotateWait::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DunegonRotateWait::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DunegonRotateWait::leave_() {
    DungeonRotateBase::leave_();
}

void DunegonRotateWait::loadParams_() {
    DungeonRotateBase::loadParams_();
}

void DunegonRotateWait::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
