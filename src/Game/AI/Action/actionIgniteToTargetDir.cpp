#include "Game/AI/Action/actionIgniteToTargetDir.h"

namespace uking::action {

IgniteToTargetDir::IgniteToTargetDir(const InitArg& arg) : IgniteToTargetSimple(arg) {}

IgniteToTargetDir::~IgniteToTargetDir() = default;

bool IgniteToTargetDir::init_(sead::Heap* heap) {
    return IgniteToTargetSimple::init_(heap);
}

void IgniteToTargetDir::enter_(ksys::act::ai::InlineParamPack* params) {
    IgniteToTargetSimple::enter_(params);
}

void IgniteToTargetDir::leave_() {
    IgniteToTargetSimple::leave_();
}

void IgniteToTargetDir::loadParams_() {
    IgniteToTargetSimple::loadParams_();
}

void IgniteToTargetDir::calc_() {
    IgniteToTargetSimple::calc_();
}

}  // namespace uking::action
