#include "Game/AI/Action/actionCarriedNoHit.h"

namespace uking::action {

CarriedNoHit::CarriedNoHit(const InitArg& arg) : Carried(arg) {}

CarriedNoHit::~CarriedNoHit() = default;

void CarriedNoHit::enter_(ksys::act::ai::InlineParamPack* params) {
    Carried::enter_(params);
}

void CarriedNoHit::leave_() {
    Carried::leave_();
}

}  // namespace uking::action
