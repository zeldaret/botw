#include "Game/AI/Action/actionEventOpenGetWeaponDemo.h"

namespace uking::action {

EventOpenGetWeaponDemo::EventOpenGetWeaponDemo(const InitArg& arg) : EventOpenGetDemo(arg) {}

EventOpenGetWeaponDemo::~EventOpenGetWeaponDemo() = default;

bool EventOpenGetWeaponDemo::init_(sead::Heap* heap) {
    return EventOpenGetDemo::init_(heap);
}

void EventOpenGetWeaponDemo::enter_(ksys::act::ai::InlineParamPack* params) {
    EventOpenGetDemo::enter_(params);
}

void EventOpenGetWeaponDemo::leave_() {
    EventOpenGetDemo::leave_();
}

void EventOpenGetWeaponDemo::loadParams_() {
    getDynamicParam(&mIsInvalidOpenPouch_d, "IsInvalidOpenPouch");
}

void EventOpenGetWeaponDemo::calc_() {
    EventOpenGetDemo::calc_();
}

}  // namespace uking::action
