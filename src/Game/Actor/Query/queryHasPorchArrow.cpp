#include "Game/Actor/Query/queryHasPorchArrow.h"
#include <evfl/Query.h>
#include "KingSystem/System/UIGlue.h"

namespace uking::query {

HasPorchArrow::HasPorchArrow(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchArrow::~HasPorchArrow() = default;

int HasPorchArrow::doQuery() {
    s32 arrow_cnt = ksys::ui::getItemValue("NormalArrow") + ksys::ui::getItemValue("FireArrow") +
                    ksys::ui::getItemValue("IceArrow") + ksys::ui::getItemValue("ElectricArrow") +
                    ksys::ui::getItemValue("BombArrow_A") + ksys::ui::getItemValue("AncientArrow");
    return arrow_cnt < *mCheckNum;
}

void HasPorchArrow::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckNum");
}

void HasPorchArrow::loadParams() {
    getDynamicParam(&mCheckNum, "CheckNum");
}

}  // namespace uking::query
