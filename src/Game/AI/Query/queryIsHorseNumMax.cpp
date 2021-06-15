#include "Game/AI/Query/queryIsHorseNumMax.h"
#include <evfl/Query.h>

namespace uking::query {

IsHorseNumMax::IsHorseNumMax(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsHorseNumMax::~IsHorseNumMax() = default;

// FIXME: implement
int IsHorseNumMax::doQuery() {
    return -1;
}

void IsHorseNumMax::loadParams(const evfl::QueryArg& arg) {}

void IsHorseNumMax::loadParams() {}

}  // namespace uking::query
