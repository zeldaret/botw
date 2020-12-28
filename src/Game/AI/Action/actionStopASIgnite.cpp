#include "Game/AI/Action/actionStopASIgnite.h"

namespace uking::action {

StopASIgnite::StopASIgnite(const InitArg& arg) : OnetimeStopASPlay(arg) {}

bool StopASIgnite::init_(sead::Heap* heap) {
    return OnetimeStopASPlay::init_(heap);
}

void StopASIgnite::enter_(ksys::act::ai::InlineParamPack* params) {
    OnetimeStopASPlay::enter_(params);
}

void StopASIgnite::leave_() {
    OnetimeStopASPlay::leave_();
}

void StopASIgnite::loadParams_() {
    OnetimeStopASPlay::loadParams_();
    getStaticParam(&mIgniteSpeed_s, "IgniteSpeed");
    getStaticParam(&mIgniteOffset_s, "IgniteOffset");
    getStaticParam(&mIgniteVelocityDir_s, "IgniteVelocityDir");
    getStaticParam(&mIgniteRotate_s, "IgniteRotate");
    getStaticParam(&mIgniteRotSpeed_s, "IgniteRotSpeed");
    getDynamicParam(&mIgniteHandle_d, "IgniteHandle");
    getAITreeVariable(&mGeneratedActorLink_a, "GeneratedActorLink");
}

void StopASIgnite::calc_() {
    OnetimeStopASPlay::calc_();
}

}  // namespace uking::action
