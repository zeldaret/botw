#include "Game/AI/Action/actionMimicFreeze.h"

namespace uking::action {

MimicFreeze::MimicFreeze(const InitArg& arg) : Freeze(arg) {}

MimicFreeze::~MimicFreeze() = default;

void MimicFreeze::enter_(ksys::act::ai::InlineParamPack* params) {
    Freeze::enter_(params);
}

void MimicFreeze::leave_() {
    Freeze::leave_();
}

void MimicFreeze::loadParams_() {
    Freeze::loadParams_();
}

}  // namespace uking::action
