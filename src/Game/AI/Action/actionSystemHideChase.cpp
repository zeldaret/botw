#include "Game/AI/Action/actionSystemHideChase.h"

namespace uking::action {

SystemHideChase::SystemHideChase(const InitArg& arg) : SystemHide(arg) {}

SystemHideChase::~SystemHideChase() = default;

bool SystemHideChase::init_(sead::Heap* heap) {
    return SystemHide::init_(heap);
}

void SystemHideChase::enter_(ksys::act::ai::InlineParamPack* params) {
    SystemHide::enter_(params);
}

void SystemHideChase::leave_() {
    SystemHide::leave_();
}

void SystemHideChase::loadParams_() {
    SystemHide::loadParams_();
    getDynamicParam(&mTargetPos_d, "TargetPos");
}

void SystemHideChase::calc_() {
    SystemHide::calc_();
}

}  // namespace uking::action
