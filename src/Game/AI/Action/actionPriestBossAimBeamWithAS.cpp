#include "Game/AI/Action/actionPriestBossAimBeamWithAS.h"

namespace uking::action {

PriestBossAimBeamWithAS::PriestBossAimBeamWithAS(const InitArg& arg) : PriestBossAimBeam(arg) {}

PriestBossAimBeamWithAS::~PriestBossAimBeamWithAS() = default;

bool PriestBossAimBeamWithAS::init_(sead::Heap* heap) {
    return PriestBossAimBeam::init_(heap);
}

void PriestBossAimBeamWithAS::enter_(ksys::act::ai::InlineParamPack* params) {
    PriestBossAimBeam::enter_(params);
}

void PriestBossAimBeamWithAS::leave_() {
    PriestBossAimBeam::leave_();
}

void PriestBossAimBeamWithAS::loadParams_() {
    PriestBossAimBeam::loadParams_();
    getStaticParam(&mASName_s, "ASName");
}

void PriestBossAimBeamWithAS::calc_() {
    PriestBossAimBeam::calc_();
}

}  // namespace uking::action
