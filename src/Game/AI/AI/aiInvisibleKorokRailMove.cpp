#include "Game/AI/AI/aiInvisibleKorokRailMove.h"

namespace uking::ai {

InvisibleKorokRailMove::InvisibleKorokRailMove(const InitArg& arg) : KorokRailMove(arg) {}

InvisibleKorokRailMove::~InvisibleKorokRailMove() = default;

bool InvisibleKorokRailMove::init_(sead::Heap* heap) {
    return KorokRailMove::init_(heap);
}

void InvisibleKorokRailMove::enter_(ksys::act::ai::InlineParamPack* params) {
    KorokRailMove::enter_(params);
}

void InvisibleKorokRailMove::leave_() {
    KorokRailMove::leave_();
}

void InvisibleKorokRailMove::loadParams_() {
    KorokRailMove::loadParams_();
}

}  // namespace uking::ai
