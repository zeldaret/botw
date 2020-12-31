#include "Game/AI/AI/aiAddBasicLinkOn.h"

namespace uking::ai {

AddBasicLinkOn::AddBasicLinkOn(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

AddBasicLinkOn::~AddBasicLinkOn() = default;

bool AddBasicLinkOn::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void AddBasicLinkOn::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void AddBasicLinkOn::leave_() {
    ksys::act::ai::Ai::leave_();
}

void AddBasicLinkOn::loadParams_() {
    getStaticParam(&mOnlyOne_s, "OnlyOne");
    getStaticParam(&mIsBroadCastOnlyOne_s, "IsBroadCastOnlyOne");
}

}  // namespace uking::ai
