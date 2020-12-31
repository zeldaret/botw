#include "Game/AI/AI/aiGiantNavMoveWithFirstAction.h"

namespace uking::ai {

GiantNavMoveWithFirstAction::GiantNavMoveWithFirstAction(const InitArg& arg)
    : GiantNavMoveTarget(arg) {}

GiantNavMoveWithFirstAction::~GiantNavMoveWithFirstAction() = default;

bool GiantNavMoveWithFirstAction::init_(sead::Heap* heap) {
    return GiantNavMoveTarget::init_(heap);
}

void GiantNavMoveWithFirstAction::enter_(ksys::act::ai::InlineParamPack* params) {
    GiantNavMoveTarget::enter_(params);
}

void GiantNavMoveWithFirstAction::leave_() {
    GiantNavMoveTarget::leave_();
}

void GiantNavMoveWithFirstAction::loadParams_() {
    GiantNavMoveTarget::loadParams_();
}

}  // namespace uking::ai
