#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class GeneralChoice4 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(GeneralChoice4, Query)
public:
    explicit GeneralChoice4(const InitArg& arg);
    ~GeneralChoice4() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
