#include "Game/AI/Query/queryIsTerrorDisappeared.h"
#include <evfl/Query.h>

namespace uking::query {

IsTerrorDisappeared::IsTerrorDisappeared(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsTerrorDisappeared::~IsTerrorDisappeared() = default;

// FIXME: implement
int IsTerrorDisappeared::doQuery() {
    return -1;
}

void IsTerrorDisappeared::loadParams(const evfl::QueryArg& arg) {}

void IsTerrorDisappeared::loadParams() {}

}  // namespace uking::query
