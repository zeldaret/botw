#include "Game/AI/Query/queryCheckHasManifactureArmor.h"
#include <evfl/Query.h>

namespace uking::query {

CheckHasManifactureArmor::CheckHasManifactureArmor(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckHasManifactureArmor::~CheckHasManifactureArmor() = default;

// FIXME: implement
int CheckHasManifactureArmor::doQuery() {
    return -1;
}

void CheckHasManifactureArmor::loadParams(const evfl::QueryArg& arg) {}

void CheckHasManifactureArmor::loadParams() {}

}  // namespace uking::query
