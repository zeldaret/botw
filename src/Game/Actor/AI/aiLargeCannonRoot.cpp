#include "Game/Actor/AI/aiLargeCannonRoot.h"

namespace uking::ai {

LargeCannonRoot::LargeCannonRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

bool LargeCannonRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LargeCannonRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LargeCannonRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LargeCannonRoot::loadParams_() {
    getStaticParam(&mSearchMaxDist_s, "SearchMaxDist");
    getStaticParam(&mSearchMinDist_s, "SearchMinDist");
    getStaticParam(&mSearchDistMargin_s, "SearchDistMargin");
}

}  // namespace uking::ai
