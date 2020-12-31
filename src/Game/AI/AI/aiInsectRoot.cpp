#include "Game/AI/AI/aiInsectRoot.h"

namespace uking::ai {

InsectRoot::InsectRoot(const InitArg& arg) : SimpleWildlifeRoot(arg) {}

InsectRoot::~InsectRoot() = default;

bool InsectRoot::init_(sead::Heap* heap) {
    return SimpleWildlifeRoot::init_(heap);
}

void InsectRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    SimpleWildlifeRoot::enter_(params);
}

void InsectRoot::leave_() {
    SimpleWildlifeRoot::leave_();
}

void InsectRoot::loadParams_() {
    SimpleWildlifeRoot::loadParams_();
    getStaticParam(&mIsEscapeInWater_s, "IsEscapeInWater");
}

}  // namespace uking::ai
