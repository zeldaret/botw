#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckMaterialValue : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckMaterialValue, Query)
public:
    explicit CheckMaterialValue(const InitArg& arg);
    ~CheckMaterialValue() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
