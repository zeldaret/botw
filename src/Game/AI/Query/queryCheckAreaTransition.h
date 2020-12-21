#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckAreaTransition : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckAreaTransition, Query)
public:
    explicit CheckAreaTransition(const InitArg& arg);
    ~CheckAreaTransition() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    const float* mCheckDistFront{};
    int* mCurrentAreaNo{};
    int* mPostAreaNo{};
};

}  // namespace uking::query
