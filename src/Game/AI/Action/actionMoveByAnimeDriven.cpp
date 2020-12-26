#include "Game/AI/Action/actionMoveByAnimeDriven.h"

namespace uking::action {

MoveByAnimeDriven::MoveByAnimeDriven(const InitArg& arg) : ksys::act::ai::Action(arg) {}

MoveByAnimeDriven::~MoveByAnimeDriven() = default;

bool MoveByAnimeDriven::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void MoveByAnimeDriven::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void MoveByAnimeDriven::leave_() {
    ksys::act::ai::Action::leave_();
}

void MoveByAnimeDriven::loadParams_() {
    getStaticParam(&mIsChangeable_s, "IsChangeable");
    getStaticParam(&mIsIgnoreSameAS_s, "IsIgnoreSameAS");
    getStaticParam(&mASKeyName_s, "ASKeyName");
    getStaticParam(&mTargetBoneName_s, "TargetBoneName");
}

void MoveByAnimeDriven::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
