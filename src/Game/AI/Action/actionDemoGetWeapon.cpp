#include "Game/AI/Action/actionDemoGetWeapon.h"

namespace uking::action {

DemoGetWeapon::DemoGetWeapon(const InitArg& arg) : DemoGetItem(arg) {}

DemoGetWeapon::~DemoGetWeapon() = default;

bool DemoGetWeapon::init_(sead::Heap* heap) {
    return DemoGetItem::init_(heap);
}

void DemoGetWeapon::loadParams_() {
    DemoGetItem::loadParams_();
}

}  // namespace uking::action
