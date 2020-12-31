#include "Game/AI/AI/aiDragonIceRoot.h"

namespace uking::ai {

DragonIceRoot::DragonIceRoot(const InitArg& arg) : DragonRoot(arg) {}

DragonIceRoot::~DragonIceRoot() = default;

bool DragonIceRoot::init_(sead::Heap* heap) {
    return DragonRoot::init_(heap);
}

void DragonIceRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    DragonRoot::enter_(params);
}

void DragonIceRoot::leave_() {
    DragonRoot::leave_();
}

void DragonIceRoot::loadParams_() {
    DragonRoot::loadParams_();
    getStaticParam(&mGrudgeBulletMaxNum_s, "GrudgeBulletMaxNum");
    getStaticParam(&mGrudgeBulletMinInterval_s, "GrudgeBulletMinInterval");
    getStaticParam(&mGrudgeSmokeTime_s, "GrudgeSmokeTime");
    getStaticParam(&mGrudgeEventRail_pre1stSpeed_s, "GrudgeEventRail_pre1stSpeed");
    getStaticParam(&mGrudgeEventRail_1stSpeed_s, "GrudgeEventRail_1stSpeed");
    getStaticParam(&mGrudgeEventRail_pre2ndSpeed_s, "GrudgeEventRail_pre2ndSpeed");
    getStaticParam(&mGrudgeEventRail_2ndSpeed_s, "GrudgeEventRail_2ndSpeed");
    getStaticParam(&mGrudgeEventRail_pre3rdSpeed_s, "GrudgeEventRail_pre3rdSpeed");
    getStaticParam(&mGrudgeEventRail_3rdSpeed_s, "GrudgeEventRail_3rdSpeed");
    getStaticParam(&mGrudgeEventRail_preEndSpeed_s, "GrudgeEventRail_preEndSpeed");
    getStaticParam(&mGrudgeEventRail_EndSpeed_s, "GrudgeEventRail_EndSpeed");
    getStaticParam(&mGrudgeEventRail_ReturnSpeed_s, "GrudgeEventRail_ReturnSpeed");
    getStaticParam(&mGrudgeBulletRate_s, "GrudgeBulletRate");
    getStaticParam(&mGrudgeEventRail_Start_s, "GrudgeEventRail_Start");
    getStaticParam(&mGrudgeEventRail_pre1st_s, "GrudgeEventRail_pre1st");
    getStaticParam(&mGrudgeEventRail_1st_s, "GrudgeEventRail_1st");
    getStaticParam(&mGrudgeEventRail_pre2nd_s, "GrudgeEventRail_pre2nd");
    getStaticParam(&mGrudgeEventRail_2nd_s, "GrudgeEventRail_2nd");
    getStaticParam(&mGrudgeEventRail_pre3rd_s, "GrudgeEventRail_pre3rd");
    getStaticParam(&mGrudgeEventRail_3rd_s, "GrudgeEventRail_3rd");
    getStaticParam(&mGrudgeEventRail_preEnd_s, "GrudgeEventRail_preEnd");
    getStaticParam(&mGrudgeEventRail_End_s, "GrudgeEventRail_End");
    getStaticParam(&mGrudgeEventRail_ReturnToSky_s, "GrudgeEventRail_ReturnToSky");
    getStaticParam(&mGrudgeBulletActorName_s, "GrudgeBulletActorName");
}

}  // namespace uking::ai
