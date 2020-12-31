#include "Game/AI/AI/aiHorse.h"

namespace uking::ai {

Horse::Horse(const InitArg& arg) : ksys::act::ai::Ai(arg) {}

Horse::~Horse() = default;

void Horse::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void Horse::leave_() {
    ksys::act::ai::Ai::leave_();
}

void Horse::loadParams_() {
    getStaticParam(&mDistanceFall_s, "DistanceFall");
    getStaticParam(&mDistanceFallDie_s, "DistanceFallDie");
}

}  // namespace uking::ai
