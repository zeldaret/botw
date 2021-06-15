#include "Game/AI/Query/queryCheckHorseCustomizeSelect.h"
#include <evfl/Query.h>

namespace uking::query {

CheckHorseCustomizeSelect::CheckHorseCustomizeSelect(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

CheckHorseCustomizeSelect::~CheckHorseCustomizeSelect() = default;

// FIXME: implement
int CheckHorseCustomizeSelect::doQuery() {
    return -1;
}

void CheckHorseCustomizeSelect::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseCustomizeSelect::loadParams() {}

}  // namespace uking::query
