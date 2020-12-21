#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDeadlyQuestEscapeTiming : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDeadlyQuestEscapeTiming, Query)
public:
    explicit CheckDeadlyQuestEscapeTiming(const InitArg& arg);
    ~CheckDeadlyQuestEscapeTiming() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
