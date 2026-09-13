#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckSelectPicture : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckSelectPicture, Query)
public:
    explicit CheckSelectPicture(const InitArg& arg);
    ~CheckSelectPicture() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    sead::SafeString mActorName{};
};

}  // namespace uking::query
