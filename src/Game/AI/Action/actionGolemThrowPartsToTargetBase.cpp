#include "Game/AI/Action/actionGolemThrowPartsToTargetBase.h"

namespace uking::action {

GolemThrowPartsToTargetBase::GolemThrowPartsToTargetBase(const InitArg& arg) : ActionWithAS(arg) {}

GolemThrowPartsToTargetBase::~GolemThrowPartsToTargetBase() = default;

bool GolemThrowPartsToTargetBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemThrowPartsToTargetBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void GolemThrowPartsToTargetBase::leave_() {
    ActionWithAS::leave_();
}

void GolemThrowPartsToTargetBase::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemThrowPartsToTargetBase::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
