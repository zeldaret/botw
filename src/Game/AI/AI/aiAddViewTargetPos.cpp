#include "Game/AI/AI/aiAddViewTargetPos.h"

namespace uking::ai {

AddViewTargetPos::AddViewTargetPos(const InitArg& arg) : AddViewTargetPosBase(arg) {}

AddViewTargetPos::~AddViewTargetPos() = default;

bool AddViewTargetPos::init_(sead::Heap* heap) {
    return AddViewTargetPosBase::init_(heap);
}

void AddViewTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    AddViewTargetPosBase::enter_(params);
}

void AddViewTargetPos::leave_() {
    AddViewTargetPosBase::leave_();
}

void AddViewTargetPos::loadParams_() {
    AddViewTargetPosBase::loadParams_();
}

}  // namespace uking::ai
