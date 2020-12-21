#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckJustBeforeEventCancel : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckJustBeforeEventCancel, Query)
public:
    explicit CheckJustBeforeEventCancel(const InitArg& arg);
    ~CheckJustBeforeEventCancel() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
