#include "Game/AI/Action/actionEventOpenGetWeaponDemo.h"

namespace uking::action {

EventOpenGetWeaponDemo::EventOpenGetWeaponDemo(const InitArg& arg) : EventOpenGetDemo(arg) {}

EventOpenGetWeaponDemo::~EventOpenGetWeaponDemo() = default;

void EventOpenGetWeaponDemo::calc_() {
    EventOpenGetDemo::calc_();
}

}  // namespace uking::action
