#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckMiniGameTimeOver : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckMiniGameTimeOver, Query)
public:
    explicit CheckMiniGameTimeOver(const InitArg& arg);
    ~CheckMiniGameTimeOver() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
