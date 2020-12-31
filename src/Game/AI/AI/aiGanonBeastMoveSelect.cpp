#include "Game/AI/AI/aiGanonBeastMoveSelect.h"

namespace uking::ai {

GanonBeastMoveSelect::GanonBeastMoveSelect(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GanonBeastMoveSelect::~GanonBeastMoveSelect() = default;

bool GanonBeastMoveSelect::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GanonBeastMoveSelect::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GanonBeastMoveSelect::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GanonBeastMoveSelect::loadParams_() {
    getStaticParam(&mDist_s, "Dist");
    getStaticParam(&mIsMoveFinishEnd_s, "IsMoveFinishEnd");
    getStaticParam(&mCentralPoint_s, "CentralPoint");
    getStaticParam(&mFrontOffset_s, "FrontOffset");
    getStaticParam(&mWallDist_s, "WallDist");
}

}  // namespace uking::ai
