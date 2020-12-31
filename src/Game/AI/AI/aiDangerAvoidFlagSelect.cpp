#include "Game/AI/AI/aiDangerAvoidFlagSelect.h"

namespace uking::ai {

DangerAvoidFlagSelect::DangerAvoidFlagSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DangerAvoidFlagSelect::~DangerAvoidFlagSelect() = default;

void DangerAvoidFlagSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DangerAvoidFlagSelect::loadParams_() {}

}  // namespace uking::ai
