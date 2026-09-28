#include "Game/Actor/AI/aiDungeonRotateTag4FireApp.h"

namespace uking::ai {

DungeonRotateTag4FireApp::DungeonRotateTag4FireApp(const InitArg& arg) : DungeonRotateTagApp(arg) {}

DungeonRotateTag4FireApp::~DungeonRotateTag4FireApp() = default;

bool DungeonRotateTag4FireApp::init_(sead::Heap* heap) {
    return DungeonRotateTagApp::init_(heap);
}

void DungeonRotateTag4FireApp::enter_(ksys::act::ai::InlineParamPack* params) {
    DungeonRotateTagApp::enter_(params);
}

void DungeonRotateTag4FireApp::leave_() {
    DungeonRotateTagApp::leave_();
}

void DungeonRotateTag4FireApp::loadParams_() {
    DungeonRotateTagApp::loadParams_();
}

}  // namespace uking::ai
