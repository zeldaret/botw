#include "Game/AI/AI/aiWolfLinkShiekSensorRoot.h"

namespace uking::ai {

WolfLinkShiekSensorRoot::WolfLinkShiekSensorRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

WolfLinkShiekSensorRoot::~WolfLinkShiekSensorRoot() = default;

bool WolfLinkShiekSensorRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void WolfLinkShiekSensorRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void WolfLinkShiekSensorRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void WolfLinkShiekSensorRoot::loadParams_() {
    getStaticParam(&mDistanceUntilUpdateTarget_s, "DistanceUntilUpdateTarget");
    getDynamicParam(&mUpdateTarget_d, "UpdateTarget");
}

}  // namespace uking::ai
