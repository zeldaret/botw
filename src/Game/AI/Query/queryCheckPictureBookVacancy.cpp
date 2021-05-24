#include "Game/AI/Query/queryCheckPictureBookVacancy.h"
#include <evfl/Query.h>

namespace uking::query {

CheckPictureBookVacancy::CheckPictureBookVacancy(const InitArg& arg) : ksys::act::ai::Query(arg) {}

CheckPictureBookVacancy::~CheckPictureBookVacancy() = default;

// FIXME: implement
int CheckPictureBookVacancy::doQuery() {
    return -1;
}

void CheckPictureBookVacancy::loadParams(const evfl::QueryArg& arg) {
    loadInt(arg.param_accessor, "VacancyNum");
    loadString(arg.param_accessor, "Category");
}

void CheckPictureBookVacancy::loadParams() {
    getDynamicParam(&mVacancyNum, "VacancyNum");
    getDynamicParam(&mCategory, "Category");
}

}  // namespace uking::query
