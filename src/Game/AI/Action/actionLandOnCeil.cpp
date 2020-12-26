#include "Game/AI/Action/actionLandOnCeil.h"

namespace uking::action {

LandOnCeil::LandOnCeil(const InitArg& arg) : ksys::act::ai::Action(arg) {}

LandOnCeil::~LandOnCeil() = default;

bool LandOnCeil::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void LandOnCeil::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void LandOnCeil::leave_() {
    ksys::act::ai::Action::leave_();
}

void LandOnCeil::loadParams_() {
    getStaticParam(&mRotRatio_s, "RotRatio");
    getStaticParam(&mGravityScale_s, "GravityScale");
    getMapUnitParam(&mIsCreateOnFace_m, "IsCreateOnFace");
}

void LandOnCeil::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
