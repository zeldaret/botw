#include "Game/AI/Query/queryHasEnoughPayment.h"
#include <evfl/Query.h>

namespace uking::query {

HasEnoughPayment::HasEnoughPayment(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasEnoughPayment::~HasEnoughPayment() = default;

// FIXME: implement
int HasEnoughPayment::doQuery() {
    return -1;
}

void HasEnoughPayment::loadParams(const evfl::QueryArg& arg) {}

void HasEnoughPayment::loadParams() {}

}  // namespace uking::query
