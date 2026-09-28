#include "KingSystem/ActorSystem/queryIsWaitRevival.h"
#include <evfl/Query.h>

namespace ksys::act::ai {

IsWaitRevival::IsWaitRevival(const InitArg& arg) : Query(arg) {}

IsWaitRevival::~IsWaitRevival() = default;

// FIXME: implement
int IsWaitRevival::doQuery() {
    return -1;
}

void IsWaitRevival::loadParams(const evfl::QueryArg& arg) {}

void IsWaitRevival::loadParams() {}

}  // namespace ksys::act::ai
