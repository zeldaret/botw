#include "Game/AI/Action/actionEventSetSkyPaletteType.h"

namespace uking::action {

EventSetSkyPaletteType::EventSetSkyPaletteType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetSkyPaletteType::~EventSetSkyPaletteType() = default;

bool EventSetSkyPaletteType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetSkyPaletteType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetSkyPaletteType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetSkyPaletteType::loadParams_() {
    getDynamicParam(&mSkyPalette_d, "SkyPalette");
}

void EventSetSkyPaletteType::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
