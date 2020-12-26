#include "Game/AI/Action/actionDynamicFireWood.h"

namespace uking::action {

DynamicFireWood::DynamicFireWood(const InitArg& arg) : FireWood(arg) {}

DynamicFireWood::~DynamicFireWood() = default;

bool DynamicFireWood::init_(sead::Heap* heap) {
    return FireWood::init_(heap);
}

void DynamicFireWood::enter_(ksys::act::ai::InlineParamPack* params) {
    FireWood::enter_(params);
}

void DynamicFireWood::leave_() {
    FireWood::leave_();
}

void DynamicFireWood::loadParams_() {
    FireWood::loadParams_();
}

void DynamicFireWood::calc_() {
    FireWood::calc_();
}

}  // namespace uking::action
