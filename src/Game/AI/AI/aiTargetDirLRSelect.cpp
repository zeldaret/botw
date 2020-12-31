#include "Game/AI/AI/aiTargetDirLRSelect.h"

namespace uking::ai {

TargetDirLRSelect::TargetDirLRSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

TargetDirLRSelect::~TargetDirLRSelect() = default;

void TargetDirLRSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

}  // namespace uking::ai
