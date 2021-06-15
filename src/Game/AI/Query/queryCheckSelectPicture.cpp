#include "Game/AI/Query/queryCheckSelectPicture.h"
#include <evfl/Query.h>

namespace uking::query {

CheckSelectPicture::CheckSelectPicture(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckSelectPicture::~CheckSelectPicture() = default;

// FIXME: implement
int CheckSelectPicture::doQuery() {
    return -1;
}

void CheckSelectPicture::loadParams(const evfl::QueryArg& arg) {
    loadString(arg.param_accessor, "ActorName");
}

void CheckSelectPicture::loadParams() {
    getDynamicParam(&mActorName, "ActorName");
}

}  // namespace uking::query
