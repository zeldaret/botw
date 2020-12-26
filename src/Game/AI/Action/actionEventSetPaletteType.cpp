#include "Game/AI/Action/actionEventSetPaletteType.h"

namespace uking::action {

EventSetPaletteType::EventSetPaletteType(const InitArg& arg) : ksys::act::ai::Action(arg) {}

EventSetPaletteType::~EventSetPaletteType() = default;

bool EventSetPaletteType::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void EventSetPaletteType::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void EventSetPaletteType::leave_() {
    ksys::act::ai::Action::leave_();
}

void EventSetPaletteType::loadParams_() {
    getDynamicParam(&mPaletteType_d, "PaletteType");
    getDynamicParam(&mChangeFrame_d, "ChangeFrame");
    getDynamicParam(&mEndFrame_d, "EndFrame");
    getDynamicParam(&mSpeed_d, "Speed");
}

void EventSetPaletteType::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
