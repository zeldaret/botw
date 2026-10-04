#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckTypeOfOwnedHorseForEvent : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckTypeOfOwnedHorseForEvent, Query)
public:
    explicit CheckTypeOfOwnedHorseForEvent(const InitArg& arg);
    ~CheckTypeOfOwnedHorseForEvent() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
