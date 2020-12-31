#include "Game/AI/AI/aiYunBoCannonBallRoot.h"

namespace uking::ai {

YunBoCannonBallRoot::YunBoCannonBallRoot(const InitArg& arg) : CannonBallRoot(arg) {}

YunBoCannonBallRoot::~YunBoCannonBallRoot() = default;

bool YunBoCannonBallRoot::init_(sead::Heap* heap) {
    return CannonBallRoot::init_(heap);
}

void YunBoCannonBallRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    CannonBallRoot::enter_(params);
}

void YunBoCannonBallRoot::leave_() {
    CannonBallRoot::leave_();
}

void YunBoCannonBallRoot::loadParams_() {
    CannonBallRoot::loadParams_();
    getMapUnitParam(&mCannonSpot_m, "CannonSpot");
}

}  // namespace uking::ai
