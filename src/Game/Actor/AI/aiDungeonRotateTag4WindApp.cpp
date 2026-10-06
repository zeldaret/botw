#include "Game/Actor/AI/aiDungeonRotateTag4WindApp.h"

namespace uking::ai {

DungeonRotateTag4WindApp::DungeonRotateTag4WindApp(const InitArg& arg) : DungeonRotateTagApp(arg) {}

DungeonRotateTag4WindApp::~DungeonRotateTag4WindApp() = default;

bool DungeonRotateTag4WindApp::init_(sead::Heap* heap) {
    return DungeonRotateTagApp::init_(heap);
}

void DungeonRotateTag4WindApp::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateTagApp::enter_(params);
}

void DungeonRotateTag4WindApp::leave_() {
    DungeonRotateTagApp::leave_();
}

void DungeonRotateTag4WindApp::loadParams_() {
    DungeonRotateTagApp::loadParams_();
}

}  // namespace uking::ai
