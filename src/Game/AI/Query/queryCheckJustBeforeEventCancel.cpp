#include "Game/AI/Query/queryCheckJustBeforeEventCancel.h"
#include <evfl/Query.h>

namespace uking::query {

CheckJustBeforeEventCancel::CheckJustBeforeEventCancel(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckJustBeforeEventCancel::~CheckJustBeforeEventCancel() = default;

// FIXME: implement
int CheckJustBeforeEventCancel::doQuery() {
    return -1;
}

void CheckJustBeforeEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckJustBeforeEventCancel::loadParams() {}

}  // namespace uking::query
