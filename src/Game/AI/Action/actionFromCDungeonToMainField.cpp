#include "Game/AI/Action/actionFromCDungeonToMainField.h"

namespace uking::action {

FromCDungeonToMainField::FromCDungeonToMainField(const InitArg& arg) : ChangeSceneBase(arg) {}

FromCDungeonToMainField::~FromCDungeonToMainField() = default;

bool FromCDungeonToMainField::init_(sead::Heap* heap) {
    return ChangeSceneBase::init_(heap);
}

void FromCDungeonToMainField::enter_(ksys::act::ai::InlineParamPack* params) {
    ChangeSceneBase::enter_(params);
}

void FromCDungeonToMainField::leave_() {
    ChangeSceneBase::leave_();
}

void FromCDungeonToMainField::loadParams_() {
    ChangeSceneBase::loadParams_();
}

void FromCDungeonToMainField::calc_() {
    ChangeSceneBase::calc_();
}

}  // namespace uking::action
