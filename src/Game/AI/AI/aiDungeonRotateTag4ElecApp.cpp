#include "Game/AI/AI/aiDungeonRotateTag4ElecApp.h"

namespace uking::ai {

DungeonRotateTag4ElecApp::DungeonRotateTag4ElecApp(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTag4ElecApp::~DungeonRotateTag4ElecApp() = default;

bool DungeonRotateTag4ElecApp::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTag4ElecApp::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTag4ElecApp::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTag4ElecApp::loadParams_() {
    getMapUnitParam(&mCtrlDgnRemainsElectricBodyPart_m, "CtrlDgnRemainsElectricBodyPart");
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
}

}  // namespace uking::ai
