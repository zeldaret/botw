#include "Game/AI/Action/actionReserveParashawlStart.h"

namespace uking::action {

ReserveParashawlStart::ReserveParashawlStart(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ReserveParashawlStart::~ReserveParashawlStart() = default;

bool ReserveParashawlStart::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ReserveParashawlStart::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ReserveParashawlStart::leave_() {
    ksys::act::ai::Action::leave_();
}

void ReserveParashawlStart::loadParams_() {}

void ReserveParashawlStart::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
