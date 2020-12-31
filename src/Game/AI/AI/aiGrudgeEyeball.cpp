#include "Game/AI/AI/aiGrudgeEyeball.h"

namespace uking::ai {

GrudgeEyeball::GrudgeEyeball(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

GrudgeEyeball::~GrudgeEyeball() = default;

bool GrudgeEyeball::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void GrudgeEyeball::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void GrudgeEyeball::leave_() {
    ksys::act::ai::Ai::leave_();
}

void GrudgeEyeball::loadParams_() {
    getMapUnitParam(&mEyeballFirstState_m, "EyeballFirstState");
}

}  // namespace uking::ai
