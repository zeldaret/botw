#include "Game/Actor/Query/queryCheckE3Mode.h"
#include <evfl/Query.h>
#include "Game/E3Mgr.h"

namespace uking::query {

CheckE3Mode::CheckE3Mode(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckE3Mode::~CheckE3Mode() = default;

int CheckE3Mode::doQuery() {
    auto* e3m = E3Mgr::instance();
    if (e3m != nullptr) {
        if (e3m->isDemoMode0AndNotStageSelect()) {
            return 1;
        }
        if (e3m->isDemoMode1AndNotStageSelect()) {
            return 2;
        }
        if (e3m->isDemoMode2AndNotStageSelect()) {
            return 3;
        }
    }
    return 0;
}

void CheckE3Mode::loadParams(const evfl::QueryArg& arg) {}

void CheckE3Mode::loadParams() {}

}  // namespace uking::query
