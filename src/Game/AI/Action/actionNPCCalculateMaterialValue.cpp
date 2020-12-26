#include "Game/AI/Action/actionNPCCalculateMaterialValue.h"

namespace uking::action {

NPCCalculateMaterialValue::NPCCalculateMaterialValue(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

NPCCalculateMaterialValue::~NPCCalculateMaterialValue() = default;

bool NPCCalculateMaterialValue::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void NPCCalculateMaterialValue::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void NPCCalculateMaterialValue::leave_() {
    ksys::act::ai::Action::leave_();
}

void NPCCalculateMaterialValue::loadParams_() {}

void NPCCalculateMaterialValue::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
