#include "Game/AI/Action/actionDemoGetWeapon.h"

namespace uking::action {

DemoGetWeapon::DemoGetWeapon(const InitArg& arg) : DemoGetItem(arg) {}

DemoGetWeapon::~DemoGetWeapon() = default;

bool DemoGetWeapon::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetWeapon::enter_(ksys::act::ai::InlineParamPack* params) {
    DemoGetItem::enter_(params);
}

void DemoGetWeapon::leave_() {
    DemoGetItem::leave_();
}

void DemoGetWeapon::loadParams_() {
    DemoGetItem::loadParams_();
}

void DemoGetWeapon::calc_() {
    DemoGetItem::calc_();
}

}  // namespace uking::action
