#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckExistActor : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckExistActor, Query)
public:
    explicit CheckExistActor(const InitArg& arg);
    ~CheckExistActor() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    bool* mIsCheckEquipStand{};
    bool* mIsCheckLife{};
    sead::SafeString mActorName{};
};

}  // namespace uking::query
