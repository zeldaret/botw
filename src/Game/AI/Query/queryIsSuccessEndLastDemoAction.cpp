#include "Game/AI/Query/queryIsSuccessEndLastDemoAction.h"
#include <evfl/Query.h>

namespace uking::query {

IsSuccessEndLastDemoAction::IsSuccessEndLastDemoAction(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsSuccessEndLastDemoAction::~IsSuccessEndLastDemoAction() = default;

// FIXME: implement
int IsSuccessEndLastDemoAction::doQuery() {
    return -1;
}

void IsSuccessEndLastDemoAction::loadParams(const evfl::QueryArg& arg) {}

void IsSuccessEndLastDemoAction::loadParams() {}

}  // namespace uking::query
