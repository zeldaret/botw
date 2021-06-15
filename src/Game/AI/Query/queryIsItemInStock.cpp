#include "Game/AI/Query/queryIsItemInStock.h"
#include <evfl/Query.h>

namespace uking::query {

IsItemInStock::IsItemInStock(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsItemInStock::~IsItemInStock() = default;

// FIXME: implement
int IsItemInStock::doQuery() {
    return -1;
}

void IsItemInStock::loadParams(const evfl::QueryArg& arg) {}

void IsItemInStock::loadParams() {}

}  // namespace uking::query
