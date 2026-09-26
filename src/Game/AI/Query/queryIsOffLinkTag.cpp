#include "Game/AI/Query/queryIsOffLinkTag.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"

namespace uking::query {

IsOffLinkTag::IsOffLinkTag(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsOffLinkTag::~IsOffLinkTag() = default;

int IsOffLinkTag::doQuery() {
    return !mActor->checkBasicSig();
}

void IsOffLinkTag::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "SignalType");
}

void IsOffLinkTag::loadParams() {
    getDynamicParam(&mSignalType, "SignalType");
}

}  // namespace uking::query
