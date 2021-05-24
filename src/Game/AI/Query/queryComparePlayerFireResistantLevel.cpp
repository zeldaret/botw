#include "Game/AI/Query/queryComparePlayerFireResistantLevel.h"
#include <evfl/Query.h>

namespace uking::query {

ComparePlayerFireResistantLevel::ComparePlayerFireResistantLevel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

ComparePlayerFireResistantLevel::~ComparePlayerFireResistantLevel() = default;

// FIXME: implement
int ComparePlayerFireResistantLevel::doQuery() {
    return -1;
}

void ComparePlayerFireResistantLevel::loadParams(const evfl::QueryArg& arg) {}

void ComparePlayerFireResistantLevel::loadParams() {}

}  // namespace uking::query
