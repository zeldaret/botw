#include "Game/AI/AI/aiLimitedTimeredActorCreator.h"

namespace uking::ai {

LimitedTimeredActorCreator::LimitedTimeredActorCreator(const InitArg& arg)
    : ksys::act::ai::Ai(arg) {}

LimitedTimeredActorCreator::~LimitedTimeredActorCreator() = default;

bool LimitedTimeredActorCreator::init_(sead::Heap* heap) {
    return ksys::act::ai::Ai::init_(heap);
}

void LimitedTimeredActorCreator::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Ai::enter_(params);
}

void LimitedTimeredActorCreator::leave_() {
    ksys::act::ai::Ai::leave_();
}

void LimitedTimeredActorCreator::loadParams_() {
    getStaticParam(&mCreateTimer_s, "CreateTimer");
    getStaticParam(&mCreateTimerRand_s, "CreateTimerRand");
    getStaticParam(&mCreateActorName_s, "CreateActorName");
    getMapUnitParam(&mCreateLimit_m, "CreateLimit");
    getMapUnitParam(&mActorName_m, "ActorName");
    getAITreeVariable(&mGeneratedActorLink_a, "GeneratedActorLink");
}

}  // namespace uking::ai
