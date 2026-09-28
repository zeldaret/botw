#include "KingSystem/ActorSystem/queryCheckJustBeforeEventCancel.h"
#include <evfl/Query.h>

namespace ksys::act::ai {

CheckJustBeforeEventCancel::CheckJustBeforeEventCancel(const InitArg& arg) : Query(arg) {}

CheckJustBeforeEventCancel::~CheckJustBeforeEventCancel() = default;

// FIXME: implement
int CheckJustBeforeEventCancel::doQuery() {
    return -1;
}

void CheckJustBeforeEventCancel::loadParams(const evfl::QueryArg& arg) {}

void CheckJustBeforeEventCancel::loadParams() {}

}  // namespace ksys::act::ai
