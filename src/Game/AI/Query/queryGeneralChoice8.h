#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class GeneralChoice8 : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(GeneralChoice8, Query)
public:
    explicit GeneralChoice8(const InitArg& arg);
    ~GeneralChoice8() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
