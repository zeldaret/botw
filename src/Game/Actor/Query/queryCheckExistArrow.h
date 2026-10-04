#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckExistArrow : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckExistArrow, Query)
public:
    explicit CheckExistArrow(const InitArg& arg);
    ~CheckExistArrow() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;
};

}  // namespace uking::query
