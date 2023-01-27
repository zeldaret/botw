#include "Game/Cooking/cookManager.h"
#include <codec/seadHashCRC32.h>
#include <random/seadGlobalRandom.h>
#include <typeindex>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/InitTimeInfo.h"
#include "KingSystem/Utils/SafeDelete.h"

namespace uking {

struct CookingEffect {
    sead::SafeString name;
    CookEffectId effect_id;
};

static const CookingEffect sCookingEffects[CookingMgr::NumEffects]{
    {"None", CookEffectId::None},
    {"LifeRecover", CookEffectId::LifeRecover},
    {"LifeMaxUp", CookEffectId::LifeMaxUp},
    {"ResistHot", CookEffectId::ResistHot},
    {"ResistCold", CookEffectId::ResistCold},
    {"ResistElectric", CookEffectId::ResistElectric},
    {"AttackUp", CookEffectId::AttackUp},
    {"DefenseUp", CookEffectId::DefenseUp},
    {"Quietness", CookEffectId::Quietness},
    {"MovingSpeed", CookEffectId::MovingSpeed},
    {"GutsRecover", CookEffectId::GutsRecover},
    {"ExGutsMaxUp", CookEffectId::ExGutsMaxUp},
    {"Fireproof", CookEffectId::Fireproof},
};

struct Crc32Constants {
    ksys::util::InitConstants init_constants;
    const u32 crc32_life_recover = sead::HashCRC32::calcStringHash("LifeRecover");
    const u32 crc32_guts_performance = sead::HashCRC32::calcStringHash("GutsPerformance");
    const u32 crc32_stamina_recover = sead::HashCRC32::calcStringHash("StaminaRecover");
    const u32 crc32_life_max_up = sead::HashCRC32::calcStringHash("LifeMaxUp");
    const u32 crc32_resist_hot = sead::HashCRC32::calcStringHash("ResistHot");
    const u32 crc32_resist_cold = sead::HashCRC32::calcStringHash("ResistCold");
    const u32 crc32_resist_electric = sead::HashCRC32::calcStringHash("ResistElectric");
    const u32 crc32_all_speed = sead::HashCRC32::calcStringHash("AllSpeed");
    const u32 crc32_attack_up = sead::HashCRC32::calcStringHash("AttackUp");
    const u32 crc32_defense_up = sead::HashCRC32::calcStringHash("DefenseUp");
    const u32 crc32_quietness = sead::HashCRC32::calcStringHash("Quietness");
    const u32 crc32_fireproof = sead::HashCRC32::calcStringHash("Fireproof");
};

static Crc32Constants sCrc32Constants;

CookItem::CookItem() = default;

void CookItem::reset() {
    actor_name.clear();
    life_recover = 0.0f;
    effect_time = 0;
    is_crit = false;
    sell_price = 0;
    effect_id = CookEffectId::None;
    vitality_boost = 0.0f;
    for (auto& ingredient : ingredients) {
        ingredient.clear();
    }
}

void CookItem::copy(CookItem& to) const {
    to.actor_name = actor_name;
    to.life_recover = life_recover;
    to.effect_time = effect_time;
    to.is_crit = is_crit;
    to.sell_price = sell_price;
    to.vitality_boost = vitality_boost;
    to.effect_id = effect_id;
    to.ingredients = ingredients;
}

SEAD_SINGLETON_DISPOSER_IMPL(CookingMgr)

CookingMgr::CookingMgr() = default;

CookingMgr::~CookingMgr() {
    if (mConfig) {
        ksys::util::safeDelete(mConfig);
    }
}

void CookingMgr::cookFail(CookItem& cook_item) {
    if (cook_item.actor_name.isEmpty())
        cook_item.actor_name.copy(mFailActorName);

    f32 life_recover;
    if (cook_item.actor_name == mFailActorName) {
        // Dubious food
        cook_item.effect_time = 0;
        const f32 min_recovery = (f32)mFailActorLifeRecover;
        life_recover =
            min_recovery > cook_item.life_recover ? min_recovery : cook_item.life_recover;
    } else {
        // Rock-hard food
        cook_item.effect_time = 0;
        life_recover = (f32)mStoneFoodActorLifeRecover;
    }

    cook_item.life_recover = life_recover;
    cook_item.vitality_boost = 0.0f;
    cook_item.effect_id = CookEffectId::None;
    cook_item.sell_price = 2;
}

void CookingMgr::cookFailForMissingConfig(CookItem& cook_item, const sead::SafeString& actor_name) {
    f32 life_recover;
    if (actor_name.isEmpty() || actor_name == mFailActorName) {
        cook_item.actor_name.copy(mFailActorName);
        cook_item.effect_time = 0;
        life_recover = (f32)mFailActorLifeRecover;
    } else {
        cook_item.actor_name = actor_name;
        cook_item.effect_time = 0;
        life_recover = (f32)mStoneFoodActorLifeRecover;
    }

    cook_item.life_recover = life_recover;
    cook_item.vitality_boost = 0.0f;
    cook_item.effect_id = CookEffectId::None;
    cook_item.sell_price = 1;
}

void CookingMgr::cookCalcCritBoost(const IngredientArray& ingredients, CookItem& cook_item,
                                   const BoostArg* boost_arg) const {
    // Find if any of the ingredients are Monster Extract.
    if (hasMonsterExtract(ingredients)) {
        cookHandleMonsterExtract(ingredients, cook_item);
        return;
    }

    if (!boost_arg || !boost_arg->always_boost) {
        if (boost_arg && !boost_arg->enable_random_boost)
            return;

        s32 threshold = 0;
        s32 num_ingredients = 0;
        s32 success_rate = 0;

        for (int i = 0; i < NumIngredientsMax; i++) {
            const auto& ingredient = ingredients[i];

            if (!ingredient.arg)
                continue;

            num_ingredients++;

            if (ingredient.actor_data.tryGetIntByKey(&success_rate, "cookSpiceBoostSuccessRate") &&
                success_rate > threshold) {
                threshold = success_rate;
            }
        }

        if (num_ingredients >= 1)
            threshold += mIngredientNumSuccessRates[num_ingredients - 1];

        if ((s32)sead::GlobalRandom::instance()->getU32(100) >= threshold)
            return;
    }
    cookHandleCrit(ingredients, cook_item);
}

void CookingMgr::cookHandleMonsterExtract([[maybe_unused]] const IngredientArray& ingredients,
                                          CookItem& cook_item) const {
    // Monster Extract found; calculate boosts.

    s32 effect_min = 0;
    s32 effect_max = 4;

    if (cook_item.life_recover <= 0.0f || cook_item.effect_id == CookEffectId::LifeMaxUp)
        effect_min = 2;

    if (cook_item.effect_id == CookEffectId::None)
        effect_max = 2;

    switch (sead::GlobalRandom::instance()->getS32Range(effect_min, effect_max)) {
    case 0:
        cook_item.life_recover += (f32)getCookingEffectEntry(CookEffectId::LifeRecover).ssa;
        break;
    case 1:
        cook_item.life_recover = (f32)getCookingEffectEntry(CookEffectId::LifeRecover).min;
        break;
    case 2:
        if (cook_item.effect_id != CookEffectId::None) {
            if (cook_item.vitality_boost > 0.0f && cook_item.vitality_boost < 1.0f) {
                cook_item.vitality_boost = 1.0;
            }
            cook_item.vitality_boost = (f32)((s32)cook_item.vitality_boost +
                                             getCookingEffectEntry(cook_item.effect_id).ssa);
        }
        break;
    case 3:
        if (cook_item.effect_id != CookEffectId::None) {
            cook_item.vitality_boost = (f32)getCookingEffectEntry(cook_item.effect_id).min;
        }
        break;
    default:
        break;
    }

    // Effect time
    if (cook_item.effect_time >= 1) {
        const u32 roll = sead::GlobalRandom::instance()->getU32(3);

        if (roll == 0)
            // 1 minute
            cook_item.effect_time = 60;
        if (roll == 1)
            // 10 minutes
            cook_item.effect_time = 600;
        if (roll == 2)
            // 30 minutes
            cook_item.effect_time = 1800;
    }
}

// NON_MATCHING
void CookingMgr::cookHandleCrit([[maybe_unused]] const IngredientArray& ingredients,
                                CookItem& cook_item) const {
    enum Bonus {
        LifeBonus = 0,
        VitalityBonus = 1,
        TimeBonus = 2,
    };

    Bonus bonus = LifeBonus;

    cook_item.is_crit = true;

    const auto& life_entry = getCookingEffectEntry(CookEffectId::LifeRecover);

    if (cook_item.effect_id != CookEffectId::None) {
        const f32 life_recover = cook_item.life_recover;
        const s32 vitality_bonus = sead::Mathi::clampMin((s32)cook_item.vitality_boost, 1);

        const f32 life_recover_max = (f32)life_entry.max;
        const s32 vitality_bonus_max = getCookingEffectEntry(cook_item.effect_id).max;

        const bool life_recover_maxed = life_recover >= life_recover_max;
        const bool vitality_bonus_maxed = vitality_bonus >= vitality_bonus_max;

        switch (cook_item.effect_id) {
        case CookEffectId::LifeMaxUp:
            bonus = VitalityBonus;
            break;

        case CookEffectId::GutsRecover:
        case CookEffectId::ExGutsMaxUp:
            if (vitality_bonus_maxed)
                bonus = LifeBonus;
            else if (life_recover_maxed)
                bonus = VitalityBonus;
            else
                bonus = sead::GlobalRandom::instance()->getBool() ? VitalityBonus : LifeBonus;
            break;

        default:
            if (vitality_bonus_maxed) {
                if (life_recover_maxed) {
                    bonus = TimeBonus;
                } else {
                    bonus = sead::GlobalRandom::instance()->getBool() ? TimeBonus : LifeBonus;
                }
            } else {
                if (life_recover_maxed) {
                    bonus = sead::GlobalRandom::instance()->getBool() ? TimeBonus : VitalityBonus;
                } else {
                    bonus = (Bonus)sead::GlobalRandom::instance()->getU32(3);
                }
            }
            break;
        }
    }

    switch (bonus) {
    case VitalityBonus:
        if (cook_item.effect_id != CookEffectId::None) {
            if (cook_item.vitality_boost > 0.0f && cook_item.vitality_boost < 1.0f)
                cook_item.vitality_boost = 1.0f;
            cook_item.vitality_boost = (f32)((int)cook_item.vitality_boost +
                                             getCookingEffectEntry(cook_item.effect_id).ssa);
        }
        break;
    case TimeBonus:
        cook_item.effect_time += mCritEffectTime;
        break;
    case LifeBonus:
        cook_item.life_recover += (f32)life_entry.ssa;
        break;
    }
}

void CookingMgr::cookCalcSpiceBoost(const IngredientArray& ingredients, CookItem& cook_item) const {
    using namespace ksys::act;

    int int_val;

    for (int i = 0; i < NumIngredientsMax; i++) {
        if (!ingredients[i].arg)
            continue;

        if (InfoData::instance()->hasTag(ingredients[i].actor_data, tags::CookEnemy) ||
            !InfoData::instance()->hasTag(ingredients[i].actor_data, tags::CookSpice)) {
            continue;
        }

        if (ingredients[i].actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostHitPointRecover") &&
            int_val > 0) {
            cook_item.life_recover += (f32)int_val;
        }

        if (ingredients[i].actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostEffectiveTime") &&
            int_val > 0) {
            cook_item.effect_time += int_val;
        }

        // The following loops are buggy, but will never be run, as their config values are left 0.

        if (ingredients[i].actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostMaxHeartLevel") &&
            int_val > 0) {
            // i < 1 check needs to come after others.
            for ([[maybe_unused]] int _ = 0; i < 1; i++) {
                if (cook_item.effect_id == CookEffectId::LifeMaxUp) {
                    cook_item.vitality_boost += (f32)int_val;
                }
            }
        }

        if (ingredients[i].actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostStaminaLevel") &&
            int_val > 0) {
            // i < 1 check needs to come after others.
            for ([[maybe_unused]] int _ = 0; i < 1; i++) {
                if (cook_item.effect_id == CookEffectId::GutsRecover ||
                    cook_item.effect_id == CookEffectId::ExGutsMaxUp) {
                    cook_item.vitality_boost += (f32)int_val;
                }
            }
        }
    }
}

void CookingMgr::cookCalcItemPrice(const IngredientArray& ingredients, CookItem& cook_item) const {
    cook_item.sell_price = 0;

    if (mFairyTonicName == cook_item.actor_name) {
        // Fairy Tonic is sold for 2 rupees.
        cook_item.sell_price = 2;
        return;
    }

    s32 int_val = 0;
    s32 max_price = 0;
    s32 mult_idx = 0;

    for (int i = 0; i < NumIngredientsMax; ++i) {
        const auto& ingredient = ingredients[i];
        const auto& actor_data = ingredient.actor_data;

        if (!ingredient.arg)
            break;

        if (ksys::act::InfoData::instance()->hasTag(actor_data, ksys::act::tags::CookLowPrice)) {
            // This ingredient is only worth 1 rupee.
            mult_idx += ingredient.arg->count;
            cook_item.sell_price += ingredient.arg->count;
            max_price += ingredient.arg->count;
        } else {
            if (actor_data.tryGetIntByKey(&int_val, "itemSellingPrice")) {
                mult_idx += ingredient.arg->count;
                cook_item.sell_price += int_val * ingredient.arg->count;
            }
            if (actor_data.tryGetIntByKey(&int_val, "itemBuyingPrice")) {
                max_price += int_val * ingredient.arg->count;
            }
        }
    }

    if (mult_idx >= 1) {
        cook_item.sell_price =
            (s32)(mIngredientNumMultipliers[mult_idx - 1] * (f32)cook_item.sell_price);
    }

    if (cook_item.sell_price >= 1) {
        // Round up to the nearest power of 10
        if (cook_item.sell_price % 10 != 0) {
            cook_item.sell_price = cook_item.sell_price + 10 - cook_item.sell_price % 10;
        }
    }

    // clamp and clampMin don't work here.
    cook_item.sell_price = sead::Mathi::min(max_price, cook_item.sell_price);
    cook_item.sell_price = sead::Mathi::max(cook_item.sell_price, 2);
}

void CookingMgr::cookCalcIngredientsBoost(const IngredientArray& ingredients,
                                          CookItem& cook_item) const {
    const bool is_medicine = isMedicine(cook_item);
    const bool is_not_fairy_tonic = mFairyTonicName != cook_item.actor_name;

    sead::SafeArray<s32, NumEffectSlots> effect_counts{};
    sead::SafeArray<s32, NumEffectSlots> cure_levels{};

    s32 stamina_boost = 0;
    s32 life_boost = 0;
    s32 time_boost = 0;
    s32 total_count = 0;
    s32 life_recover = 0;
    s32 int_val;

    for (int i = 0; i < NumIngredientsMax; i++) {
        if (!ingredients[i].arg)
            break;

        const al::ByamlIter& actor_data = ingredients[i].actor_data;
        const s32 count = ingredients[i].arg->count;

        total_count += count;

        if (ksys::act::InfoData::instance()->hasTag(actor_data, ksys::act::tags::CookEnemy)) {
            if (actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostEffectiveTime") && int_val > 0) {
                time_boost += int_val * count;
            }

            if (actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostMaxHeartLevel") && int_val > 0) {
                life_boost += int_val * count;
            }

            if (actor_data.tryGetIntByKey(&int_val, "cookSpiceBoostStaminaLevel") && int_val > 0) {
                stamina_boost += int_val * count;
            }
        } else {
            if (actor_data.tryGetIntByKey(&int_val, "cureItemHitPointRecover") && int_val > 0) {
                life_recover += int_val * count;
            }

            if (actor_data.tryGetIntByKey(&int_val, "cureItemEffectLevel") && int_val > 0) {
                const char* string_val = nullptr;
                if (actor_data.tryGetStringByKey(&string_val, "cureItemEffectType")) {
                    const auto effect_id = getCookEffectIdByName(string_val);
                    if (effect_id != CookEffectId::None) {
                        effect_counts[(int)effect_id] += count;
                        cure_levels[(int)effect_id] += int_val * count;
                    }
                }
            }
        }
    }

    bool effect_found = false;
    for (int i = 0; i < NumEffectSlots; i++) {
        const s32 effect_count = effect_counts[i];
        if (effect_count > 0) {
            if (effect_found) {
                // Finding a second effect makes them cancel out.
                effect_found = false;
                cook_item.vitality_boost = 0.0f;
                cook_item.effect_id = CookEffectId::None;
                cook_item.effect_time = 0;
                break;
            }

            const auto& entry = mCookingEffectEntries[i];

            cook_item.vitality_boost = (f32)cure_levels[i] * entry.multiplier;

            const auto effect_id = (CookEffectId)i;
            cook_item.effect_id = effect_id;

            const s32 boost_time = entry.boost_time;
            if (boost_time > 0)
                cook_item.effect_time = time_boost + 30 * total_count + boost_time * effect_count;

            if (effect_id == CookEffectId::LifeMaxUp) {
                cook_item.vitality_boost += (f32)life_boost;
            } else if (effect_id == CookEffectId::GutsRecover ||
                       effect_id == CookEffectId::ExGutsMaxUp) {
                cook_item.vitality_boost += (f32)stamina_boost;
            }

            effect_found = true;
        }
    }

    if (!is_not_fairy_tonic && effect_found) {
        effect_found = false;
        cook_item.vitality_boost = 0.0f;
        cook_item.effect_id = CookEffectId::None;
        cook_item.effect_time = 0;
    }

    if (is_medicine && !effect_found) {
        cook_item.actor_name = mFailActorName;
    }

    if (isCookFailure(cook_item)) {
        cook_item.life_recover = (f32)life_recover * mFailActorLifeRecoverMultiplier;
    } else if (effect_found) {
        cook_item.life_recover = (f32)life_recover * mLifeRecoverMultiplier;
    } else {
        cook_item.life_recover =
            (f32)life_recover * getCookingEffectEntry(CookEffectId::LifeRecover).multiplier;
    }

    if (cook_item.effect_id != CookEffectId::None) {
        const s32 max = getCookingEffectEntry(cook_item.effect_id).max;
        if (cook_item.vitality_boost > (f32)max)
            cook_item.vitality_boost = (f32)max;
    }
}

bool CookingMgr::findIngredientByName(CookingMgr::IngredientArray& ingredients, u32 name_hash,
                                      int num_ingredients) const {
    for (int ingredient_idx = 0; ingredient_idx < num_ingredients; ingredient_idx++) {
        Ingredient& ingredient = ingredients[ingredient_idx];
        if (!ingredient.used_in_recipe && ingredient.name_hash == name_hash) {
            ingredient.used_in_recipe = true;
            return true;
        }
    }
    return false;
}

bool CookingMgr::findIngredientByTag(CookingMgr::IngredientArray& ingredients, u32 tag_hash,
                                     int num_ingredients) const {
    for (int ingredient_idx = 0; ingredient_idx < num_ingredients; ingredient_idx++) {
        Ingredient& ingredient = ingredients[ingredient_idx];
        if (!ingredient.used_in_recipe &&
            ksys::act::InfoData::instance()->hasTag(ingredient.actor_data, tag_hash)) {
            ingredient.used_in_recipe = true;
            return true;
        }
    }
    return false;
}

bool CookingMgr::isMedicine(const CookItem& cook_item) const {
    return !cook_item.actor_name.isEmpty() &&
           ksys::act::InfoData::instance()->hasTag(cook_item.actor_name.cstr(),
                                                   ksys::act::tags::CookEMedicine);
}

bool CookingMgr::isCookFailure(const CookItem& cook_item) const {
    return !cook_item.actor_name.isEmpty() &&
           ksys::act::InfoData::instance()->hasTag(cook_item.actor_name.cstr(),
                                                   ksys::act::tags::CookFailure);
}

bool CookingMgr::hasMonsterExtract(const CookingMgr::IngredientArray& ingredients) const {
    for (int i = 0; i < NumIngredientsMax; i++) {
        const auto& ingredient = ingredients[i];
        if (ingredient.arg && ingredient.arg->name == mMonsterExtractName) {
            return true;
        }
    }
    return false;
}

CookEffectId CookingMgr::getCookEffectId(u32 name_hash) const {
    CookEffectId entry_idx;

    if (sCrc32Constants.crc32_life_recover == name_hash)
        entry_idx = CookEffectId::LifeRecover;
    else if (sCrc32Constants.crc32_guts_performance == name_hash)
        entry_idx = CookEffectId::ExGutsMaxUp;
    else if (sCrc32Constants.crc32_stamina_recover == name_hash)
        entry_idx = CookEffectId::GutsRecover;
    else if (sCrc32Constants.crc32_life_max_up == name_hash)
        entry_idx = CookEffectId::LifeMaxUp;
    else if (sCrc32Constants.crc32_resist_hot == name_hash)
        entry_idx = CookEffectId::ResistHot;
    else if (sCrc32Constants.crc32_resist_cold == name_hash)
        entry_idx = CookEffectId::ResistCold;
    else if (sCrc32Constants.crc32_resist_electric == name_hash)
        entry_idx = CookEffectId::ResistElectric;
    else if (sCrc32Constants.crc32_all_speed == name_hash)
        entry_idx = CookEffectId::MovingSpeed;
    else if (sCrc32Constants.crc32_attack_up == name_hash)
        entry_idx = CookEffectId::AttackUp;
    else if (sCrc32Constants.crc32_defense_up == name_hash)
        entry_idx = CookEffectId::DefenseUp;
    else if (sCrc32Constants.crc32_quietness == name_hash)
        entry_idx = CookEffectId::Quietness;
    else if (sCrc32Constants.crc32_fireproof == name_hash)
        entry_idx = CookEffectId::Fireproof;
    else
        entry_idx = CookEffectId::None;
    return entry_idx;
}

CookEffectId CookingMgr::getCookEffectIdByName(const sead::SafeString& effect_name) const {
    const auto name_hash = sead::HashCRC32::calcStringHash(effect_name);
    return getCookEffectIdFromTreeMap(name_hash);
}

CookEffectId CookingMgr::getCookEffectIdFromTreeMap(const u32 name_hash) const {
    if (const auto* node = mCookingEffectNameIdMap.find(name_hash)) {
        return node->value();
    }
    return CookEffectId::None;
}

void CookingMgr::init(sead::Heap* heap) {
    ksys::res::LoadRequest req;

    req.mRequester = "CookingMgr";
    req._22 = false;

    sead::FixedSafeString<0x80> path;
    path.format("Cooking/CookData.byml");

    auto* res = sead::DynamicCast<sead::DirectResource>(mResHandle.load(path, &req));
    if (!res)
        return;

    mConfig = mConfig ? new (mConfig) al::ByamlIter(res->getRawData()) :
                        new (heap) al::ByamlIter(res->getRawData());

    mCookingEffectNameIdMap.clear();

    for (int effect_idx = 0; effect_idx < NumEffects; effect_idx++) {
        auto& effect = sCookingEffects[effect_idx];
        const u32 name_hash = sead::HashCRC32::calcStringHash(effect.name);
        mCookingEffectNameIdMap.insert(name_hash, effect.effect_id);
    }

    for (int i = 0; i < NumEffectSlots; i++) {
        mCookingEffectEntries[i] = CookingEffectEntry{};
        mCookingEffectEntries[i].ssa = 0;
    }

    for (int i = 0; i < NumIngredientsMax; i++) {
        mIngredientNumMultipliers[i] = 1.0f;
    }

    // Must be separate from previous loop.
    for (int i = 0; i < NumIngredientsMax; i++) {
        mIngredientNumSuccessRates[i] = 5 * i;
    }

    mFairyTonicName = "Item_Cook_C_16";
    mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);

