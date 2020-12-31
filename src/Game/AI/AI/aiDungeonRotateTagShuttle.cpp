#include "Game/AI/AI/aiDungeonRotateTagShuttle.h"

namespace uking::ai {

DungeonRotateTagShuttle::DungeonRotateTagShuttle(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

DungeonRotateTagShuttle::~DungeonRotateTagShuttle() = default;

bool DungeonRotateTagShuttle::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void DungeonRotateTagShuttle::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void DungeonRotateTagShuttle::leave_() {
    ksys::act::ai::Ai::leave_();
}

void DungeonRotateTagShuttle::loadParams_() {
    getMapUnitParam(&mInitDgnRotRad_m, "InitDgnRotRad");
}

}  // namespace uking::ai
