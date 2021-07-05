#include "Game/AI/Query/queryCheckHorseTakenOut.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtSpecialFlags.h"

namespace uking::query {

CheckHorseTakenOut::CheckHorseTakenOut(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckHorseTakenOut::~CheckHorseTakenOut() = default;

int CheckHorseTakenOut::doQuery() {
    s32 active = ksys::gdt::getS32ByKey("Horse_ActiveIndex");
    if (active < 0)
        return 2;

    s32 selected = ksys::gdt::getS32ByKey("Horse_SelectedIndex");
    return active == selected;
}

void CheckHorseTakenOut::loadParams(const evfl::QueryArg& arg) {}

void CheckHorseTakenOut::loadParams() {}

}  // namespace uking::query
