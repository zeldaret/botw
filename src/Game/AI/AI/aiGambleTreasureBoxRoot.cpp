#include "Game/AI/AI/aiGambleTreasureBoxRoot.h"

namespace uking::ai {

GambleTreasureBoxRoot::GambleTreasureBoxRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GambleTreasureBoxRoot::~GambleTreasureBoxRoot() = default;

bool GambleTreasureBoxRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GambleTreasureBoxRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GambleTreasureBoxRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GambleTreasureBoxRoot::loadParams_() {
    getAITreeVariable(&mIsOpenTreasureBox_a, "IsOpenTreasureBox");
    getAITreeVariable(&mDropActorName_a, "DropActorName");
}

}  // namespace uking::ai
