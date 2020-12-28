#include "Game/AI/Action/actionChangePosture.h"

namespace uking::action {

ChangePosture::ChangePosture(const InitArg& arg) : ksys::act::ai::Action(arg) {}

ChangePosture::~ChangePosture() = default;

bool ChangePosture::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ChangePosture::loadParams_() {
    getDynamicParam(&mPosture_d, "Posture");
}

}  // namespace uking::action
