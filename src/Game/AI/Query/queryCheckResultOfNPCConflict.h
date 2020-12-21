#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckResultOfNPCConflict : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckResultOfNPCConflict, Query)
public:
    explicit CheckResultOfNPCConflict(const InitArg& arg);
    ~CheckResultOfNPCConflict() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
