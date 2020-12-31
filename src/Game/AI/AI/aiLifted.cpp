#include "Game/AI/AI/aiLifted.h"

namespace uking::ai {

Lifted::Lifted(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Lifted::~Lifted() = default;

void Lifted::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Lifted::leave_() {
    ksys::act::ai::Ai::leave_();
}

void Lifted::loadParams_() {
    getStaticParam(&mIsGetItem_s, "IsGetItem");
}

}  // namespace uking::ai
