#include "Game/AI/Query/queryGeneralChoice3.h"
#include <evfl/Query.h>

namespace uking::query {

GeneralChoice3::GeneralChoice3(const InitArg& arg) : ksys::act::ai::Query(arg) {}

GeneralChoice3::~GeneralChoice3() = default;

// FIXME: implement
int GeneralChoice3::doQuery() {
    return -1;
}

void GeneralChoice3::loadParams(const evfl::QueryArg& arg) {}

void GeneralChoice3::loadParams() {}

}  // namespace uking::query
