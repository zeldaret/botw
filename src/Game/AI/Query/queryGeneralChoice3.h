#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class GeneralChoice3 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(GeneralChoice3, Query)
public:
    explicit GeneralChoice3(const InitArg& arg);
    ~GeneralChoice3() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
