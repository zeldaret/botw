#include "Game/AI/Query/queryHasArmorAlreadyDyed.h"
#include <evfl/Query.h>

namespace uking::query {

HasArmorAlreadyDyed::HasArmorAlreadyDyed(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasArmorAlreadyDyed::~HasArmorAlreadyDyed() = default;

// FIXME: implement
int HasArmorAlreadyDyed::doQuery() {
    return -1;
}

void HasArmorAlreadyDyed::loadParams(const evfl::QueryArg& arg) {}

void HasArmorAlreadyDyed::loadParams() {}

}  // namespace uking::query
