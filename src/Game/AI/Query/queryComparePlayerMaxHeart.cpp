#include "Game/AI/Query/queryComparePlayerMaxHeart.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

ComparePlayerMaxHeart::ComparePlayerMaxHeart(const InitArg& arg) : ksys::act::ai::Query(arg) {}

ComparePlayerMaxHeart::~ComparePlayerMaxHeart() = default;

int ComparePlayerMaxHeart::doQuery() {
    auto* pi = ksys::act::PlayerInfo::instance();
    if (pi == nullptr)
        return 0;

    s32 full_hearts = pi->getMaxHearts() / 4;
    return full_hearts >= *mThreshold;
}

void ComparePlayerMaxHeart::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerMaxHeart::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
