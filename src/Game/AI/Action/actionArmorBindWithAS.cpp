#include "Game/AI/Action/actionArmorBindWithAS.h"

namespace uking::action {

ArmorBindWithAS::ArmorBindWithAS(const InitArg& arg) : ArmorBindAction(arg) {}

ArmorBindWithAS::~ArmorBindWithAS() = default;

bool ArmorBindWithAS::init_(sead::Heap* heap) {
    return ArmorBindAction::init_(heap);
}

void ArmorBindWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    ArmorBindAction::enter_(params);
}

void ArmorBindWithAS::leave_() {
    ArmorBindAction::leave_();
}

void ArmorBindWithAS::loadParams_() {
    ArmorBindAction::loadParams_();
    getDynamicParam(&mASName_d, "ASName");
}

void ArmorBindWithAS::calc_() {
    ArmorBindAction::calc_();
}

}  // namespace uking::action
