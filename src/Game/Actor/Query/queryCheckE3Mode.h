#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckE3Mode : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckE3Mode, Query)
public:
    explicit CheckE3Mode(const InitArg& arg);
    ~CheckE3Mode() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