    mFailActorName = "Item_Cook_O_01";
    mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);

    mMonsterExtractName = "Item_Material_08";
    mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);

    mLifeRecoverMultiplier = 1.0;
    mStoneFoodActorLifeRecover = 1;
    mCritEffectTime = 300;
    mFailActorLifeRecoverMultiplier = 1.0;
    mFailActorLifeRecover = 4;

    al::ByamlIter iter;
    al::ByamlIter cei_iter;
    al::ByamlIter entry_iter;

    const char* string_val = nullptr;
    int int_val;
    u32 uint_val;
    float float_val;

    if (mConfig->tryGetIterByKey(&iter, "System")) {
        if (iter.tryGetStringByKey(&string_val, "FA")) {
            mFailActorName = string_val;
            mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);
        }
        if (iter.tryGetStringByKey(&string_val, "FCA")) {
            mFairyTonicName = string_val;
            mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);
        }
        if (iter.tryGetStringByKey(&string_val, "MEA")) {
            mMonsterExtractName = string_val;
            mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);
        }

        if (iter.tryGetFloatByKey(&float_val, "LRMR") && float_val >= 0)
            mLifeRecoverMultiplier = float_val;
        if (iter.tryGetFloatByKey(&float_val, "FALRMR") && float_val >= 0)
            mFailActorLifeRecoverMultiplier = float_val;
        if (iter.tryGetIntByKey(&int_val, "FALR") && int_val >= 0)
            mFailActorLifeRecover = int_val;
        if (iter.tryGetIntByKey(&int_val, "SFALR") && int_val >= 0)
            mStoneFoodActorLifeRecover = int_val;
        if (iter.tryGetIntByKey(&int_val, "SSAET") && int_val >= 0)
            mCritEffectTime = int_val;

        if (iter.tryGetIterByKey(&cei_iter, "CEI")) {
            const int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIterByIndex(&entry_iter, i) &&
                    entry_iter.tryGetUIntByKey(&uint_val, "T")) {
                    const u32 name_hash = uint_val;

                    const CookEffectId entry_idx = getCookEffectId(name_hash);

                    if (entry_idx == CookEffectId::None)
                        continue;

                    if (entry_iter.tryGetIntByKey(&int_val, "BT"))
                        getCookingEffectEntry(entry_idx).boost_time = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Ma"))
                        getCookingEffectEntry(entry_idx).max = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Mi"))
                        getCookingEffectEntry(entry_idx).min = int_val;

                    if (entry_iter.tryGetFloatByKey(&float_val, "MR"))
                        getCookingEffectEntry(entry_idx).multiplier = float_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "SSA"))
                        getCookingEffectEntry(entry_idx).ssa = int_val;
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMMR")) {
            const int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetFloatByIndex(&float_val, i) && i < NumIngredientsMax) {
                    mIngredientNumMultipliers[i] = sead::Mathf::clamp(float_val, 0.0f, 5.0f);
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMSSR")) {
            const int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIntByIndex(&int_val, i) && i < NumIngredientsMax) {
                    mIngredientNumSuccessRates[i] = sead::Mathi::clamp(int_val, -100, 100);
                }
            }
        }
    }
}

