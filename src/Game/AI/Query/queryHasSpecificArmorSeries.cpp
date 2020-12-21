#include "Game/AI/Query/queryHasSpecificArmorSeries.h"
#include <evfl/query.h>

namespace uking::query {

HasSpecificArmorSeries::HasSpecificArmorSeries(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasSpecificArmorSeries::~HasSpecificArmorSeries() = default;

// FIXME: implement
int HasSpecificArmorSeries::doQuery() {
    return -1;
}

void HasSpecificArmorSeries::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "SeriesType");
}

void HasSpecificArmorSeries::loadParams() {
    getDynamicParam(&mSeriesType, "SeriesType");
}

}  // namespace uking::query
