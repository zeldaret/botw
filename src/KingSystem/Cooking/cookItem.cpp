#include "KingSystem/Cooking/cookItem.h"

namespace ksys {

CookItem::CookItem() = default;

void CookItem::reset() {
    name.clear();
    stamina_recover_x = 0.0f;
    stamina_recover_y = 0;
    _224 = false;
    cook_effect_1 = 0;
    cook_effect_0_x = -1;
    cook_effect_0_y = 0.0f;
    for (auto& ingredient : ingredients) {
        ingredient.clear();
    }
}

void CookItem::copy(CookItem& to) const {
    to.name = name;
    to.stamina_recover_x = stamina_recover_x;
    to.stamina_recover_y = stamina_recover_y;
    to._224 = _224;
    to.cook_effect_1 = cook_effect_1;
    to.cook_effect_0_y = cook_effect_0_y;
    to.cook_effect_0_x = cook_effect_0_x;
    to.ingredients = ingredients;
}

}  // namespace ksys
