#include "Game/AI/AI/aiGanonThrowMultiActorRoot.h"

namespace uking::ai {

GanonThrowMultiActorRoot::GanonThrowMultiActorRoot(const InitArg& arg) : GanonThrowActorRoot(arg) {}

GanonThrowMultiActorRoot::~GanonThrowMultiActorRoot() = default;

bool GanonThrowMultiActorRoot::init_(sead::Heap* heap) {
    return GanonThrowActorRoot::init_(heap);
}

void GanonThrowMultiActorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    GanonThrowActorRoot::enter_(params);
}

void GanonThrowMultiActorRoot::leave_() {
    GanonThrowActorRoot::leave_();
}

void GanonThrowMultiActorRoot::loadParams_() {
    GanonThrowActorRoot::loadParams_();
    getStaticParam(&mPartsName1_s, "PartsName1");
    getStaticParam(&mPartsName2_s, "PartsName2");
    getStaticParam(&mPartsName3_s, "PartsName3");
    getStaticParam(&mPartsName4_s, "PartsName4");
    getStaticParam(&mPartsName5_s, "PartsName5");
    getStaticParam(&mPartsName6_s, "PartsName6");
    getStaticParam(&mPartsName7_s, "PartsName7");
    getStaticParam(&mPartsName8_s, "PartsName8");
}

}  // namespace uking::ai
