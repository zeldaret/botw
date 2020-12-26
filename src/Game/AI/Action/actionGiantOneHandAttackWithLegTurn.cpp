#include "Game/AI/Action/actionGiantOneHandAttackWithLegTurn.h"

namespace uking::action {

GiantOneHandAttackWithLegTurn::GiantOneHandAttackWithLegTurn(const InitArg& arg)
    : GiantOneHandActionWithLegTurn(arg) {}

GiantOneHandAttackWithLegTurn::~GiantOneHandAttackWithLegTurn() = default;

bool GiantOneHandAttackWithLegTurn::init_(sead::Heap* heap) {
    return GiantOneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandAttackWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantOneHandActionWithLegTurn::enter_(params);
}

void GiantOneHandAttackWithLegTurn::leave_() {
    GiantOneHandActionWithLegTurn::leave_();
}

void GiantOneHandAttackWithLegTurn::loadParams_() {
    GiantOneHandActionWithLegTurn::loadParams_();
    // FIXME: CALL sub_71007050F0 @ 0x71007050f0
}

void GiantOneHandAttackWithLegTurn::calc_() {
    GiantOneHandActionWithLegTurn::calc_();
}

}  // namespace uking::action
