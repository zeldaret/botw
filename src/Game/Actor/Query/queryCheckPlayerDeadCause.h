#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPlayerDeadCause : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPlayerDeadCause, Query)
public:
    explicit CheckPlayerDeadCause(const InitArg& arg);
    ~CheckPlayerDeadCause() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    // Unused
    void* _20{};
};

}  // namespace uking::query
