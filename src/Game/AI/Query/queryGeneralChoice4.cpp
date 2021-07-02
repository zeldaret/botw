#include "Game/AI/Query/queryGeneralChoice4.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::query {

GeneralChoice4::GeneralChoice4(const InitArg& arg) : ksys::act::ai::Query(arg) {}

GeneralChoice4::~GeneralChoice4() = default;

// FIXME: implement
int GeneralChoice4::doQuery() {
    s32 idx = ksys::act::getSelectedChoiceIdx(4, getName());
    if (idx < 0)
        return 0;

    return idx;
}

void GeneralChoice4::loadParams(const evfl::QueryArg& arg) {}

void GeneralChoice4::loadParams() {}

}  // namespace uking::query
