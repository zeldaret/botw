#include "Game/AI/AI/aiPickShootItemRoot.h"

namespace uking::ai {

PickShootItemRoot::PickShootItemRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

PickShootItemRoot::~PickShootItemRoot() = default;

void PickShootItemRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void PickShootItemRoot::loadParams_() {
    getStaticParam(&mRemainTime_s, "RemainTime");
}

}  // namespace uking::ai
