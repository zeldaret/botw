#include "Game/AI/Query/queryGeneralChoice2.h"
#include <evfl/Query.h>

namespace uking::query {

GeneralChoice2::GeneralChoice2(const InitArg& arg) : ksys::act::ai::Query(arg) {}

GeneralChoice2::~GeneralChoice2() = default;

// FIXME: implement
int GeneralChoice2::doQuery() {
    return -1;
}

void GeneralChoice2::loadParams(const evfl::QueryArg& arg) {}

void GeneralChoice2::loadParams() {}

}  // namespace uking::query
