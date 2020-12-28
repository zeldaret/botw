#include "Game/AI/Action/actionIgniteToTargetDir.h"

namespace uking::action {

IgniteToTargetDir::IgniteToTargetDir(const InitArg& arg) : IgniteToTargetSimple(arg) {}

IgniteToTargetDir::~IgniteToTargetDir() = default;

void IgniteToTargetDir::loadParams_() {
    IgniteToTargetSimple::loadParams_();
}

}  // namespace uking::action
