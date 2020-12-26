#include "Game/AI/Action/actionSystemDelete.h"

namespace uking::action {

SystemDelete::SystemDelete(const InitArg& arg) : ksys::act::ai::Action(arg) {}

SystemDelete::~SystemDelete() = default;

bool SystemDelete::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void SystemDelete::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void SystemDelete::leave_() {
    ksys::act::ai::Action::leave_();
}

void SystemDelete::loadParams_() {}

void SystemDelete::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