// NON_MATCHING
bool CookingMgr::cook(const CookArg& arg, CookItem& cook_item,
                      const CookingMgr::BoostArg& boost_arg) {
    ksys::act::InfoData* actor_info_data = ksys::act::InfoData::instance();

    al::ByamlIter recipes_iter;
    sead::SafeArray<Ingredient, NumIngredientsMax> ingredients;

    int num_ingredients = 0;
    if (mConfig && actor_info_data) {
        for (int i = 0; i < NumIngredientsMax; i++) {
            const auto& cook_ingredient = arg.ingredients[i];
            if (!cook_ingredient.name.isEmpty()) {
                const u32 name_hash = sead::HashCRC32::calcStringHash(cook_ingredient.name);
                auto& ingredient = ingredients[num_ingredients];
                if (actor_info_data->getActorIter(&ingredient.actor_data, name_hash)) {
                    ingredient.name_hash = name_hash;
                    ingredient.arg = &cook_ingredient;
                    num_ingredients++;
                }
            }
        }
    }

    if (!mConfig || !actor_info_data || num_ingredients == 0) {
        // Unused label:
        //    COOK_FAILURE_FOR_MISSING_CONFIG:
        cookFailForMissingConfig(cook_item, mFailActorName);
        return false;
    }

    const Ingredient* single_ingredient = nullptr;
    bool multiple_non_spice_ingredients = false;

    if (num_ingredients > 1) {
        if (mConfig->tryGetIterByKey(&recipes_iter, "Recipes")) {
            const s32 num_recipes = recipes_iter.getSize();
            const char* string_val = nullptr;
            u32 uint_val = 0;
            al::ByamlIter recipe_iter;
            al::ByamlIter hash_iter;
            al::ByamlIter actors_iter;
            al::ByamlIter tags_iter;

            if (num_recipes > 0) {
                for (int recipe_idx = 0; recipe_idx < num_recipes; recipe_idx++) {
                    if (!recipes_iter.tryGetIterByIndex(&recipe_iter, recipe_idx))
                        continue;

                    recipe_iter.tryGetStringByKey(&string_val, "Result");
                    recipe_iter.tryGetUIntByKey(&uint_val, "Recipe");
                    const s32 num_actors = recipe_iter.tryGetIterByKey(&actors_iter, "Actors") ?
                                               actors_iter.getSize() :
                                               0;
                    const s32 num_tags =
                        recipe_iter.tryGetIterByKey(&tags_iter, "Tags") ? tags_iter.getSize() : 0;

                    if (num_actors + num_tags > num_ingredients ||
                        (num_actors == 0 && num_tags == 0))
                        continue;

                    ingredients[0].used_in_recipe = false;
                    ingredients[1].used_in_recipe = false;
                    ingredients[2].used_in_recipe = false;
                    ingredients[3].used_in_recipe = false;
                    ingredients[4].used_in_recipe = false;

                    // Each recipe entry can have a list of sets of Actors, and a list of sets of
                    // Tags. An ingredient must be found for each set of Actors and Tags.

                    if (num_actors > 0) {
                        bool any_actors_missed = false;

                        for (int actor_idx = 0; actor_idx < num_actors; actor_idx++) {
                            if (actors_iter.tryGetIterByIndex(&hash_iter, actor_idx)) {
                                const s32 num_hashes = hash_iter.getSize();
                                if (num_hashes < 1)
                                    continue;
                                bool found = false;
                                for (int hash_idx = 0; hash_idx < num_hashes; hash_idx++) {
                                    u32 hash_val;
                                    if (hash_iter.tryGetUIntByIndex(&hash_val, hash_idx)) {
                                        // Any actor in this list will work.
                                        found = findIngredientByName(ingredients, hash_val,
                                                                     num_ingredients);
                                        if (found)
                                            break;
                                    }
                                }
                                if (!found) {
                                    any_actors_missed = true;
                                    break;
                                }
                            }
                            if (any_actors_missed)
                                break;
                        }

                        if (any_actors_missed)
                            continue;
                    }

                    if (num_tags > 0) {
                        bool any_tags_missed = false;

                        for (int tag_idx = 0; tag_idx < num_tags; tag_idx++) {
                            if (tags_iter.tryGetIterByIndex(&hash_iter, tag_idx)) {
                                const s32 num_hashes = hash_iter.getSize();
                                bool found = false;
                                for (int hash_idx = 0; hash_idx < num_hashes; hash_idx++) {
                                    u32 hash_val;
                                    if (hash_iter.tryGetUIntByIndex(&hash_val, hash_idx)) {
                                        // Any tag in this list will work.
                                        found = findIngredientByTag(ingredients, hash_val,
                                                                    num_ingredients);
                                        if (found)
                                            break;
                                    }
                                }
                                if (!found) {
                                    any_tags_missed = true;
                                    break;
                                }
                            }
                            if (any_tags_missed)
                                break;
                        }

                        if (any_tags_missed)
                            continue;
                    }

                    al::ByamlIter actor_iter;
                    if (!actor_info_data->getActorIter(&actor_iter, uint_val))
                        continue;

                    actor_iter.tryGetStringByKey(&string_val, "name");
                    cook_item.actor_name = string_val;

                    cookCalcIngredientsBoost(ingredients, cook_item);

                    if (isCookFailure(cook_item)) {
                        goto COOK_FAILURE;
                    }

                    cookCalcCritBoost(ingredients, cook_item, &boost_arg);
                    cookCalcSpiceBoost(ingredients, cook_item);

                    cookCalcRecipeBoost(recipe_iter, cook_item);

                    cookAdjustItem(cook_item);

                    cookCalcItemPrice(ingredients, cook_item);
                    return true;
                }
            }
        }

        single_ingredient = nullptr;
        for (int ingredient_idx = 0; ingredient_idx < num_ingredients; ingredient_idx++) {
            const auto& ingredient = ingredients[ingredient_idx];
            if (actor_info_data->hasTag(ingredient.actor_data, ksys::act::tags::CookSpice))
                continue;

            if (single_ingredient) {
                multiple_non_spice_ingredients = true;
                break;
            }

            single_ingredient = &ingredient;
        }
    } else {
        single_ingredient = &ingredients[0];
    }

    if (single_ingredient && !multiple_non_spice_ingredients) {
        if (mConfig->tryGetIterByKey(&recipes_iter, "SingleRecipes")) {
            const s32 num_recipes = recipes_iter.getSize();
            const char* string_val = nullptr;
            s32 int_val;
            u32 uint_val = 0;
            al::ByamlIter recipe_iter;
            al::ByamlIter actors_iter;
            al::ByamlIter tags_iter;

            if (num_recipes > 0) {
                for (int recipe_idx = 0; recipe_idx < num_recipes; recipe_idx++) {
                    if (!recipes_iter.tryGetIterByIndex(&recipe_iter, recipe_idx))
                        continue;

                    recipe_iter.tryGetStringByKey(&string_val, "Result");
                    recipe_iter.tryGetUIntByKey(&uint_val, "Recipe");

                    if (!recipe_iter.tryGetIntByKey(&int_val, "Num") || num_ingredients < int_val)
                        continue;

                    const s32 num_actors = recipe_iter.tryGetIterByKey(&actors_iter, "Actors") ?
                                               actors_iter.getSize() :
                                               0;
                    const s32 num_tags =
                        recipe_iter.tryGetIterByKey(&tags_iter, "Tags") ? tags_iter.getSize() : 0;

                    if (num_actors + num_tags > num_ingredients ||
                        (num_actors == 0 && num_tags == 0))
                        continue;

                    if (num_actors > 0) {
                        bool found = false;
                        for (int hash_idx = 0; hash_idx < num_actors; hash_idx++) {
                            u32 hash_val;
                            if (actors_iter.tryGetUIntByIndex(&hash_val, hash_idx) &&
                                single_ingredient->name_hash == hash_val) {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            continue;
                    }

                    if (num_tags > 0) {
                        bool found = false;
                        for (int hash_idx = 0; hash_idx < num_tags; hash_idx++) {
                            u32 hash_val;
                            if (tags_iter.tryGetUIntByIndex(&hash_val, hash_idx) &&
                                actor_info_data->hasTag(single_ingredient->actor_data, hash_val)) {
                                found = true;
                                break;
                            }
                        }
                        if (!found)
                            continue;
                    }

                    al::ByamlIter actorIter;
                    if (!actor_info_data->getActorIter(&actorIter, uint_val))
                        continue;

                    actorIter.tryGetStringByKey(&string_val, "name");
                    cook_item.actor_name = string_val;

                    cookCalcIngredientsBoost(ingredients, cook_item);

                    if (isCookFailure(cook_item)) {
                        goto COOK_FAILURE;
                    }

                    cookCalcCritBoost(ingredients, cook_item, &boost_arg);
                    cookCalcSpiceBoost(ingredients, cook_item);

                    cookCalcRecipeBoost(recipe_iter, cook_item);

                    cookAdjustItem(cook_item);

                    cookCalcItemPrice(ingredients, cook_item);
                    return true;
                }
            }
        }
    }

    cook_item.actor_name = mFailActorName;
    cookCalcIngredientsBoost(ingredients, cook_item);

COOK_FAILURE:
    cookFail(cook_item);
    return true;
}

void CookingMgr::cookCalcRecipeBoost(const al::ByamlIter& recipe_iter, CookItem& cook_item) const {
    int int_val;

    if (recipe_iter.tryGetIntByKey(&int_val, "HB"))
        cook_item.life_recover += (f32)int_val;

    if (recipe_iter.tryGetIntByKey(&int_val, "TB")) {
        if (cook_item.effect_time > 0) {
            cook_item.effect_time += int_val;
        }
    }
}

void CookingMgr::cookAdjustItem(CookItem& cook_item) const {
    cook_item.life_recover = (f32)(s32)cook_item.life_recover;

    const f32 life_recover_max = (f32)getCookingEffectEntry(CookEffectId::LifeRecover).max;
    if (cook_item.life_recover > life_recover_max)
        cook_item.life_recover = life_recover_max;
    if (cook_item.life_recover < 0.0f)
        cook_item.life_recover = 0.0f;

    if (cook_item.effect_id == CookEffectId::None) {
        if (cook_item.life_recover == 0.0f)
            cook_item.life_recover = 1.0f;
    } else {
        if (cook_item.vitality_boost > 0.0f && cook_item.vitality_boost < 1.0f)
            cook_item.vitality_boost = 1.0f;

        s32 vitality_boost = (s32)cook_item.vitality_boost;

        const s32 vitality_boost_max = getCookingEffectEntry(cook_item.effect_id).max;
        if (vitality_boost > vitality_boost_max)
            vitality_boost = vitality_boost_max;

        if (cook_item.effect_id == CookEffectId::GutsRecover)
            vitality_boost = vitality_boost * 200;

        f32 vitality_boost_f = cook_item.vitality_boost = (f32)vitality_boost;

        if (cook_item.effect_id == CookEffectId::LifeMaxUp) {
            if ((s32)vitality_boost_f % 4 != 0) {
                // Round up to whole heart.
                vitality_boost_f = (f32)(((s32)vitality_boost_f + 4) & ~3u);
                cook_item.vitality_boost = vitality_boost_f;
            }

            if (vitality_boost_f < 4.0f) {
                vitality_boost_f = 4.0f;
                cook_item.vitality_boost = 4.0f;
            }

            cook_item.life_recover = vitality_boost_f;
        }
    }

    cook_item.effect_time = sead::Mathi::clamp(cook_item.effect_time, 0, 1800);
}

void CookingMgr::resetArgCookData(CookArg& arg,
                                  const sead::Buffer<sead::FixedSafeString<64>>& ingredient_names,
                                  int num_ingredients, CookItem& cook_item) const {
    for (int i = 0; i < NumIngredientsMax; i++) {
        arg.ingredients[i].name = "";
        arg.ingredients[i].count = 0;
    }

    arg.ingredients[0].count = 1;
    arg.ingredients[0].name = ingredient_names[0];

    for (int i = 1; i < num_ingredients; i++) {
        for (int j = 0; j < NumIngredientsMax; j++) {
            auto& ingredient = arg.ingredients[j];
            if (ingredient.name == ingredient_names[i]) {
                ingredient.count++;
                break;
            }
            if (ingredient.name.isEmpty()) {
                ingredient.count = 1;
                ingredient.name = ingredient_names[i];
                break;
            }
        }
    }

    cook_item.reset();

    for (int i = 0; i < NumIngredientsMax && i < num_ingredients; i++) {
        cook_item.ingredients[i] = ingredient_names[i];
    }
}

void CookingMgr::prepareCookArg(
    CookArg& arg, const sead::SafeArray<sead::FixedSafeString<64>, NumIngredientsMax>& item_names,
    int num_items, CookItem& cook_item) const {
    for (int i = 0; i < NumIngredientsMax; i++) {
        arg.ingredients[i].name = "";
        arg.ingredients[i].count = 0;
    }

    arg.ingredients[0].count = 1;
    arg.ingredients[0].name = item_names[0];

    for (int i = 1; i < num_items; i++) {
        const auto& item_name = item_names[i];
        for (int j = 0; j < NumIngredientsMax; j++) {
            auto& ingredient = arg.ingredients[j];
            if (ingredient.name == item_name) {
                ingredient.count++;
                break;
            }
            if (ingredient.name.isEmpty()) {
                ingredient.count = 1;
                ingredient.name = item_name;
                break;
            }
        }
    }

    cook_item.reset();

    for (int i = 0; i < NumIngredientsMax && i < num_items; i++) {
        cook_item.ingredients[i] = item_names[i];
    }
}

bool CookingMgr::cookWithItems(const sead::SafeString& item1, const sead::SafeString& item2,
                               const sead::SafeString& item3, const sead::SafeString& item4,
                               const sead::SafeString& item5, CookItem& cook_item,
                               const CookingMgr::BoostArg& boost_arg) {
    CookArg arg;
    sead::SafeArray<sead::FixedSafeString<64>, NumIngredientsMax> item_names;

    int num_items = 0;

    if (!item1.isEmpty()) {
        item_names[num_items].copy(item1);
        num_items++;
    }

    if (!item2.isEmpty()) {
        item_names[num_items].copy(item2);
        num_items++;
    }

    if (!item3.isEmpty()) {
        item_names[num_items].copy(item3);
        num_items++;
    }

    if (!item4.isEmpty()) {
        item_names[num_items].copy(item4);
        num_items++;
    }

    if (!item5.isEmpty()) {
        item_names[num_items].copy(item5);
        num_items++;
    }

    if (num_items > 0) {
        prepareCookArg(arg, item_names, num_items, cook_item);
        if (cook(arg, cook_item, boost_arg))
            return true;
    }
    return false;
}

void CookingMgr::setCookItem(const CookItem& from) {
    from.copy(mCookItem);
}

void CookingMgr::resetCookItem() {
    mCookItem.reset();
}

void CookingMgr::getCookItem(CookItem& to) const {
    mCookItem.copy(to);
}

}  // namespace uking
