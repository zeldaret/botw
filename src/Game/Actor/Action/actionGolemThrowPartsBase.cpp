#include "Game/Actor/Action/actionGolemThrowPartsBase.h"

namespace uking::action {

GolemThrowPartsBase::GolemThrowPartsBase(const InitArg& arg) : ActionWithAS(arg) {}

GolemThrowPartsBase::~GolemThrowPartsBase() = default;

bool GolemThrowPartsBase::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemThrowPartsBase::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void GolemThrowPartsBase::leave_() {
    ActionWithAS::leave_();
}

void GolemThrowPartsBase::loadParams_() {
    StopBase::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemThrowPartsBase::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
