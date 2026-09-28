#include "Game/Actor/Action/actionGiantOneHandPunchWithLegTurn.h"

namespace uking::action {

GiantOneHandPunchWithLegTurn::GiantOneHandPunchWithLegTurn(const InitArg& arg)
    : OneHandActionWithLegTurn(arg) {}

GiantOneHandPunchWithLegTurn::~GiantOneHandPunchWithLegTurn() = default;

bool GiantOneHandPunchWithLegTurn::init_(sead::Heap* heap) {
    return OneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandPunchWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    OneHandActionWithLegTurn::enter_(params);
}

void GiantOneHandPunchWithLegTurn::leave_() {
    OneHandActionWithLegTurn::leave_();
}

void GiantOneHandPunchWithLegTurn::loadParams_() {
    OneHandActionWithLegTurn::loadParams_();
    // FIXME: CALL sub_7100704D84 @ 0x7100704d84
}

void GiantOneHandPunchWithLegTurn::calc_() {
    OneHandActionWithLegTurn::calc_();
}

}  // namespace uking::action
