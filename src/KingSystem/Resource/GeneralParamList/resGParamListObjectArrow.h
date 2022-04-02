#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectArrow : public GParamListObject {
public:
    GParamListObjectArrow();
    const char* getName() const override { return "Arrow"; }

    agl::utl::Parameter<s32> mArrowNum;
    agl::utl::Parameter<s32> mDeleteTime;
    agl::utl::Parameter<s32> mDeleteTimeWithChemical;
    agl::utl::Parameter<s32> mEnemyShootNumForDelete;
    agl::utl::Parameter<s32> mArrowDeletePer;
    agl::utl::Parameter<s32> mExtraDamage;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectArrow, 0xf8);

inline GParamListObjectArrow::GParamListObjectArrow() {
    auto* const obj = &mObj;

    mArrowNum.init(0, "ArrowNum", "", obj);
    mDeleteTime.init(0, "DeleteTime", "", obj);
    mDeleteTimeWithChemical.init(0, "DeleteTimeWithChemical", "", obj);
    mEnemyShootNumForDelete.init(0, "EnemyShootNumForDelete", "", obj);
    mArrowDeletePer.init(0, "ArrowDeletePer", "", obj);
    mExtraDamage.init(0, "ExtraDamage", "", obj);
}

}  // namespace ksys::res
