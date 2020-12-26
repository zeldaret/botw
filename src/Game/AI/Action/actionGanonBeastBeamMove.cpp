#include "Game/AI/Action/actionGanonBeastBeamMove.h"

namespace uking::action {

GanonBeastBeamMove::GanonBeastBeamMove(const InitArg& arg) : SimpleLineBeam(arg) {}

GanonBeastBeamMove::~GanonBeastBeamMove() = default;

bool GanonBeastBeamMove::init_(sead::Heap* heap) {
    return SimpleLineBeam::init_(heap);
}

void GanonBeastBeamMove::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleLineBeam::enter_(params);
}

void GanonBeastBeamMove::leave_() {
    SimpleLineBeam::leave_();
}

void GanonBeastBeamMove::loadParams_() {
    SimpleLineBeam::loadParams_();
    getStaticParam(&mRestDistTime_s, "RestDistTime");
    getStaticParam(&mRestDistTimeAdd_s, "RestDistTimeAdd");
    getStaticParam(&mRestNumMax_s, "RestNumMax");
    getStaticParam(&mRestDistLimit_s, "RestDistLimit");
    getStaticParam(&mRestDistMinLimit_s, "RestDistMinLimit");
    getStaticParam(&mRestDistInterval_s, "RestDistInterval");
    getStaticParam(&mRestActor_s, "RestActor");
}

void GanonBeastBeamMove::calc_() {
    SimpleLineBeam::calc_();
}

}  // namespace uking::action
