#include "KingSystem/ActorSystem/queryCheckEventCancel.h"
#include <evfl/Query.h>

namespace ksys::act::ai {

CheckEventCancel::CheckEventCancel(const InitArg& arg) : Query(arg) {}

CheckEventCancel::~CheckEventCancel() = default;

// FIXME: implement
int CheckEventCancel::doQuery() {
    return -1;
}

void CheckEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckEventCancel::loadParams() {}

}  // namespace ksys::act::ai
