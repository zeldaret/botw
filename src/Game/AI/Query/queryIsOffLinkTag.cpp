#include "Game/AI/Query/queryIsOffLinkTag.h"
#include <evfl/Query.h>

namespace uking::query {

IsOffLinkTag::IsOffLinkTag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOffLinkTag::~IsOffLinkTag() = default;

// FIXME: implement
int IsOffLinkTag::doQuery() {
    return -1;
}

void IsOffLinkTag::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "SignalType");
}

void IsOffLinkTag::loadParams() {
    getDynamicParam(&mSignalType, "SignalType");
}

}  // namespace uking::query
