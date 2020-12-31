#include "Game/AI/AI/aiPriestBossLineFormationAppear.h"

namespace uking::ai {

PriestBossLineFormationAppear::PriestBossLineFormationAppear(const InitArg& arg)
    : SeqTwoAction(arg) {}

PriestBossLineFormationAppear::~PriestBossLineFormationAppear() = default;

bool PriestBossLineFormationAppear::init_(sead::Heap* heap) {
    return SeqTwoAction::init_(heap);
}

void PriestBossLineFormationAppear::enter_(ksys::act::ai::InlineParamPack* params) {
    SeqTwoAction::enter_(params);
}

void PriestBossLineFormationAppear::leave_() {
    SeqTwoAction::leave_();
}

void PriestBossLineFormationAppear::loadParams_() {
    SeqTwoAction::loadParams_();
}

}  // namespace uking::ai
