#include "Game/AI/Action/actionMoveWithDynAS.h"

namespace uking::action {

MoveWithDynAS::MoveWithDynAS(const InitArg& arg) : MoveBase(arg) {}

MoveWithDynAS::~MoveWithDynAS() = default;

bool MoveWithDynAS::init_(sead::Heap* heap) {
    return MoveBase::init_(heap);
}

void MoveWithDynAS::enter_(ksys::act::ai::InlineParamPack* params) {
    MoveBase::enter_(params);
}

void MoveWithDynAS::leave_() {
    MoveBase::leave_();
}

void MoveWithDynAS::loadParams_() {
    MoveBase::loadParams_();
    getDynamicParam(&mASName_d, "ASName");
}

void MoveWithDynAS::calc_() {
    MoveBase::calc_();
}

}  // namespace uking::action
