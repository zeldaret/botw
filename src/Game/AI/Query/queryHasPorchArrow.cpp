#include "Game/AI/Query/queryHasPorchArrow.h"
#include <evfl/Query.h>
#include "Game/UI/uiUtils.h"

namespace uking::query {

HasPorchArrow::HasPorchArrow(const InitArg& arg) : ksys::act::ai::Query(arg) {}

HasPorchArrow::~HasPorchArrow() = default;

int HasPorchArrow::doQuery() {
    s32 arrow_cnt = ui::getItemValue("NormalArrow") + ui::getItemValue("FireArrow") +
                    ui::getItemValue("IceArrow") + ui::getItemValue("ElectricArrow") +
                    ui::getItemValue("BombArrow_A") + ui::getItemValue("AncientArrow");
    return arrow_cnt < *mCheckNum;
}

void HasPorchArrow::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "CheckNum");
}

void HasPorchArrow::loadParams() {
    getDynamicParam(&mCheckNum, "CheckNum");
}

}  // namespace uking::query
