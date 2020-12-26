#include "Game/AI/Action/actionDungeonRotateApp.h"

namespace uking::action {

DungeonRotateApp::DungeonRotateApp(const InitArg& arg) : DungeonRotateBase(arg) {}

DungeonRotateApp::~DungeonRotateApp() = default;

bool DungeonRotateApp::init_(sead::Heap* heap) {
    return DungeonRotateBase::init_(heap);
}

void DungeonRotateApp::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateBase::enter_(params);
}

void DungeonRotateApp::leave_() {
    DungeonRotateBase::leave_();
}

void DungeonRotateApp::loadParams_() {
    DungeonRotateBase::loadParams_();
    getStaticParam(&mRotDirType_s, "RotDirType");
    getDynamicParam(&mDynTargetAng_d, "DynTargetAng");
}

void DungeonRotateApp::calc_() {
    DungeonRotateBase::calc_();
}

}  // namespace uking::action
