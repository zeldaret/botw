#include "Game/AI/Query/queryIsBloodyMoonTrig.h"
#include <evfl/Query.h>

namespace uking::query {

IsBloodyMoonTrig::IsBloodyMoonTrig(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsBloodyMoonTrig::~IsBloodyMoonTrig() = default;

// FIXME: implement
int IsBloodyMoonTrig::doQuery() {
    return -1;
}

void IsBloodyMoonTrig::loadParams(const evfl::QueryArg& arg) {}

void IsBloodyMoonTrig::loadParams() {}

}  // namespace uking::query
