#include "Game/AI/Query/queryCheckPorchInItem.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actTag.h"

namespace uking::query {

CheckPorchInItem::CheckPorchInItem(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPorchInItem::~CheckPorchInItem() = default;

int CheckPorchInItem::doQuery() {
    return ksys::act::hasTag(mPorchItemName, ksys::act::tags::CanGetPouch);
}

void CheckPorchInItem::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "PorchItemName");
}

void CheckPorchInItem::loadParams() {
    getDynamicParam(&mPorchItemName, "PorchItemName");
}

}  // namespace uking::query
