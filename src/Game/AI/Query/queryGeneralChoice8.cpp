#include "Game/AI/Query/queryGeneralChoice8.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActorUtil.h"

namespace uking::query {

GeneralChoice8::GeneralChoice8(const InitArg& arg) : ksys::act::ai::Query(arg) {}

GeneralChoice8::~GeneralChoice8() = default;

// FIXME: implement
int GeneralChoice8::doQuery() {
    s32 idx = ksys::act::getSelectedChoiceIdx(8, getName());
    if (idx < 0)
        return 0;

    return idx;
}

void GeneralChoice8::loadParams(const evfl::QueryArg& arg) {}

void GeneralChoice8::loadParams() {}

}  // namespace uking::query
