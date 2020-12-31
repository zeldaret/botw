#include "Game/AI/AI/aiGolemPartRoot.h"

namespace uking::ai {

GolemPartRoot::GolemPartRoot(const InitArg& arg) : ReuseBulletPartsRoot(arg) {}

GolemPartRoot::~GolemPartRoot() = default;

bool GolemPartRoot::init_(sead::Heap* heap) {
    return ReuseBulletPartsRoot::init_(heap);
}

void GolemPartRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ReuseBulletPartsRoot::enter_(params);
}

void GolemPartRoot::leave_() {
    ReuseBulletPartsRoot::leave_();
}

void GolemPartRoot::loadParams_() {
    ReuseBulletPartsRoot::loadParams_();
    getStaticParam(&mChemFieldScale_s, "ChemFieldScale");
    getStaticParam(&mNormalAS_s, "NormalAS");
    getStaticParam(&mActiveAS_s, "ActiveAS");
    getAITreeVariable(&mGolemPartInitialIceMagic_a, "GolemPartInitialIceMagic");
    getAITreeVariable(&mGolemPartInitialBurn_a, "GolemPartInitialBurn");
}

}  // namespace uking::ai
