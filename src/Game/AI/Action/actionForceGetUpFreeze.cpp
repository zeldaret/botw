#include "Game/AI/Action/actionForceGetUpFreeze.h"

namespace uking::action {

ForceGetUpFreeze::ForceGetUpFreeze(const InitArg& arg) : Freeze(arg) {}

ForceGetUpFreeze::~ForceGetUpFreeze() = default;

bool ForceGetUpFreeze::init_(sead::Heap* heap) {
    return Freeze::init_(heap);
}

void ForceGetUpFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void ForceGetUpFreeze::leave_() {
    Freeze::leave_();
}

void ForceGetUpFreeze::loadParams_() {
    Freeze::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void ForceGetUpFreeze::calc_() {
    Freeze::calc_();
}

}  // namespace uking::action
