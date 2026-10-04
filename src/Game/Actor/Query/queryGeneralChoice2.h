#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class GeneralChoice2 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(GeneralChoice2, Query)
public:
    explicit GeneralChoice2(const InitArg& arg);
    ~GeneralChoice2() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
