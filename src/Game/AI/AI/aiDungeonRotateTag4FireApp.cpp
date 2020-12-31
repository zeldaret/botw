#include "Game/AI/AI/aiDungeonRotateTag4FireApp.h"

namespace uking::ai {

DungeonRotateTag4FireApp::DungeonRotateTag4FireApp(const InitArg& arg)
    : WholeDungeonRotateTag(arg) {}

DungeonRotateTag4FireApp::~DungeonRotateTag4FireApp() = default;

bool DungeonRotateTag4FireApp::init_(sead::Heap* heap) {
    return WholeDungeonRotateTag::init_(heap);
}

void DungeonRotateTag4FireApp::enter_(ksys::act::ai::InlineParamPack* params) {
    WholeDungeonRotateTag::enter_(params);
}

void DungeonRotateTag4FireApp::leave_() {
    WholeDungeonRotateTag::leave_();
}

void DungeonRotateTag4FireApp::loadParams_() {
    WholeDungeonRotateTag::loadParams_();
}

}  // namespace uking::ai
