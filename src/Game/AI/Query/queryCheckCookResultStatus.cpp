#include "Game/AI/Query/queryCheckCookResultStatus.h"
#include <evfl/Query.h>
#include "Game/Cooking/cookManager.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

CheckCookResultStatus::CheckCookResultStatus(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckCookResultStatus::~CheckCookResultStatus() = default;

int CheckCookResultStatus::doQuery() {
    auto* cooking_mgr = CookingMgr::instance();
    if (!cooking_mgr)
        return 0;

    CookItem cook_item;
    cooking_mgr->getCookItem(cook_item);

    switch (*mCheckType) {
    case 0:
        return !ksys::act::hasTag(cook_item.actor_name, ksys::act::tags::CookFailure);
    case 1:
        return cook_item.is_crit;
    default:
        return 0;
    }
}

void CheckCookResultStatus::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckType");
}

void CheckCookResultStatus::loadParams() {
    getDynamicParam(&mCheckType, "CheckType");
    getAITreeVariable(&mCurrentCookResultHolder, "CurrentCookResultHolder");
}

}  // namespace uking::query
