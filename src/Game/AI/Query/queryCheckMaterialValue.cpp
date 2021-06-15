#include "Game/AI/Query/queryCheckMaterialValue.h"
#include <evfl/Query.h>

namespace uking::query {

CheckMaterialValue::CheckMaterialValue(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMaterialValue::~CheckMaterialValue() = default;

// FIXME: implement
int CheckMaterialValue::doQuery() {
    return -1;
}

void CheckMaterialValue::loadParams(const evfl::QueryArg& arg) {}

void CheckMaterialValue::loadParams() {}

}  // namespace uking::query
