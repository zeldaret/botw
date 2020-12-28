#include "Game/AI/Action/actionDisableAutoSavePausing.h"

namespace uking::action {

DisableAutoSavePausing::DisableAutoSavePausing(const InitArg& arg) : ksys::act::ai::Action(arg) {}

DisableAutoSavePausing::~DisableAutoSavePausing() = default;

bool DisableAutoSavePausing::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DisableAutoSavePausing::loadParams_() {}

}  // namespace uking::action
