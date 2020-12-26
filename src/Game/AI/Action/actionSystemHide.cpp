#include "Game/AI/Action/actionSystemHide.h"

namespace uking::action {

SystemHide::SystemHide(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemHide::~SystemHide() = default;

bool SystemHide::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemHide::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemHide::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemHide::loadParams_() {
    getStaticParam(&mIsOnAttention_s, "IsOnAttention");
    getStaticParam(&mASName_s, "ASName");
}

void SystemHide::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
