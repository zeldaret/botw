#include "Game/AI/Query/queryHasEnoughPayment.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

HasEnoughPayment::HasEnoughPayment(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasEnoughPayment::~HasEnoughPayment() = default;

int HasEnoughPayment::doQuery() {
    auto* gdm = ksys::gdt::Manager::instance();
    if (gdm != nullptr) {
        s32 state = -1;
        if (!gdm->getParam().get().getS32(&state, "Shop_CurrentItemState"))
            return 1;
        if (state == 2 || state == 3)
            return 0;
    }
    return 1;
}

void HasEnoughPayment::loadParams(const evfl::QueryArg& arg) {}

void HasEnoughPayment::loadParams() {}

}  // namespace uking::query
