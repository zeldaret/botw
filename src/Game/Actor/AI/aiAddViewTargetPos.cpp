#include "Game/Actor/AI/aiAddViewTargetPos.h"

namespace uking::ai {

AddViewTargetPos::AddViewTargetPos(const InitArg& arg) : AddViewTarget(arg) {}

AddViewTargetPos::~AddViewTargetPos() = default;

bool AddViewTargetPos::init_(sead::Heap* heap) {
    return AddViewTarget::init_(heap);
}

void AddViewTargetPos::enter_(ksys::act::ai::InlineParamPack* params) {
    AddViewTarget::enter_(params);
}

void AddViewTargetPos::leave_() {
    AddViewTarget::leave_();
}

void AddViewTargetPos::loadParams_() {
    AddViewTarget::loadParams_();
}

}  // namespace uking::ai
