#include "Game/Cooking/cookManager.h"
#include <codec/seadHashCRC32.h>
#include <random/seadGlobalRandom.h>
#include <typeindex>
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/Resource/resLoadRequest.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking {

struct CookingEffect {
    sead::SafeString name;
    u32 effect_id;
};

static const CookingEffect sCookingEffects[CookingMgr::NumEffects]{
    {"None", -1u},     {"LifeRecover", 1},    {"LifeMaxUp", 2},    {"ResistHot", 4},
    {"ResistCold", 5}, {"ResistElectric", 6}, {"AttackUp", 10},    {"DefenseUp", 11},
    {"Quietness", 12}, {"MovingSpeed", 13},   {"GutsRecover", 14}, {"ExGutsMaxUp", 15},
    {"Fireproof", 16},
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
    _224 = false;
    item_price = 0;
    effect_id = -1;
    stamina_recover = 0.0f;
    for (auto& ingredient : ingredients) {
        ingredient.clear();
    }
}

void CookItem::copy(CookItem& to) const {
    to.actor_name = actor_name;
    to.life_recover = life_recover;
    to.effect_time = effect_time;
    to._224 = _224;
    to.item_price = item_price;
    to.stamina_recover = stamina_recover;
    to.effect_id = effect_id;
    to.ingredients = ingredients;
}

CookingMgr::CookingMgr() = default;

SEAD_SINGLETON_DISPOSER_IMPL(CookingMgr)

CookingMgr::~CookingMgr() {
    if (mConfig) {
        delete mConfig;
        mConfig = nullptr;
    }
}

void CookingMgr::cookFail(CookItem& item) {
    if (item.actor_name.isEmpty())
        item.actor_name.copy(mFailActorName);

    f32 life_recover;
    if (item.actor_name == mFailActorName) {
        // Dubious food
        item.effect_time = 0;
        f32 min_recovery = (f32)(s32)mFALR;
        life_recover = min_recovery > item.life_recover ? min_recovery : item.life_recover;
    } else {
        // Rock-hard food
        item.effect_time = 0;
        life_recover = (f32)(s32)mSFALR;
    }

    item.life_recover = life_recover;
    item.stamina_recover = 0.0f;
    item.effect_id = -1;
    item.item_price = 2;
}

void CookingMgr::cookFailForMissingConfig(CookItem& item, const sead::SafeString& name) {
    f32 life_recover;
    if (name.isEmpty() || name == mFailActorName) {
        item.actor_name.copy(mFailActorName);
        item.effect_time = 0;
        life_recover = (f32)(s32)mFALR;
    } else {
        item.actor_name = name;
        item.effect_time = 0;
        life_recover = (f32)(s32)mSFALR;
    }

    item.life_recover = life_recover;
    item.stamina_recover = 0.0f;
    item.effect_id = -1;
    item.item_price = 1;
}

// NON_MATCHING
void CookingMgr::cookCalcBoost(const CookingMgr::Ingredient* ingredients, CookItem& item,
                               const BoostArg* boost_arg) const {
    // Find if any of the ingredients are Monster Extract.
    bool found_monster_extract = false;
    for (int i = 0; i < NumIngredientsMax; i++) {
        const auto& ingredient = ingredients[i];
        if (ingredient.arg && ingredient.arg->name == mMonsterExtractName) {
            found_monster_extract = true;
            break;
        }
    }

    if (found_monster_extract) {
        // Monster Extract found; calculate boosts.
        s32 effect_min = item.life_recover <= 0.0f || item.effect_id == 2 ? 2 : 0;
        s32 effect_max = item.effect_id == -1 ? 2 : 4;
        switch (sead::GlobalRandom::instance()->getS32Range(effect_min, effect_max)) {
        case 0:
            item.life_recover += (float)mCookingEffectEntries[1].ssa;
            break;
        case 1:
            item.life_recover += (float)mCookingEffectEntries[1].mi;
            break;
        case 2:
            if (item.effect_id != -1) {
                if (item.stamina_recover > 0.0f && item.stamina_recover < 1.0f) {
                    item.stamina_recover = 1.0;
                }
                item.stamina_recover += (float)mCookingEffectEntries[item.effect_id].ssa;
            }
            break;
        case 3:
            if (item.effect_id != -1) {
                item.stamina_recover = (float)mCookingEffectEntries[item.effect_id].mi;
            }
            break;
        default:
            break;
        }

        // Effect time
        if (item.effect_time >= 1) {
            u64 roll = sead::GlobalRandom::instance()->getU32(3);
            s32 new_time;
            if (roll == 2)
                // 30 minutes
                new_time = 1800;
            else if (roll == 1)
                // 10 minutes
                new_time = 600;
            else if (roll == 0)
                // 1 minute
                new_time = 60;
            else
                return;
            item.effect_time = new_time;
        }

        return;
    }

    if (boost_arg && boost_arg->always_boost) {
        cookHandleBoostSuccessInner(ingredients, item);
        return;
    }

    if (boost_arg && !boost_arg->enable_random_boost) {
        return;
    }

    s32 success_rate = 0;
    s32 num_ingredients = 0;
    s32 threshold = 0;

    for (int i = 0; i < NumIngredientsMax; i++) {
        const auto& ingredient = ingredients[i];
        if (ingredient.arg) {
            num_ingredients++;
            if (ingredient.actor_data.tryGetIntByKey(&success_rate, "cookSpiceBoostSuccessRate") &&
                success_rate > threshold) {
                threshold = success_rate;
            }
        }
    }

    if (num_ingredients >= 1)
        threshold += mNMSSR[num_ingredients - 1];

    if ((s32)sead::GlobalRandom::instance()->getU32(100) < threshold) {
        cookHandleBoostSuccessInner(ingredients, item);
    }
}

void CookingMgr::cookCalcItemPrice(const CookingMgr::Ingredient* ingredients,
                                   CookItem& item) const {
    item.item_price = 0;
    s32 price;

    if (mFairyTonicName == item.actor_name) {
        item.item_price = 2;
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
            s32 p = ingredient.arg->_58;
            mult_idx += p;
            item.item_price += p;
            max_price += ingredient.arg->_58;
        } else {
            if (actor_data.tryGetIntByKey(&int_val, "itemSellingPrice")) {
                s32 p = ingredient.arg->_58;
                mult_idx += p;
                item.item_price += int_val * p;
            }
            if (actor_data.tryGetIntByKey(&int_val, "itemBuyingPrice")) {
                max_price += int_val * ingredient.arg->_58;
            }
        }
    }

    if (mult_idx >= 1) {
        price = (s32)(mNMMR[mult_idx - 1] * (float)item.item_price);
        item.item_price = price;
    } else {
        price = item.item_price;
    }

    if (price >= 1) {
        // Round up to the nearest power of 10
        if (price % 10 != 0) {
            price = price + 10 - price % 10;
            item.item_price = price;
        }
    }

    if (max_price < price)
        price = max_price;
    if (price <= 2)
        price = 2;

    item.item_price = price;
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
        u32 name_hash = sead::HashCRC32::calcStringHash(effect.name);
        mCookingEffectNameIdMap.insert(name_hash, effect.effect_id);
    }

    for (int i = 0; i < NumEffectSlots; i++) {
        mCookingEffectEntries[i] = CookingEffectEntry{};
        mCookingEffectEntries[i].ssa = 0;
    }

    mNMMR[0] = 1.0f;
    mNMMR[1] = 1.0f;
    mNMMR[2] = 1.0f;
    mNMMR[3] = 1.0f;
    mNMMR[4] = 1.0f;

    mNMSSR[0] = 0;
    mNMSSR[1] = 5;
    mNMSSR[2] = 10;
    mNMSSR[3] = 15;
    mNMSSR[4] = 20;

    mFairyTonicName = "Item_Cook_C_16";
    mFairyTonicNameHash = sead::HashCRC32::calcStringHash(mFairyTonicName);

    mFailActorName = "Item_Cook_O_01";
    mFailActorNameHash = sead::HashCRC32::calcStringHash(mFailActorName);

    mMonsterExtractName = "Item_Material_08";
    mMonsterExtractNameHash = sead::HashCRC32::calcStringHash(mMonsterExtractName);

    mLRMR = 1.0;
    mSFALR = 1;
    mSSAET = 300;
    mFALRMR = 1.0;
    mFALR = 4;

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
            mLRMR = float_val;
        if (iter.tryGetFloatByKey(&float_val, "FALRMR") && float_val >= 0)
            mFALRMR = float_val;
        if (iter.tryGetIntByKey(&int_val, "FALR") && int_val >= 0)
            mFALR = int_val;
        if (iter.tryGetIntByKey(&int_val, "SFALR") && int_val >= 0)
            mSFALR = int_val;
        if (iter.tryGetIntByKey(&int_val, "SSAET") && int_val >= 0)
            mSSAET = int_val;

        if (iter.tryGetIterByKey(&cei_iter, "CEI")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIterByIndex(&entry_iter, i) &&
                    entry_iter.tryGetUIntByKey(&uint_val, "T")) {
                    const u32 entry_hash = uint_val;

                    int entry_idx;

                    if (sCrc32Constants.crc32_life_recover == entry_hash)
                        entry_idx = 1;
                    else if (sCrc32Constants.crc32_guts_performance == entry_hash)
                        entry_idx = 15;
                    else if (sCrc32Constants.crc32_stamina_recover == entry_hash)
                        entry_idx = 14;
                    else if (sCrc32Constants.crc32_life_max_up == entry_hash)
                        entry_idx = 2;
                    else if (sCrc32Constants.crc32_resist_hot == entry_hash)
                        entry_idx = 4;
                    else if (sCrc32Constants.crc32_resist_cold == entry_hash)
                        entry_idx = 5;
                    else if (sCrc32Constants.crc32_resist_electric == entry_hash)
                        entry_idx = 6;
                    else if (sCrc32Constants.crc32_all_speed == entry_hash)
                        entry_idx = 13;
                    else if (sCrc32Constants.crc32_attack_up == entry_hash)
                        entry_idx = 10;
                    else if (sCrc32Constants.crc32_defense_up == entry_hash)
                        entry_idx = 11;
                    else if (sCrc32Constants.crc32_quietness == entry_hash)
                        entry_idx = 12;
                    else if (sCrc32Constants.crc32_fireproof == entry_hash)
                        entry_idx = 16;
                    else
                        continue;

                    if (entry_iter.tryGetIntByKey(&int_val, "BT"))
                        mCookingEffectEntries[entry_idx].bt = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Ma"))
                        mCookingEffectEntries[entry_idx].ma = int_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "Mi"))
                        mCookingEffectEntries[entry_idx].mi = int_val;

                    if (entry_iter.tryGetFloatByKey(&float_val, "MR"))
                        mCookingEffectEntries[entry_idx].mr = float_val;

                    if (entry_iter.tryGetIntByKey(&int_val, "SSA"))
                        mCookingEffectEntries[entry_idx].ssa = int_val;
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMMR")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetFloatByIndex(&float_val, i) && i < NumIngredientsMax) {
                    mNMMR[i] = sead::Mathf::clamp(float_val, 0.0f, 5.0f);
                }
            }
        }

        if (iter.tryGetIterByKey(&cei_iter, "NMSSR")) {
            int size = cei_iter.getSize();

            for (int i = 0; i < size; i++) {
                if (cei_iter.tryGetIntByIndex(&int_val, i) && i < NumIngredientsMax) {
                    mNMSSR[i] = sead::Mathi::clamp(int_val, -100, 100);
                }
            }
        }
    }
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
