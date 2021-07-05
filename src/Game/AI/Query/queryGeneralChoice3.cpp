#include "Game/AI/Query/queryGeneralChoice3.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::query {

GeneralChoice3::GeneralChoice3(const InitArg& arg) : ksys::act::ai::Query(arg) {}

GeneralChoice3::~GeneralChoice3() = default;

int GeneralChoice3::doQuery() {
    s32 idx = ksys::act::getSelectedChoiceIdx(3, getName());
    if (idx < 0)
        return 0;

    return idx;
}

void GeneralChoice3::loadParams(const evfl::QueryArg& arg) {}

void GeneralChoice3::loadParams() {}

}  // namespace uking::query
