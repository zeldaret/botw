#include "Game/AI/Query/queryComparePlayerMaxStamina.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actPlayerInfo.h"

namespace uking::query {

ComparePlayerMaxStamina::ComparePlayerMaxStamina(const InitArg& arg) : ksys::act::ai::Query(arg) {}

ComparePlayerMaxStamina::~ComparePlayerMaxStamina() = default;

int ComparePlayerMaxStamina::doQuery() {
    auto* pi = ksys::act::PlayerInfo::instance();
    if (pi == nullptr)
        return 0;

    s32 stamina = pi->getMaxStamina();
    if (stamina % 200 <= 0)
        return stamina / 200 >= *mThreshold;
    else
        return stamina / 200 + 1 >= *mThreshold;
}

void ComparePlayerMaxStamina::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "Threshold");
}

void ComparePlayerMaxStamina::loadParams() {
    getDynamicParam(&mThreshold, "Threshold");
}

}  // namespace uking::query
