#include "Game/AI/Action/actionGuardWithAS.h"

namespace uking::action {

GuardWithAS::GuardWithAS(const InitArg& arg) : Guard(arg) {}

GuardWithAS::~GuardWithAS() = default;

bool GuardWithAS::init_(sead::Heap* heap) {
    return Guard::init_(heap);
}

void GuardWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    Guard::enter_(params);
}

void GuardWithAS::leave_() {
    Guard::leave_();
}

void GuardWithAS::loadParams_() {
    Guard::loadParams_();
    getStaticParam(&mASSlot_s, "ASSlot");
    getStaticParam(&mASName_s, "ASName");
}

void GuardWithAS::calc_() {
    Guard::calc_();
}

}  // namespace uking::action
