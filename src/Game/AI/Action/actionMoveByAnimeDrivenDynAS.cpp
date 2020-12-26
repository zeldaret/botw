#include "Game/AI/Action/actionMoveByAnimeDrivenDynAS.h"

namespace uking::action {

MoveByAnimeDrivenDynAS::MoveByAnimeDrivenDynAS(const InitArg& arg) : MoveByAnimeDriven(arg) {}

MoveByAnimeDrivenDynAS::~MoveByAnimeDrivenDynAS() = default;

bool MoveByAnimeDrivenDynAS::init_(sead::Heap* heap) {
    return MoveByAnimeDriven::init_(heap);
}

void MoveByAnimeDrivenDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveByAnimeDriven::enter_(params);
}

void MoveByAnimeDrivenDynAS::leave_() {
    MoveByAnimeDriven::leave_();
}

void MoveByAnimeDrivenDynAS::loadParams_() {
    MoveByAnimeDriven::loadParams_();
    getDynamicParam(&mDynASKeyName_d, "DynASKeyName");
}

void MoveByAnimeDrivenDynAS::calc_() {
    MoveByAnimeDriven::calc_();
}

}  // namespace uking::action
