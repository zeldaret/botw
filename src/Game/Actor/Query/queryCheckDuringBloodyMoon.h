#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckDuringBloodyMoon : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckDuringBloodyMoon, Query)
public:
    explicit CheckDuringBloodyMoon(const InitArg& arg);
    ~CheckDuringBloodyMoon() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
