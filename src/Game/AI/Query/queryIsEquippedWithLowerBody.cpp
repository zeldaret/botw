#include "Game/AI/Query/queryIsEquippedWithLowerBody.h"
#include <evfl/Query.h>

namespace uking::query {

IsEquippedWithLowerBody::IsEquippedWithLowerBody(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsEquippedWithLowerBody::~IsEquippedWithLowerBody() = default;

// FIXME: implement
int IsEquippedWithLowerBody::doQuery() {
    return -1;
}

void IsEquippedWithLowerBody::loadParams(const evfl::QueryArg& arg) {}

void IsEquippedWithLowerBody::loadParams() {}

}  // namespace uking::query
