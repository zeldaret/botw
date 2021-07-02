#include "Game/AI/Query/queryIsSuccessEndLastDemoAction.h"
#include <evfl/Query.h>
#include "KingSystem/ActorSystem/actActor.h"
#include "KingSystem/ActorSystem/actAiRoot.h"

namespace uking::query {

IsSuccessEndLastDemoAction::IsSuccessEndLastDemoAction(const InitArg& arg)
    : ksys::act::ai::Query(arg) {}

IsSuccessEndLastDemoAction::~IsSuccessEndLastDemoAction() = default;

int IsSuccessEndLastDemoAction::doQuery() {
    if (mActor != nullptr && mActor->getRootAi() != nullptr) {
        auto* action = mActor->getRootAi()->getCurrentAction();
        if (action == nullptr)
            return 0;

        if (action->isFinished())
            return 1;
    }
    return 0;
}

void IsSuccessEndLastDemoAction::loadParams(const evfl::QueryArg& arg) {}

void IsSuccessEndLastDemoAction::loadParams() {}

}  // namespace uking::query
