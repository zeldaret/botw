#include "Game/AI/Query/queryCheckExistArrow.h"
#include <evfl/Query.h>

namespace uking::query {

CheckExistArrow::CheckExistArrow(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckExistArrow::~CheckExistArrow() = default;

// FIXME: implement
int CheckExistArrow::doQuery() {
    return -1;
}

void CheckExistArrow::loadParams(const evfl::QueryArg& arg) {}

void CheckExistArrow::loadParams() {}

}  // namespace uking::query
