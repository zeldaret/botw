#include "Game/AI/AI/aiDungeonRotateTag4WindApp.h"

namespace uking::ai {

DungeonRotateTag4WindApp::DungeonRotateTag4WindApp(const InitArg& arg)
    : WholeDungeonRotateTag(arg) {}

DungeonRotateTag4WindApp::~DungeonRotateTag4WindApp() = default;

bool DungeonRotateTag4WindApp::init_(sead::Heap* heap) {
    return WholeDungeonRotateTag::init_(heap);
}

void DungeonRotateTag4WindApp::enter_(ksys::act::ai::InlineParamPack* params) {
    WholeDungeonRotateTag::enter_(params);
}

void DungeonRotateTag4WindApp::leave_() {
    WholeDungeonRotateTag::leave_();
}

void DungeonRotateTag4WindApp::loadParams_() {
    WholeDungeonRotateTag::loadParams_();
}

}  // namespace uking::ai
