#include "Game/AI/Action/actionGiantArmorEquip.h"

namespace uking::action {

GiantArmorEquip::GiantArmorEquip(const InitArg& arg) : BindAction(arg) {}

GiantArmorEquip::~GiantArmorEquip() = default;

bool GiantArmorEquip::init_(sead::Heap* heap) {
    return BindAction::init_(heap);
}

void GiantArmorEquip::enter_(ksys::act::ai::InlineParamPack* params) {
    BindAction::enter_(params);
}

void GiantArmorEquip::leave_() {
    BindAction::leave_();
}

void GiantArmorEquip::loadParams_() {
    BindAction::loadParams_();
}

void GiantArmorEquip::calc_() {
    BindAction::calc_();
}

}  // namespace uking::action
