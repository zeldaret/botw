#include "Game/AI/Query/queryComparePlayerOriginalHeart.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

ComparePlayerOriginalHeart::ComparePlayerOriginalHeart(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

ComparePlayerOriginalHeart::~ComparePlayerOriginalHeart() = default;

int ComparePlayerOriginalHeart::doQuery() {
    using PlayerInfo = ksys::act::PlayerInfo;

    if (PlayerInfo::instance() == nullptr)
        return 0;

    s32 life = PlayerInfo::instance()->getLife();
    s32 hearts = PlayerInfo::instance()->getMaxHearts();
    s32 compare;
    if (life <= hearts)
        compare = life;
    else
        compare = hearts;
    return compare >= *mThreshold;
}

void ComparePlayerOriginalHeart::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerOriginalHeart::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
