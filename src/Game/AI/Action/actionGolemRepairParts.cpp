#include "Game/AI/Action/actionGolemRepairParts.h"

namespace uking::action {

GolemRepairParts::GolemRepairParts(const InitArg& arg) : ActionWithAS(arg) {}

GolemRepairParts::~GolemRepairParts() = default;

bool GolemRepairParts::init_(sead::Heap* heap) {
    return ActionWithAS::init_(heap);
}

void GolemRepairParts::enter_(ksys::act::ai::InlineParamPack* params) {
    ActionWithAS::enter_(params);
}

void GolemRepairParts::leave_() {
    ActionWithAS::leave_();
}

void GolemRepairParts::loadParams_() {
    ActionWithPosAngReduce::loadParams_();
    getStaticParam(&mASName_s, "ASName");
    getStaticParam(&mTgtBodyName_s, "TgtBodyName");
    getStaticParam(&mChmObjectName_s, "ChmObjectName");
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    // FIXME: CALL sub_71005E1BE8 @ 0x71005e1be8
    getAITreeVariable(&mGolemChemicalController_a, "GolemChemicalController");
}

void GolemRepairParts::calc_() {
    ActionWithAS::calc_();
}

}  // namespace uking::action
