#include "Game/AI/AI/aiLastBossThunderRoot.h"

namespace uking::ai {

LastBossThunderRoot::LastBossThunderRoot(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

LastBossThunderRoot::~LastBossThunderRoot() = default;

bool LastBossThunderRoot::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LastBossThunderRoot::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LastBossThunderRoot::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LastBossThunderRoot::loadParams_() {}

}  // namespace uking::ai
