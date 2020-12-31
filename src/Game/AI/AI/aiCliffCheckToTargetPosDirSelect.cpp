#include "Game/AI/AI/aiCliffCheckToTargetPosDirSelect.h"

namespace uking::ai {

CliffCheckToTargetPosDirSelect::CliffCheckToTargetPosDirSelect(const InitArg& arg)
    : CliffCheckSelect(arg) {}

CliffCheckToTargetPosDirSelect::~CliffCheckToTargetPosDirSelect() = default;

bool CliffCheckToTargetPosDirSelect::init_(sead::Heap* heap) {
    return CliffCheckSelect::init_(heap);
}

void CliffCheckToTargetPosDirSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    CliffCheckSelect::enter_(params);
}

void CliffCheckToTargetPosDirSelect::leave_() {
    CliffCheckSelect::leave_();
}

void CliffCheckToTargetPosDirSelect::loadParams_() {
    CliffCheckSelect::loadParams_();
}

}  // namespace uking::ai
