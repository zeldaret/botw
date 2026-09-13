#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckEventCancel : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckEventCancel, Query)
public:
    explicit CheckEventCancel(const InitArg& arg);
    ~CheckEventCancel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
