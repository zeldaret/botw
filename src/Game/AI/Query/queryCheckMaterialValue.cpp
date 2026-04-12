#include "Game/AI/Query/queryCheckMaterialValue.h"
#include <evfl/Query.h>
#include "KingSystem/GameData/gdtManager.h"

namespace uking::query {

CheckMaterialValue::CheckMaterialValue(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckMaterialValue::~CheckMaterialValue() = default;

int CheckMaterialValue::doQuery() {
    int mat = 0;
    auto* gdm = ksys::gdt::Manager::instance();
    if (!gdm)
        return 0;

    gdm->getParamBypassPerm().get().getS32(&mat, "AllMaterialValue");

    return mat > 0;
}

void CheckMaterialValue::loadParams(const evfl::QueryArg& arg) {}

void CheckMaterialValue::loadParams() {}

}  // namespace uking::query
