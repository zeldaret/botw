#include "Game/AI/Query/queryCheckEventCancel.h"
#include <evfl/Query.h>

namespace uking::query {

CheckEventCancel::CheckEventCancel(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckEventCancel::~CheckEventCancel() = default;

// FIXME: implement
int CheckEventCancel::doQuery() {
    return -1;
}

void CheckEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckEventCancel::loadParams() {}

}  // namespace uking::query
