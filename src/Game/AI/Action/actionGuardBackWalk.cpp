#include "Game/AI/Action/actionGuardBackWalk.h"

namespace uking::action {

GuardBackWalk::GuardBackWalk(const InitArg& arg) : BackWalkEx(arg) {}

bool GuardBackWalk::init_(sead::Heap* heap) {
    return BackWalkEx::init_(heap);
}

void GuardBackWalk::enter_(ksys::act::ai::InlineParamPack* params) {
    BackWalkEx::enter_(params);
}

void GuardBackWalk::leave_() {
    BackWalkEx::leave_();
}

void GuardBackWalk::loadParams_() {
    BackWalkEx::loadParams_();
}

void GuardBackWalk::calc_() {
    BackWalkEx::calc_();
}

}  // namespace uking::action
