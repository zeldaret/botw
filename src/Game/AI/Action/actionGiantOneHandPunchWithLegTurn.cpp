#include "Game/AI/Action/actionGiantOneHandPunchWithLegTurn.h"

namespace uking::action {

GiantOneHandPunchWithLegTurn::GiantOneHandPunchWithLegTurn(const InitArg& arg)
    : GiantOneHandActionWithLegTurn(arg) {}

GiantOneHandPunchWithLegTurn::~GiantOneHandPunchWithLegTurn() = default;

bool GiantOneHandPunchWithLegTurn::init_(sead::Heap* heap) {
    return GiantOneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandPunchWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantOneHandActionWithLegTurn::enter_(params);
}

void GiantOneHandPunchWithLegTurn::leave_() {
    GiantOneHandActionWithLegTurn::leave_();
}

void GiantOneHandPunchWithLegTurn::loadParams_() {
    GiantOneHandActionWithLegTurn::loadParams_();
    // FIXME: CALL sub_7100704D84 @ 0x7100704d84
}

void GiantOneHandPunchWithLegTurn::calc_() {
    GiantOneHandActionWithLegTurn::calc_();
}

}  // namespace uking::action
