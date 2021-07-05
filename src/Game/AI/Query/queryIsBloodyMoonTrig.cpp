#include "Game/AI/Query/queryIsBloodyMoonTrig.h"
#include <evfl/Query.h>
#include "KingSystem/World/worldManager.h"

namespace uking::query {

IsBloodyMoonTrig::IsBloodyMoonTrig(const InitArg& arg) : ksys::act::ai::Query(arg) {}

IsBloodyMoonTrig::~IsBloodyMoonTrig() = default;

int IsBloodyMoonTrig::doQuery() {
    return ksys::world::Manager::instance()->getTimeMgr()->wasBloodyDayAndDayPassed();
}

void IsBloodyMoonTrig::loadParams(const evfl::QueryArg& arg) {}

void IsBloodyMoonTrig::loadParams() {}

}  // namespace uking::query
