#include "Game/AI/AI/aiDungeonRotateTag4WaterApp.h"

namespace uking::ai {

DungeonRotateTag4WaterApp::DungeonRotateTag4WaterApp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag4WaterApp::~DungeonRotateTag4WaterApp() = default;

bool DungeonRotateTag4WaterApp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag4WaterApp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTag4WaterApp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag4WaterApp::loadParams_() {
    getStaticParam(&mLv0_s, "Lv0");
    getStaticParam(&mLv1_s, "Lv1");
    getStaticParam(&mLv2_s, "Lv2");
    getStaticParam(&mLv3_s, "Lv3");
    getStaticParam(&mLv4_s, "Lv4");
    getStaticParam(&mLv5_s, "Lv5");
    getStaticParam(&mLv6_s, "Lv6");
    getStaticParam(&mLv7_s, "Lv7");
    getStaticParam(&mLv8_s, "Lv8");
    getStaticParam(&mLv9_s, "Lv9");
    getAITreeVariable(&mTargetRad_a, "TargetRad");
    getAITreeVariable(&mTargetRadMax_a, "TargetRadMax");
    getAITreeVariable(&mTargetRadMin_a, "TargetRadMin");
}

}  // namespace uking::ai
