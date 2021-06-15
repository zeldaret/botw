#include "Game/AI/Query/queryIsAppAlreadyExchanged.h"
#include <evfl/Query.h>

namespace uking::query {

IsAppAlreadyExchanged::IsAppAlreadyExchanged(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsAppAlreadyExchanged::~IsAppAlreadyExchanged() = default;

// FIXME: implement
int IsAppAlreadyExchanged::doQuery() {
    return -1;
}

void IsAppAlreadyExchanged::loadParams(const evfl::QueryArg& arg) {}

void IsAppAlreadyExchanged::loadParams() {}

}  // namespace uking::query
