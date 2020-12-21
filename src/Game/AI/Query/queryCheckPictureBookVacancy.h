#pragma once

#include "KingSystem/ActorSystem/actAiQuery.h"

namespace uking::query {

class CheckPictureBookVacancy : public ksys::act::ai::Query {
    SEAD_RTTI_OVERRIDE(CheckPictureBookVacancy, Query)
public:
    explicit CheckPictureBookVacancy(const InitArg& arg);
    ~CheckPictureBookVacancy() override;
    int doQuery() override;

    void loadParams() override;
    void loadParams(const evfl::QueryArg& arg) override;

protected:
    int* mVacancyNum{};
    sead::SafeString mCategory{};
};

}  // namespace uking::query
