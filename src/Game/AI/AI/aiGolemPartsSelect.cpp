#include "Game/AI/AI/aiGolemPartsSelect.h"

namespace uking::ai {

GolemPartsSelect::GolemPartsSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GolemPartsSelect::~GolemPartsSelect() = default;

bool GolemPartsSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GolemPartsSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GolemPartsSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GolemPartsSelect::loadParams_() {
    getStaticParam(&mArmRModelMatrialName_s, "ArmRModelMatrialName");
    getStaticParam(&mArmLModelMatrialName_s, "ArmLModelMatrialName");
}

}  // namespace uking::ai
