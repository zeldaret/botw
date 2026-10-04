#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckHorseDeadCause : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckHorseDeadCause, Query)
public:
    explicit CheckHorseDeadCause(const InitArg& arg);
    ~CheckHorseDeadCause() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
