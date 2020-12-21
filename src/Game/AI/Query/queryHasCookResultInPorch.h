#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class HasCookResultInPorch : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(HasCookResultInPorch, Query)
public:
    explicit HasCookResultInPorch(const InitArg& arg);
    ~HasCookResultInPorch() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mCount{};
    sead::SafeString mPorchItemName{};
    sead::SafeString mCookEffectType{};
};

}  // namespace uking::query
