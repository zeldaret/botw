#include "Game/AI/Action/actionDemoMotorcyclePutMaterials.h"

namespace uking::action {

DemoMotorcyclePutMaterials::DemoMotorcyclePutMaterials(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

DemoMotorcyclePutMaterials::~DemoMotorcyclePutMaterials() = default;

bool DemoMotorcyclePutMaterials::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void DemoMotorcyclePutMaterials::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void DemoMotorcyclePutMaterials::leave_() {
    ksys::act::ai::Action::leave_();
}

void DemoMotorcyclePutMaterials::loadParams_() {
    getStaticParam(&mCloseSaddleFramesSincePut_s, "CloseSaddleFramesSincePut");
    getStaticParam(&mFinishCookFramesSincePut_s, "FinishCookFramesSincePut");
    getStaticParam(&mCloseSaddleFramesSincePutFairy_s, "CloseSaddleFramesSincePutFairy");
    getStaticParam(&mFinishCookFramesSincePutFairy_s, "FinishCookFramesSincePutFairy");
}

void DemoMotorcyclePutMaterials::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
