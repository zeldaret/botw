#pragma once

#include <basis/seadTypes.h>
#include <container/seadSafeArray.h>
#include <prim/seadSafeString.h>
#include "KingSystem/Utils/Types.h"

namespace ksys {

struct CookItem {
    CookItem();

    sead::FixedSafeString<64> name{""};
    sead::SafeArray<sead::FixedSafeString<64>, 5> ingredients;
    f32 stamina_recover_x{};
    s32 stamina_recover_y{};
    s32 cook_effect_1{};
    s32 cook_effect_0_x = -1;
    f32 cook_effect_0_y{};
    bool _224{};
};
KSYS_CHECK_SIZE_NX150(CookItem, 0x228);

}  // namespace ksys
