#include "Game/Actor/Action/actionGiantOneHandAttackWithLegTurn.h"

namespace uking::action {

GiantOneHandAttackWithLegTurn::GiantOneHandAttackWithLegTurn(const InitArg& arg)
    : OneHandActionWithLegTurn(arg) {}

GiantOneHandAttackWithLegTurn::~GiantOneHandAttackWithLegTurn() = default;

bool GiantOneHandAttackWithLegTurn::init_(sead::Heap* heap) {
    return OneHandActionWithLegTurn::init_(heap);
}

void GiantOneHandAttackWithLegTurn::enter_(ksys::act::ai::InlineParamPack* params) {
    OneHandActionWithLegTurn::enter_(params);
}

void GiantOneHandAttackWithLegTurn::leave_() {
    OneHandActionWithLegTurn::leave_();
}

void GiantOneHandAttackWithLegTurn::loadParams_() {
    OneHandActionWithLegTurn::loadParams_();
    // FIXME: CALL sub_71007050F0 @ 0x71007050f0
}

void GiantOneHandAttackWithLegTurn::calc_() {
    OneHandActionWithLegTurn::calc_();
}

}  // namespace uking::action
