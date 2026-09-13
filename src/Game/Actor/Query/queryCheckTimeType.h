#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckTimeType : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckTimeType, Query)
public:
    explicit CheckTimeType(const InitArg& arg);
    ~CheckTimeType() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
