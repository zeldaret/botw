#include "Game/AI/AI/aiGanonBeastRoot.h"

namespace uking::ai {

GanonBeastRoot::GanonBeastRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastRoot::~GanonBeastRoot() = default;

bool GanonBeastRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastRoot::loadParams_() {
    getStaticParam(&mGrudeInterval3_s, "GrudeInterval3");
    getStaticParam(&mGrudeInterval4_s, "GrudeInterval4");
    getStaticParam(&mGrudeInterval5_s, "GrudeInterval5");
    getStaticParam(&mGrudeCreateNum_s, "GrudeCreateNum");
    getStaticParam(&mWeakPointASSlot_s, "WeakPointASSlot");
    getStaticParam(&mGrudePlayerDist_s, "GrudePlayerDist");
    getStaticParam(&mGrudeRandRange_s, "GrudeRandRange");
    getStaticParam(&mGrudeCenterOffset_s, "GrudeCenterOffset");
    getStaticParam(&mInitWeakPointASName_s, "InitWeakPointASName");
    getStaticParam(&mGrudeRainObject_s, "GrudeRainObject");
    getStaticParam(&mGrudeRainObject2_s, "GrudeRainObject2");
    getAITreeVariable(&mWeakPointAliveFlag_a, "WeakPointAliveFlag");
    getAITreeVariable(&mWeakPointActiveFlag_a, "WeakPointActiveFlag");
    getAITreeVariable(&mIsGanonBeastAngry_a, "IsGanonBeastAngry");
}

}  // namespace uking::ai
