#include "Game/AI/Action/actionWildHorseCreate.h"

namespace uking::action {

WildHorseCreate::WildHorseCreate(const InitArg& arg) : ksys::act::ai::Action(arg) {}

WildHorseCreate::~WildHorseCreate() = default;

bool WildHorseCreate::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void WildHorseCreate::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void WildHorseCreate::leave_() {
    ksys::act::ai::Action::leave_();
}

void WildHorseCreate::loadParams_() {
    getStaticParam(&mMinCreateNum_s, "MinCreateNum");
    getStaticParam(&mMaxCreateNum_s, "MaxCreateNum");
    getMapUnitParam(&mWildHorseCreateNum_m, "WildHorseCreateNum");
}

void WildHorseCreate::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
