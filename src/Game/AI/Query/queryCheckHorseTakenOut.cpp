#include "Game/AI/Query/queryCheckHorseTakenOut.h"
#include <evfl/Query.h>

namespace uking::query {

CheckHorseTakenOut::CheckHorseTakenOut(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseTakenOut::~CheckHorseTakenOut() = default;

// FIXME: implement
int CheckHorseTakenOut::doQuery() {
    return -1;
}

void CheckHorseTakenOut::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseTakenOut::loadParams() {}

}  // namespace uking::query
