#include "Game/AI/AI/aiGanonDemoMoveSeqTwoAction.h"

namespace uking::ai {

GanonDemoMoveSeqTwoAction::GanonDemoMoveSeqTwoAction(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonDemoMoveSeqTwoAction::~GanonDemoMoveSeqTwoAction() = default;

bool GanonDemoMoveSeqTwoAction::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonDemoMoveSeqTwoAction::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonDemoMoveSeqTwoAction::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonDemoMoveSeqTwoAction::loadParams_() {}

}  // namespace uking::ai
