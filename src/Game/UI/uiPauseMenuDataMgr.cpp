#include "Game/UI/uiPauseMenuDataMgr.h"
#include <algorithm>
#include <container/seadBuffer.h>
#include <limits>
#include <math/seadMathCalcCommon.h>
#include <prim/seadScopedLock.h>
#include "Game/Actor/actWeapon.h"
#include "Game/DLC/aocManager.h"
#include "Game/UI/uiUtils.h"
#include "Game/gameScene.h"
#include "KingSystem/ActorSystem/Profiles/actPlayerBase.h"
#include "KingSystem/ActorSystem/actActorConstDataAccess.h"
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actBaseProcLink.h"
#include "KingSystem/ActorSystem/actInfoCommon.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/ActorSystem/actPlayerInfo.h"
#include "KingSystem/Cooking/cookItem.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtSpecialFlags.h"
#include "KingSystem/System/PlayReportMgr.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/HeapUtil.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(PauseMenuDataMgr)

sead::Vector2f sDummyCookEffect0{-1, 0};

namespace {

sead::SafeArray<CookTagInfo, 11> sCookItemOrder_{{
    {1, "CookFruit", ksys::act::tags::CookFruit},
    {1, "CookMushroom", ksys::act::tags::CookMushroom},
    {1, "CookPlant", ksys::act::tags::CookPlant},
    {1, "CookMeat", ksys::act::tags::CookMeat},
    {1, "CookSpice", ksys::act::tags::CookSpice},
    {1, "CookFish", ksys::act::tags::CookFish},
    {0, "Animal_Insect_F", 0},
    {1, "CookInsect", ksys::act::tags::CookInsect},
    {1, "CookOre", ksys::act::tags::CookOre},
    {1, "CookEnemy", ksys::act::tags::CookEnemy},
    {0, "Obj_FireWoodBundle", 0},
}};

struct PouchStaticData {
    ksys::util::InitTimeInfoEx info;

    u32 last_added_weapon_add_type{};
    u32 last_added_weapon_add_value{};
    f32 _20 = std::numeric_limits<f32>::infinity();
    f32 _24 = std::numeric_limits<f32>::infinity();
    f32 _28 = std::numeric_limits<f32>::infinity();
    u32 _2c{};
    u32 _30{};
    sead::SafeArray<f32, 70> _34{{
        0.0, 1.0, 0.0, 0.0, 0.0, 0.5, 0.5, 0.5, 0.5, 1.0, 0.5, 0.5, 0.5, 0.5, 1.0, 1.0, 1.0, 1.0,
        1.0, 1.0, 1.0, 0.5, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.5, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
        0.0, 0.5, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 1.0, 0.5, 1.0, 1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 0.5,
        1.0, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 0.5, 0.0, 1.0, 1.0, 1.0, 0.0, 1.0, 1.0, 0.5,
    }};
    u32 _14c{};
    u32 _150{};
    u32 _154{};
    u32 _158{};

    sead::SafeString WeaponSmallSword = "WeaponSmallSword";
    sead::SafeString WeaponLargeSword = "WeaponLargeSword";
    sead::SafeString WeaponSpear = "WeaponSpear";
    sead::SafeString WeaponBow = "WeaponBow";
    sead::SafeString WeaponShield = "WeaponShield";
    sead::SafeString ArmorHead = "ArmorHead";
    sead::SafeString ArmorUpper = "ArmorUpper";
    sead::SafeString ArmorLower = "ArmorLower";
    sead::SafeString Item = "Item";
    sead::SafeString PlayerItem = "PlayerItem";
    sead::SafeString HorseReins = "HorseReins";

    sead::SafeString None = "None";

    sead::SafeString Obj_KorokNuts = "Obj_KorokNuts";
    sead::SafeString Obj_DungeonClearSeal = "Obj_DungeonClearSeal";
    sead::SafeString Animal_Insect_F = "Animal_Insect_F";

    sead::SafeString Obj_HeroSoul_Zora = "Obj_HeroSoul_Zora";
    sead::SafeString Obj_HeroSoul_Rito = "Obj_HeroSoul_Rito";
    sead::SafeString Obj_HeroSoul_Goron = "Obj_HeroSoul_Goron";
    sead::SafeString Obj_HeroSoul_Gerudo = "Obj_HeroSoul_Gerudo";

    sead::SafeString Obj_DLC_HeroSoul_Zora = "Obj_DLC_HeroSoul_Zora";
    sead::SafeString Obj_DLC_HeroSoul_Rito = "Obj_DLC_HeroSoul_Rito";
    sead::SafeString Obj_DLC_HeroSoul_Goron = "Obj_DLC_HeroSoul_Goron";
    sead::SafeString Obj_DLC_HeroSoul_Gerudo = "Obj_DLC_HeroSoul_Gerudo";
    sead::SafeString Obj_WarpDLC = "Obj_WarpDLC";

    sead::SafeString Armor_116_Upper = "Armor_116_Upper";
    sead::SafeString Armor_148_Upper = "Armor_148_Upper";
    sead::SafeString Armor_149_Upper = "Armor_149_Upper";
    sead::SafeString Armor_150_Upper = "Armor_150_Upper";
    sead::SafeString Armor_151_Upper = "Armor_151_Upper";

    sead::Buffer<CookTagInfo> cook_item_order{sCookItemOrder_.size(),
                                              sCookItemOrder_.getBufferPtr()};

    sead::SafeArray<sead::SafeString, 7> default_equipment_names{{
        "Weapon_Default_Right",
        "Weapon_Default_Bow",
        "Weapon_Default_Arrow",
        "Weapon_Default_Left",
        "Armor_Default_Head",
        "Armor_Default_Upper",
        "Armor_Default_Lower",
    }};

    sead::SafeArray<sead::SafeString, 5 * 4> divine_helms{{
        "Armor_168_Head", "Armor_169_Head", "Armor_181_Head", "Armor_182_Head", "Armor_183_Head",
        "Armor_184_Head", "Armor_186_Head", "Armor_187_Head", "Armor_188_Head", "Armor_189_Head",
        "Armor_190_Head", "Armor_191_Head", "Armor_192_Head", "Armor_193_Head", "Armor_194_Head",
        "Armor_195_Head", "Armor_196_Head", "Armor_197_Head", "Armor_198_Head", "Armor_199_Head",
    }};
};

PouchStaticData sValues;

void getSameGroupActorName(sead::SafeString* group, const sead::SafeString& item,
                           al::ByamlIter* iter = nullptr) {
    if (iter) {
        ksys::act::getSameGroupActorName(group, item, iter);
    } else {
        ksys::act::getSameGroupActorName(group, item);
    }
}

int getWeaponModifierSortKey(sead::TypedBitFlag<act::WeaponModifier> flags) {
    if (flags.isOn(act::WeaponModifier::AddAtk))
        return flags.isOn(act::WeaponModifier::IsYellow) ? 0 : 1;

    if (flags.isOn(act::WeaponModifier::AddLife))
        return flags.isOn(act::WeaponModifier::IsYellow) ? 4 : 5;

    if (flags.isOn(act::WeaponModifier::AddThrow))
        return 6;

    if (flags.isOn(act::WeaponModifier::AddCrit))
        return 7;

    if (flags.isOn(act::WeaponModifier::AddGuard))
        return flags.isOn(act::WeaponModifier::IsYellow) ? 2 : 3;

    if (flags.isOn(act::WeaponModifier::AddSurfMaster))
        return 8;

    if (flags.isOn(act::WeaponModifier::AddSpreadFire))
        return 10;

    if (flags.isOn(act::WeaponModifier::AddZoomRapid))
        return 11;

    if (flags.isOn(act::WeaponModifier::AddRapidFire))
        return 9;

    return 12;
}

int getFoodSortKey(int* effect_value, const PouchItem* item) {
    const int type = item->getCookData().mCookEffect0.x;
    const int value = item->getCookData().mCookEffect0.y;
    *effect_value = value;
    // TODO: add an enum
    switch (type) {
    case 1:
        return 0;
    case 2:
        return 1;
    case 14:
        return 2;
    case 15:
        return 3;
    case 13:
        return 4;
    case 16:
        return 5;
    case 5:
        return 6;
    case 4:
        return 7;
    case 6:
        return 8;
    case 10:
        return 9;
    case 11:
        return 10;
    case 12:
        return 11;
    default:
        *effect_value = 0;
        if (ksys::act::InfoData::instance()->hasTag(item->getName().cstr(),
                                                    ksys::act::tags::CookResult)) {
            return 0;
        }
        return 12;
    }
}

int getWeaponPowerSortValue(const PouchItem* item, ksys::act::InfoData* data) {
#ifdef MATCHING_HACK_NX_CLANG
    __builtin_assume(data);  // Force LLVM to keep data (perhaps N had an "assume not null" macro?)
#endif

    WeaponStats stats;
    getWeaponStats(*item, &stats);
    int value = stats.power;
    if (item->getType() == PouchItemType::Bow && stats.bow_add_value > 1)
        value *= stats.bow_add_value;
    return value;
}

}  // namespace

int pouchItemSortPredicate(const PouchItem* lhs, const PouchItem* rhs);
int pouchItemSortPredicateForArrow(const PouchItem* lhs, const PouchItem* rhs);

PauseMenuDataMgr::PauseMenuDataMgr() {
    mListHeads.fill(nullptr);
    for (s32 i = 0; i < NumPouch50; ++i) {
        mArray1[i] = nullptr;
        mArray2[i] = PouchItemType::Invalid;
    }
    for (auto& x : mGrabbedItems)
        x = {};
    resetEquippedItemArray();
}

PauseMenuDataMgr::~PauseMenuDataMgr() = default;

PouchItem::PouchItem() {
    mData.cook.mCookEffect0 = sDummyCookEffect0;
    for (s32 i = 0; i < NumIngredientsMax; ++i)
        mIngredients.emplaceBack();
}

void PauseMenuDataMgr::resetItem() {
    mNewlyAddedItem.mType = PouchItemType::Invalid;
    mNewlyAddedItem.mItemUse = ItemUse::Invalid;
    mNewlyAddedItem.mValue = 0;
    mNewlyAddedItem.mEquipped = false;
    mNewlyAddedItem._25 = 0;
    mNewlyAddedItem.mName.clear();
    mNewlyAddedItem.mData.cook = {};
    mNewlyAddedItem.mData.cook.mCookEffect0 = sDummyCookEffect0;
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void PauseMenuDataMgr::setItemModifier(PouchItem& item, const act::WeaponModifierInfo* modifier) {
    if (modifier && !modifier->flags.isZero()) {
        item.setWeaponAddType(modifier->flags.getDirect());
        item.setWeaponAddValue(static_cast<u32>(modifier->value));
    } else {
        item.setWeaponAddType(0);
    }
}

void PauseMenuDataMgr::init(sead::Heap* heap) {}

void PauseMenuDataMgr::initForNewSave() {
    const auto lock = sead::makeScopedLock(mCritSection);

    for (auto* item = getItems().popFront(); item; item = getItems().popFront())
        destroyAndRecycleItem(item);

    mListHeads.fill(nullptr);
    for (s32 i = 0; i < NumPouch50; ++i) {
        mArray1[i] = nullptr;
        mArray2[i] = PouchItemType::Invalid;
    }

    _44498 = {};
    ksys::gdt::setFlag_KorokNutsNum(0);
    ksys::gdt::setFlag_DungeonClearSealNum(0);
    ksys::gdt::setFlag_FairyCountCheck(false);
    _444fc = {};
    resetItemAndPointers();
    mIsPouchForQuest = false;
    for (auto& x : mGrabbedItems)
        x = {};
    _44504 = {};
    _44508 = {};
    _4450c = {};
    _44510 = {};
    _44514 = {};
    mRitoSoulItem = {};
    mGoronSoulItem = {};
    mZoraSoulItem = {};
    mGerudoSoulItem = {};
    _44538 = false;
    mEquippedWeapons.fill({});

    auto* player = ksys::act::PlayerInfo::instance()->getPlayer();
    if (player) {
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::WeaponRight), 1);
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::WeaponLeft), 1);
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::WeaponBow), 1);
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::ArmorHead), 30);
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::ArmorUpper), 30);
        player->switchEquipment(getDefaultEquipment(EquipmentSlot::ArmorLower), 30);
    }
}

void PauseMenuDataMgr::loadFromGameData() {
    doLoadFromGameData();

    for (auto& x : mGrabbedItems)
        x = {};
    resetItemAndPointers();
    _444fc = 0;
    mIsPouchForQuest = false;
    resetEquippedItemArray();

    const auto lock = sead::makeScopedLock(mCritSection);
    updateInventoryInfo(getItems());
}

void PauseMenuDataMgr::doLoadFromGameData() {
    namespace gdt = ksys::gdt;
    const auto lock = sead::makeScopedLock(mCritSection);
    auto& lists = mItemLists;

    for (auto* item = lists.list1.popFront(); item; item = lists.list1.popFront())
        destroyAndRecycleItem(item);

    mListHeads.fill(nullptr);
    mRitoSoulItem = nullptr;
    mGoronSoulItem = nullptr;
    mZoraSoulItem = nullptr;
    mGerudoSoulItem = nullptr;
    for (s32 i = 0; i < NumPouch50; ++i) {
        mArray1[i] = nullptr;
        mArray2[i] = PouchItemType::Invalid;
    }

    s32 num_food = 0;
    s32 num_swords = 0;
    s32 num_shields = 0;
    s32 num_bows = 0;
    mLastAddedItem = nullptr;
    bool found_travel_medallion = false;

    for (u32 idx = 0; idx < u32(NumPouchItemsMax); ++idx) {
        const char* item_name;
        gdt::getFlag_PorchItem(&item_name, idx);

        if (found_travel_medallion || sValues.Obj_WarpDLC == item_name)
            found_travel_medallion = true;

        if (sead::SafeString(item_name).isEmpty())
            break;

        const bool equipped = gdt::getFlag_PorchItem_EquipFlag(idx);
        const s32 value = gdt::getFlag_PorchItem_Value1(idx);
        const auto type = getType(item_name);

        switch (type) {
        case PouchItemType::Sword: {
            act::WeaponModifierInfo info{};
            info.loadPorchSwordFlag(num_swords);
            addToPouch(item_name, type, lists, value, equipped, &info, true);
            ++num_swords;
            break;
        }
        case PouchItemType::Bow: {
            act::WeaponModifierInfo info{};
            info.loadPorchBowFlag(num_bows);
            addToPouch(item_name, type, lists, value, equipped, &info, true);
            ++num_bows;
            break;
        }
        case PouchItemType::Shield: {
            act::WeaponModifierInfo info{};
            info.loadPorchShieldFlag(num_shields);
            addToPouch(item_name, type, lists, value, equipped, &info, true);
            ++num_shields;
            break;
        }
        default:
            addToPouch(item_name, type, lists, value, equipped, nullptr, true);
            break;
        }

        if (!mLastAddedItem)
            continue;

        if (type == PouchItemType::Food) {
            sead::Vector2f v{0, 0};

            gdt::getFlag_StaminaRecover(&v, num_food);
            mLastAddedItem->getCookData().setStaminaRecoverX(v.x);
            mLastAddedItem->getCookData().setStaminaRecoverY(v.y);

            gdt::getFlag_CookEffect0(&v, num_food);
            mLastAddedItem->getCookData().setCookEffect0(v);

            gdt::getFlag_CookEffect1(&v, num_food);
            mLastAddedItem->getCookData().setCookEffect1(v.x);

            gdt::getFlag_CookMaterialName0(&item_name, num_food);
            mLastAddedItem->setIngredient(0, item_name);

            gdt::getFlag_CookMaterialName1(&item_name, num_food);
            mLastAddedItem->setIngredient(1, item_name);

            gdt::getFlag_CookMaterialName2(&item_name, num_food);
            mLastAddedItem->setIngredient(2, item_name);

            gdt::getFlag_CookMaterialName3(&item_name, num_food);
            mLastAddedItem->setIngredient(3, item_name);

            gdt::getFlag_CookMaterialName4(&item_name, num_food);
            mLastAddedItem->setIngredient(4, item_name);

            ++num_food;

        } else if (type == PouchItemType::Sword &&
                   isMasterSwordActorName(mLastAddedItem->getName()) &&
                   gdt::getFlag_MasterSwordRecoverTime() <= sead::Mathf::epsilon() &&
                   mLastAddedItem->getValue() <= 0) {
            const s32 new_value = getWeaponInventoryLife(mLastAddedItem->getName());
            mLastAddedItem->mValue = new_value;
            gdt::setFlag_PorchItem_Value1(new_value, idx);
        }
    }

    // Add the Travel Medallion (Obj_WarpDLC) to the inventory if it is missing for some reason
    if (aoc::Manager::instance()->hasAoc2() &&
        !(found_travel_medallion | !gdt::getFlag_IsGet_Obj_WarpDLC())) {
        addToPouch(sValues.Obj_WarpDLC.cstr(), PouchItemType::KeyItem, lists, 1, false, nullptr,
                   true);
    }

    // Add missing champion powers and fix some divine beast related flags
    // in case something went wrong with the "divine beast cleared" cutscenes
    bool was_missing_hero_soul = false;
    s32 num_cleared_beasts = 0;

    if (gdt::getFlag_Clear_RemainsWind()) {
        ++num_cleared_beasts;
        if (!mRitoSoulItem) {
            was_missing_hero_soul = true;
            addToPouch(sValues.Obj_HeroSoul_Rito.cstr(), PouchItemType::KeyItem, lists, 1, true,
                       nullptr, true);
            gdt::setFlag_IsPlayed_Demo119_0(true);
        }
    }

    if (gdt::getFlag_Clear_RemainsFire()) {
        ++num_cleared_beasts;
        if (!mGoronSoulItem) {
            was_missing_hero_soul = true;
            addToPouch(sValues.Obj_HeroSoul_Goron.cstr(), PouchItemType::KeyItem, lists, 1, true,
                       nullptr, true);
            gdt::setFlag_IsPlayed_Demo116_0(true);
        }
    }

    if (gdt::getFlag_Clear_RemainsWater()) {
        ++num_cleared_beasts;
        if (!mZoraSoulItem) {
            was_missing_hero_soul = true;
            addToPouch(sValues.Obj_HeroSoul_Zora.cstr(), PouchItemType::KeyItem, lists, 1, true,
                       nullptr, true);
            gdt::setFlag_IsPlayed_Demo122_0(true);
        }
    }

    if (gdt::getFlag_Clear_RemainsElectric()) {
        ++num_cleared_beasts;
        if (!mGerudoSoulItem) {
            was_missing_hero_soul = true;
            addToPouch(sValues.Obj_HeroSoul_Gerudo.cstr(), PouchItemType::KeyItem, lists, 1, true,
                       nullptr, true);
            gdt::setFlag_IsPlayed_Demo125_0(true);
        }
    }

    if (was_missing_hero_soul)
        updateDivineBeastClearFlags(num_cleared_beasts);

    _44490 = -1;
    _44494 = -1;
}

bool PauseMenuDataMgr::cannotGetItem(const sead::SafeString& name, int n) const {
    namespace act = ksys::act;

    al::ByamlIter iter;
    if (!act::InfoData::instance()->getActorIter(&iter, name.cstr()))
        return true;

    if (!act::InfoData::instance()->hasTag(iter, act::tags::CanGetPouch))
        return true;

    if (act::InfoData::instance()->getSortKey(name.cstr()) == 99999)
        return true;

    const auto lock = sead::makeScopedLock(mCritSection);
    const auto type = getType(name);

    if (act::InfoData::instance()->hasTag(iter, act::tags::CanStack))
        return !hasFreeSpaceForItem(mItemLists, name, n);

    if (type <= PouchItemType::Shield) {
        switch (type) {
        case PouchItemType::Sword: {
            const auto limit = ksys::gdt::getFlag_WeaponPorchStockNum();
            return isList2Empty() || limit < countItems(PouchItemType::Sword) + n;
        }
        case PouchItemType::Shield: {
            const auto limit = ksys::gdt::getFlag_ShieldPorchStockNum();
            return isList2Empty() || limit < countItems(PouchItemType::Shield) + n;
        }
        case PouchItemType::Bow: {
            const auto limit = ksys::gdt::getFlag_BowPorchStockNum();
            return isList2Empty() || limit < countItems(PouchItemType::Bow) + n;
        }
        default: {
            const auto limit = ksys::gdt::getFlag_WeaponPorchStockNum();
            return isList2Empty() || limit < countItems(PouchItemType::Sword, true) + n;
        }
        }
    }

    if (type == PouchItemType::Food)
        return isList2Empty() || countItems(PouchItemType::Food, true) + n > NumFoodMax;

    if (type == PouchItemType::Material)
        return isList2Empty() || countItems(PouchItemType::Material) + n > NumMaterialsMax;

    if (type == PouchItemType::KeyItem)
        return isList2Empty() || countItems(PouchItemType::KeyItem) + n > NumKeyItemsMax;

    return isList2Empty() || countItems(PouchItemType::ArmorHead) + n > NumArmorsMax;
}

PouchItemType PauseMenuDataMgr::getType(const sead::SafeString& item, al::ByamlIter* iter) {
    sead::SafeString group;
    getSameGroupActorName(&group, item, iter);

    al::ByamlIter actor_iter;
    if (iter && iter->isValid() && group == item) {
        actor_iter = *iter;
    } else {
        if (!ksys::act::InfoData::instance()->getActorIter(&actor_iter, group.cstr()))
            return PouchItemType::Invalid;
    }

    if (ksys::act::InfoData::instance()->hasTag(actor_iter, ksys::act::tags::Arrow))
        return PouchItemType::Arrow;

    const char* profile_c;
    if (!ksys::act::InfoData::instance()->getActorProfile(&profile_c, actor_iter))
        return PouchItemType::Invalid;

    const sead::SafeString profile = profile_c;

    if (profile == sValues.WeaponSmallSword)
        return PouchItemType::Sword;
    if (profile == sValues.WeaponLargeSword)
        return PouchItemType::Sword;
    if (profile == sValues.WeaponSpear)
        return PouchItemType::Sword;

    if (profile == sValues.WeaponBow)
        return PouchItemType::Bow;

    if (profile == sValues.WeaponShield)
        return PouchItemType::Shield;

    if (profile == sValues.ArmorHead)
        return PouchItemType::ArmorHead;
    if (profile == sValues.ArmorUpper)
        return PouchItemType::ArmorUpper;
    if (profile == sValues.ArmorLower)
        return PouchItemType::ArmorLower;

    if (profile == sValues.HorseReins)
        return PouchItemType::KeyItem;

    if (ksys::act::InfoData::instance()->hasTag(actor_iter, ksys::act::tags::CookResult))
        return PouchItemType::Food;
    if (ksys::act::InfoData::instance()->hasTag(actor_iter, ksys::act::tags::RoastItem))
        return PouchItemType::Food;

    if (ksys::act::InfoData::instance()->hasTag(actor_iter, ksys::act::tags::Important))
        return PouchItemType::KeyItem;

    return PouchItemType::Material;
}

bool PauseMenuDataMgr::hasFreeSpaceForItem(const PauseMenuDataMgr::Lists& lists,
                                           const sead::SafeString& name, int n) const {
    sead::SafeString group_name;
    getSameGroupActorName(&group_name, name);

    const int count = getItemCount(group_name);
    const bool is_arrow =
        ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::Arrow);

    if (count == 0 && is_arrow) {
        for (const auto& item : lists.list1) {
            if (item.getType() == PouchItemType::Arrow && group_name == item.getName())
                return true;
        }

        return countItems(PouchItemType::Arrow) < NumArrowItemsMax;
    }

    if (count == 0) {
        const auto type = getType(name);

        if (type == PouchItemType::Food)
            return !lists.list2.isEmpty() && countItems(PouchItemType::Food, true) < NumFoodMax;

        if (type == PouchItemType::Material)
            return !lists.list2.isEmpty() && countItems(PouchItemType::Material) < NumMaterialsMax;

        if (type == PouchItemType::KeyItem)
            return !lists.list2.isEmpty() && countItems(PouchItemType::KeyItem) < NumKeyItemsMax;

        return false;
    }

    return count + n <= ItemStackSizeMax;
}

int PauseMenuDataMgr::countItems(PouchItemType type, bool count_any_weapon) const {
    if (isPouchItemInvalid(type) || getItems().isEmpty())
        return 0;

    const auto& list = getItems();

    if (count_any_weapon) {
        PouchItem** head = nullptr;

        if (type <= PouchItemType::Shield) {
            int count = 0;
            for (auto* item = list.nth(0); item && item->getType() <= PouchItemType::Shield;
                 item = list.next(item)) {
                count += item->get25();
            }
            return count;

        } else if (type <= PouchItemType::ArmorLower) {
            int count = 0;
            for (auto* item = getItemHead(PouchCategory::Armor);
                 item && item->getType() <= PouchItemType::ArmorLower; item = list.next(item)) {
                count += item->get25();
            }
            return count;

        } else if (type == PouchItemType::Material) {
            head = getItemHeadp(PouchCategory::Material);
            if (!head)
                return 0;

        } else if (type == PouchItemType::Food) {
            head = getItemHeadp(PouchCategory::Food);
            if (!head)
                return 0;

        } else if (type == PouchItemType::KeyItem) {
            head = getItemHeadp(PouchCategory::KeyItem);
            if (!head)
                return 0;

        } else {
            return 0;
        }

        if (!head)
            return 0;

        int count = 0;
        for (auto* item = *head; item && item->getType() == type; item = list.next(item)) {
            count += item->get25();
        }
        return count;
    }

    PouchItem* first = nullptr;

    if (type == PouchItemType::Sword) {
        first = getItemHead(PouchCategory::Sword);

    } else if (type == PouchItemType::Bow) {
        first = getItemHead(PouchCategory::Bow);

    } else if (type == PouchItemType::Arrow) {
        for (auto* item = getItemHead(PouchCategory::Bow);
             item && item->getType() <= PouchItemType::Arrow; item = list.next(item)) {
            if (item->getType() == PouchItemType::Arrow) {
                first = item;
                break;
            }
        }

    } else if (type == PouchItemType::Shield) {
        first = getItemHead(PouchCategory::Shield);

    } else if (type <= PouchItemType::ArmorLower) {
        int count = 0;
        for (auto* item = getItemHead(PouchCategory::Armor);
             item && item->getType() <= PouchItemType::ArmorLower; item = list.next(item)) {
            count += item->get25();
        }
        return count;

    } else if (type == PouchItemType::Material) {
        first = getItemHead(PouchCategory::Material);

    } else if (type == PouchItemType::Food) {
        first = getItemHead(PouchCategory::Food);

    } else if (type == PouchItemType::KeyItem) {
        first = getItemHead(PouchCategory::KeyItem);

    } else {
        return 0;
    }

    int count = 0;
    for (auto* item = first; item && item->getType() == type; item = list.next(item)) {
        count += item->get25();
    }
    return count;
}

bool PauseMenuDataMgr::isWeaponSectionFull(const sead::SafeString& weapon_type) const {
    const auto lock = sead::makeScopedLock(mCritSection);

    const auto check = [this](auto get_flag, PouchCategory category, PouchItemType type) {
        const s32 num_slots = get_flag(false);
        if (mItemLists.list2.isEmpty())
            return true;

        s32 num = 0;
        if (!getItems().isEmpty()) {
            for (auto item = getItemHead(category); item; item = nextItem(item)) {
                if (item->getType() != type)
                    break;
                num += item->_25;
            }
        }

        return num_slots <= num;
    };

    if (weapon_type == sValues.WeaponSmallSword || weapon_type == sValues.WeaponLargeSword ||
        weapon_type == sValues.WeaponSpear) {
        return check(ksys::gdt::getFlag_WeaponPorchStockNum, PouchCategory::Sword,
                     PouchItemType::Sword);
    }

    if (weapon_type == sValues.WeaponBow) {
        return check(ksys::gdt::getFlag_BowPorchStockNum, PouchCategory::Bow, PouchItemType::Bow);
    }

    if (weapon_type == sValues.WeaponShield) {
        return check(ksys::gdt::getFlag_ShieldPorchStockNum, PouchCategory::Shield,
                     PouchItemType::Shield);
    }

    return false;
}

void PauseMenuDataMgr::itemGet(const sead::SafeString& name, int value,
                               const act::WeaponModifierInfo* modifier) {
    if (name.include("Default") || name.include("Extra"))
        return;

    const auto type = getType(name);

    mNewlyAddedItem.mType = type;
    mNewlyAddedItem.mValue = value;
    mNewlyAddedItem._25 = 1;
    mNewlyAddedItem.mName = name;
    mNewlyAddedItem.mEquipped = false;

    if (modifier) {
        setItemModifier(mNewlyAddedItem, modifier);
        const auto add_type = modifier->flags.getDirect();
        const auto add_value = mNewlyAddedItem.getWeaponAddValue();
        sValues.last_added_weapon_add_type = add_type;
        sValues.last_added_weapon_add_value = add_value;
    }

    const auto lock = sead::makeScopedLock(mCritSection);
    auto& lists = mItemLists;
    ksys::PlayReportMgr::instance()->reportDebug("PouchGet", name);
    addToPouch(name, type, lists, value, false, modifier);
    saveToGameData(lists.list1);
}

void PauseMenuDataMgr::updateAfterAddingItem(bool only_sort) {
    const auto lock = sead::makeScopedLock(mCritSection);

    if (getItems().isEmpty())
        return;

    mCategoryToSort = PouchCategory::Invalid;
    auto& items = getItems();
    items.sort(pouchItemSortPredicateForArrow);
    if (!only_sort) {
        updateInventoryInfo(items);
        updateListHeads();
        saveToGameData(items);
    }
}

void PauseMenuDataMgr::updateListHeads() {
    for (s32 i = 0; i < mListHeads.size(); ++i)
        mListHeads[i] = nullptr;

    const auto set_if_null = [&](PouchCategory cat, s32 i) {
        if (!mListHeads[s32(cat)])
            mListHeads[s32(cat)] = &mArray1[i];
    };

    for (s32 i = 0; i < NumPouch50; ++i) {
        if (mArray2[i] == PouchItemType::Invalid)
            continue;

        switch (mArray2[i]) {
        case PouchItemType::Sword:
            set_if_null(PouchCategory::Sword, i);
            break;
        case PouchItemType::Bow:
        case PouchItemType::Arrow:
            set_if_null(PouchCategory::Bow, i);
            break;
        case PouchItemType::Shield:
            set_if_null(PouchCategory::Shield, i);
            break;
        case PouchItemType::ArmorHead:
        case PouchItemType::ArmorUpper:
        case PouchItemType::ArmorLower:
            set_if_null(PouchCategory::Armor, i);
            break;
        case PouchItemType::Material:
            set_if_null(PouchCategory::Material, i);
            break;
        case PouchItemType::Food:
            set_if_null(PouchCategory::Food, i);
            break;
        case PouchItemType::KeyItem:
            set_if_null(PouchCategory::KeyItem, i);
            break;
        case PouchItemType::Invalid:
            break;
        }
    }
}

void PauseMenuDataMgr::addToPouch(const sead::SafeString& name, PouchItemType type, Lists& lists,
                                  int value, bool equipped, const act::WeaponModifierInfo* modifier,
                                  bool is_inventory_load) {
    if (ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::CanGetCollectSet))
        return;

    if (type == PouchItemType::KeyItem) {
        // If this is a key item and duplicates are not allowed, we need to check
        // whether the item is already in the inventory. If it is, do not add it again.
        if (!ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::CanStack)) {
            for (auto* item = getItemHead(PouchCategory::KeyItem);
                 item && item->getType() == PouchItemType::KeyItem; item = lists.list1.next(item)) {
                if (item->get25() && item->getName() == name)
                    return;
            }
        }

    } else if (type == PouchItemType::Sword && isMasterSwordActorName(name)) {
        // Duplicates are not allowed for the Master Sword.
        // Adding a second Master Sword should just refresh the item value or equipped status.
        for (auto* item = getItemHead(PouchCategory::Sword);
             item && item->getType() == PouchItemType::Sword; item = lists.list1.next(item)) {
            if (!item->get25() || item->getName() != name)
                continue;

            if (ksys::gdt::getFlag_MasterSwordRecoverTime() <= sead::Mathf::epsilon()) {
                if (item->getValue() <= 0)
                    item->mValue = value;
            } else {
                item->mValue = 0;
                item->mEquipped = false;
            }

            mLastAddedItem = item->mValue > 0 ? item : nullptr;
            resetItem();
            return;
        }
    }

    if (type != PouchItemType::Invalid) {
        doAddToPouch(type, name, lists, value, equipped, modifier, is_inventory_load);

        updateAfterAddingItem(true);
        updateInventoryInfo(lists.list1);
        updateListHeads();

        if (name == sValues.Obj_KorokNuts)
            ksys::gdt::setFlag_KorokNutsNum(getItemCount(name));
        else if (name == sValues.Obj_DungeonClearSeal)
            ksys::gdt::setFlag_DungeonClearSealNum(getItemCount(name));
    }

    sead::SafeString same_group_actor_name;
    ksys::act::getSameGroupActorName(&same_group_actor_name, name);
    ksys::gdt::setIsGetItem(same_group_actor_name, true);
    ksys::gdt::setIsGetItem2(same_group_actor_name, true);
}

void PauseMenuDataMgr::saveToGameData(const sead::OffsetList<PouchItem>& list) const {
    if (mIsPouchForQuest)
        return;

    auto* item = list.size() > 0 ? list.nth(0) : nullptr;
    s32 num_food = 0;
    s32 idx = 0;
    s32 num_swords = 0;
    s32 num_shields = 0;
    s32 num_bows = 0;

    for (idx = 0; idx < NumPouchItemsMax; ++idx) {
        if (!item) {
            ksys::gdt::setFlag_PorchItem({}, idx);
            ksys::gdt::setFlag_PorchItem_EquipFlag(false, idx);
            ksys::gdt::setFlag_PorchItem_Value1(0, idx);
            continue;
        }

        while (item && !item->get25()) {
#ifdef MATCHING_HACK_NX_CLANG
            asm("");  // Prevent list.mOffset from being loaded too early
#endif
            item = list.next(item);
        }

        if (!item) {
            ksys::gdt::setFlag_PorchItem({}, idx);
            ksys::gdt::setFlag_PorchItem_EquipFlag(false, idx);
            ksys::gdt::setFlag_PorchItem_Value1(0, idx);
            return;
        }

        sead::FixedSafeString<64> name{item->getName()};
        s32 value = item->getValue();
        for (const auto& entry : mGrabbedItems) {
            if (entry.item == item) {
                value +=
                    ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::CanStack);
            }
        }
        const auto type = item->getType();
        ksys::gdt::setFlag_PorchItem(name, idx);
        ksys::gdt::setFlag_PorchItem_EquipFlag(item->isEquipped(), idx);
        ksys::gdt::setFlag_PorchItem_Value1(value, idx);
        switch (type) {
        case PouchItemType::Sword:
            if (num_swords < NumSwordsMax) {
                act::WeaponModifierInfo(*item).savePorchSwordFlag(num_swords);
                ++num_swords;
            }
            break;
        case PouchItemType::Bow:
            if (num_bows < NumBowsMax) {
                act::WeaponModifierInfo(*item).savePorchBowFlag(num_bows);
                ++num_bows;
            }
            break;
        case PouchItemType::Arrow:
            break;
        case PouchItemType::Shield:
            if (num_shields < NumShieldsMax) {
                act::WeaponModifierInfo(*item).savePorchShieldFlag(num_shields);
                ++num_shields;
            }
            break;
        case PouchItemType::ArmorHead:
        case PouchItemType::ArmorUpper:
        case PouchItemType::ArmorLower:
        case PouchItemType::Material:
            break;
        case PouchItemType::Food:
            if (num_food >= NumFoodMax)
                break;

            ksys::gdt::setFlag_StaminaRecover(
                {static_cast<f32>(item->getCookData().mStaminaRecoverX),
                 static_cast<f32>(item->getCookData().mStaminaRecoverY) * 30.0f / 30.0f},
                num_food);
            ksys::gdt::setFlag_CookEffect0(item->getCookData().mCookEffect0, num_food);
            ksys::gdt::setFlag_CookEffect1({f32(item->getCookData().mCookEffect1), 0.0}, num_food);
            ksys::gdt::setFlag_CookMaterialName0(item->getIngredient(0), num_food);
            ksys::gdt::setFlag_CookMaterialName1(item->getIngredient(1), num_food);
            ksys::gdt::setFlag_CookMaterialName2(item->getIngredient(2), num_food);
            ksys::gdt::setFlag_CookMaterialName3(item->getIngredient(3), num_food);
            ksys::gdt::setFlag_CookMaterialName4(item->getIngredient(4), num_food);
            ++num_food;
            break;
        default:
            break;
        }

        item = list.next(item);
    }
}

void PauseMenuDataMgr::cookItemGet(const ksys::CookItem& cook_item) {
    const auto* info = ksys::act::InfoData::instance();
    if (!info->hasTag(cook_item.name.cstr(), ksys::act::tags::CookResult))
        return;

    const auto lock = sead::makeScopedLock(mCritSection);
    auto& lists = mItemLists;

    ksys::PlayReportMgr::instance()->reportDebug("PouchGet", cook_item.name);
    const auto type = getType(cook_item.name);
    addToPouch(cook_item.name, type, lists, 1, false);
    setCookDataOnLastAddedItem(cook_item);
    saveToGameData(lists.list1);
}

void PauseMenuDataMgr::setCookDataOnLastAddedItem(const ksys::CookItem& cook_item) {
    if (!mLastAddedItem)
        return;

    mLastAddedItem->getCookData().setStaminaRecoverY(cook_item.stamina_recover_y);
    mLastAddedItem->getCookData().setStaminaRecoverX(cook_item.stamina_recover_x);
    mLastAddedItem->getCookData().setCookEffect1(cook_item.cook_effect_1);
    const int y = cook_item.cook_effect_0_y;
    const int x = cook_item.cook_effect_0_x;
    mLastAddedItem->getCookData().setCookEffect0({float(x), float(y)});
    for (s32 i = 0; i < cook_item.ingredients.size(); ++i)
        mLastAddedItem->setIngredient(i, cook_item.ingredients[i]);
    mLastAddedItem->sortIngredients();
}

void PauseMenuDataMgr::autoEquipLastAddedItem() {
    if (mLastAddedItem && mLastAddedItem->getType() <= PouchItemType::ArmorLower) {
        const auto lock = sead::makeScopedLock(mCritSection);
        autoEquip(mLastAddedItem, getItems());
    }
}

// NON_MATCHING: branching
const sead::SafeString& PauseMenuDataMgr::autoEquip(PouchItem* item,
                                                    const sead::OffsetList<PouchItem>& list) {
    const auto type = item->getType();
    if (type == PouchItemType::KeyItem)
        item->mEquipped = true;

    if (type >= PouchItemType::Material)
        return sead::SafeString::cEmptyString;

    if (isPouchItemArmor(type)) {
        for (auto& other : list) {
            if (other.getType() > PouchItemType::ArmorLower)
                break;
            if (other.getType() == type)
                other.mEquipped = false;
        }
    } else if (isPouchItemWeapon(type)) {
        for (auto& other : list) {
            if (other.getType() > PouchItemType::Shield)
                break;
            if (other.getType() == type)
                other.mEquipped = false;
        }
    }

    item->mEquipped = true;
    updateInventoryInfo(list);
    saveToGameData(list);
    return sead::SafeString::cEmptyString;
}

// NON_MATCHING: harmless reordering
void PauseMenuDataMgr::unequipAll(PouchItemType type) {
    const auto lock = sead::makeScopedLock(mCritSection);

    if (type == PouchItemType::Arrow)
        return;

    for (auto& item : getItems()) {
        if (type == PouchItemType::Invalid) {
            if (item.getType() > PouchItemType::ArmorLower)
                break;
            if (item.isEquipped() && item.getType() != PouchItemType::Arrow)
                item.mEquipped = false;

        } else {
            if (item.getType() > PouchItemType::ArmorLower)
                break;
            if (item.isEquipped() && item.getType() == type) {
                item.mEquipped = false;
                break;
            }
        }
    }
}

KSYS_ALWAYS_INLINE inline void
PauseMenuDataMgr::deleteItem_(const sead::OffsetList<PouchItem>& list, PouchItem* item,
                              const sead::SafeString& name) {
    destroyAndRecycleItem(mItemLists, item);
    ksys::PlayReportMgr::instance()->reportDebug("PouchDelete", name);
    saveToGameData(list);
    updateInventoryInfo(list);
    updateListHeads();
}

void PauseMenuDataMgr::removeItem(const sead::SafeString& name) {
    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    PouchItem* item = nullptr;
    for (auto& it : items) {
        if (name == it.getName() && !it.isEquipped()) {
            item = &it;
            break;
        }
    }

    if (!item)
        return;

    // If the item is stackable, just remove one copy of the item if possible.
    auto* info = ksys::act::InfoData::instance();
    if (info->hasTag(item->getName().cstr(), ksys::act::tags::CanStack) && item->getValue() > 1) {
        item->mValue -= 1;
        ksys::PlayReportMgr::instance()->reportDebug("PouchDelete", name);
        updateInventoryInfo(items);
        updateListHeads();
        saveToGameData(items);
        return;
    }

    // Otherwise, delete the PouchItem entirely.
    deleteItem_(items, item, name);
}

void PauseMenuDataMgr::removeWeaponIfEquipped(const sead::SafeString& name) {
    const auto lock = sead::makeScopedLock(mCritSection);
    if (!ksys::act::PlayerInfo::instance()->getPlayer())
        return;

    const auto& items = getItems();

    PouchItem* item = nullptr;
    for (auto& it : items) {
        if (name == it.getName() && it.isEquipped()) {
            item = &it;
            break;
        }
    }

    if (item)
        deleteItem_(items, item, name);
}

void PauseMenuDataMgr::removeArrow(const sead::SafeString& arrow_name, int count) {
    if (!ksys::act::InfoData::instance()->hasTag(arrow_name.cstr(), ksys::act::tags::Arrow))
        return;

    const auto lock = sead::makeScopedLock(mCritSection);
    s32 idx = 0;
    for (auto& item : getItems()) {
        if (arrow_name == item.getName()) {
            if (count < item.getCount()) {
                item.mValue -= count;
                break;
            }

            count -= item.getCount();
            item.mValue = 0;
        }
        ++idx;
    }

    const auto num = getItemCount(arrow_name);
    if (!mIsPouchForQuest && idx >= 0)
        ksys::gdt::setFlag_PorchItem_Value1(num, idx);
}

// NON_MATCHING: branch merging -- but this is pretty clearly equivalent
int PauseMenuDataMgr::getItemCount(const sead::SafeString& name, bool count_equipped) const {
    const auto type = getType(name);
    if (isPouchItemInvalid(type))
        return 0;

    const auto& items = getItems();
    sead::SafeString group_name;
    getSameGroupActorName(&group_name, name);

    PouchItem* first = nullptr;
    switch (type) {
    case PouchItemType::Sword:
        first = getItemHead(PouchCategory::Sword);
        break;
    case PouchItemType::Bow:
        first = getItemHead(PouchCategory::Bow);
        break;
    case PouchItemType::Arrow:
        for (auto* item = getItemHead(PouchCategory::Bow); item; item = items.next(item)) {
            if (item->getType() > PouchItemType::Arrow)
                break;
            if (item->getType() == PouchItemType::Arrow) {
                first = item;
                break;
            }
        }
        break;
    case PouchItemType::Shield:
        first = getItemHead(PouchCategory::Shield);
        break;
    case PouchItemType::Food:
        first = getItemHead(PouchCategory::Food);
        break;
    case PouchItemType::KeyItem:
        first = getItemHead(PouchCategory::KeyItem);
        break;
    default:
        if (type > PouchItemType::Material)
            first = getItemHead(PouchCategory::Material);
        else
            first = getItemHead(PouchCategory::Armor);
        break;
    }

    if (ksys::act::InfoData::instance()->hasTag(group_name.cstr(), ksys::act::tags::CanStack)) {
        for (auto* item = first; item; item = items.next(item)) {
            if (group_name == item->getName())
                return item->getValue();
        }
        return 0;
    }

    s32 count = 0;
    if (count_equipped) {
        for (auto* item = first; item; item = items.next(item)) {
            if (group_name == item->getName())
                count += item->get25();
        }
    } else {
        for (auto* item = first; item; item = items.next(item)) {
            if (group_name == item->getName() && item->get25())
                count += !item->isEquipped();
        }
    }
    return count;
}

void PauseMenuDataMgr::setEquippedWeaponItemValue(s32 value, PouchItemType type) {
    if (isPouchItemNotWeapon(type))
        return;

    const auto lock = sead::makeScopedLock(mCritSection);

    s32 idx = 0;
    for (auto& item : getItems()) {
        if (!item.isEquipped() || item.getType() != type) {
            ++idx;
            continue;
        }

        item.mValue = value;
        if (idx >= 0 && !mIsPouchForQuest)
            ksys::gdt::setFlag_PorchItem_Value1(value, idx);

        return;
    }
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
const sead::SafeString& PauseMenuDataMgr::getDefaultEquipment(EquipmentSlot idx) const {
    if (idx != EquipmentSlot::WeaponArrow &&
        u32(idx) < u32(sValues.default_equipment_names.size())) {
        return sValues.default_equipment_names(u32(idx));
    }
    return sead::SafeString::cEmptyString;
}

bool PauseMenuDataMgr::hasItem(const sead::SafeString& name) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    bool ret = false;
    for (auto& item : getItems()) {
        if (name != item.getName())
            continue;

        if (ksys::act::InfoData::instance()->hasTag(name.cstr(), ksys::act::tags::CanStack))
            ret = item.getValue() > 0;
        else
            ret = true;
        break;
    }
    return ret;
}

PouchItem* PauseMenuDataMgr::getMasterSword() const {
    const auto lock = sead::makeScopedLock(mCritSection);

    for (auto* item = getItemHead(PouchCategory::Sword); item; item = nextItem(item)) {
        if (item->getType() != PouchItemType::Sword)
            return nullptr;
        if (item->_25 && item->getName() == "Weapon_Sword_070")
            return item;
    }

    return nullptr;
}

void PauseMenuDataMgr::removeGrabbedItems() {
    const auto lock = sead::makeScopedLock(mCritSection);
    for (s32 i = 0, n = mGrabbedItems.size(); i < n; ++i) {
        auto& entry = mGrabbedItems[i];
        auto* item = entry.item;
        if (item && item->getValue() == 0 && !entry._9)
            destroyAndRecycleItem(mItemLists, item);
        entry = {};
    }

    const auto& items = getItems();
    mLastAddedItem = nullptr;
    updateInventoryInfo(items);
    updateListHeads();
    saveToGameData(items);
}

// NON_MATCHING: mostly branching (which leads to other differences), but visibly equivalent
bool PauseMenuDataMgr::addGrabbedItem(ksys::act::BaseProcLink* link) {
    if (!link || !link->hasProc())
        return false;

    ksys::act::ActorConstDataAccess accessor;
    ksys::act::acquireActor(link, &accessor);
    const auto name = accessor.getName();
    auto& cs = mCritSection;
    const auto& items = getItems();
    bool found = false;

    for (s32 i = 0; i < NumGrabbableItems; ++i) {
        auto& entry = mGrabbedItems[i];
        if (found) {
            mGrabbedItems[i - 1].item = entry.item;
            mGrabbedItems[i - 1]._8 = entry._8;
            mGrabbedItems[i - 1]._9 = entry._9;
            continue;
        }

        if (!entry.item || name != entry.item->getName())
            continue;

        if (entry.item->getValue() == 0 && !entry._9) {
            const auto lock = sead::makeScopedLock(cs);
            auto* item = entry.item;
            destroyAndRecycleItem(mItemLists, item);
            updateInventoryInfo(items);
            updateListHeads();
            saveToGameData(items);
            mLastAddedItem = nullptr;
        }

        found = true;
        entry = {};
    }
    mGrabbedItems[4] = {};
    return found;
}

bool PauseMenuDataMgr::getEquippedArrowType(sead::BufferedSafeString* name, int* count) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    for (const auto* item = getItemHead(PouchCategory::Bow); item; item = nextItem(item)) {
        if (item->getType() > PouchItemType::Arrow)
            break;
        if (item->getType() == PouchItemType::Arrow && item->get25() && item->isEquipped()) {
            if (name)
                name->copy(item->getName());
            if (count)
                *count = item->getValue();
            return true;
        }
    }
    return false;
}

int PauseMenuDataMgr::getArrowCount(const sead::SafeString& name) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    for (auto item = getItemHead(PouchCategory::Bow); item; item = nextItem(item)) {
        if (item->getType() > PouchItemType::Arrow)
            break;
        if (item->getType() == PouchItemType::Arrow && item->_25 && item->getName() == name)
            return item->getCount();
    }
    return 0;
}

int PauseMenuDataMgr::getRealArrowCount(const sead::SafeString& name) const {
    if (!mIsPouchForQuest)
        return getArrowCount(name);

    s32 count;
    s32 status = 2;
    for (u32 i = 0; i < u32(NumPouchItemsMax); ++i) {
        const char* item_name;
        ksys::gdt::getFlag_PorchItem(&item_name, i);
        if (sead::SafeString(item_name).isEmpty())
            break;
        if (sead::SafeString(item_name) == name) {
            count = ksys::gdt::getFlag_PorchItem_Value1(i);
            status = 1;
            break;
        }
    }
    return status == 2 ? 0 : count;
}

void PauseMenuDataMgr::breakMasterSword() {
    const auto lock = sead::makeScopedLock(mCritSection);
    s32 idx = 0;
    for (auto& item : getItems()) {
        if (item.getType() == PouchItemType::Sword && isMasterSwordActorName(item.getName())) {
            item.mValue = 0;
            item.mEquipped = false;
            if (!mIsPouchForQuest && idx >= 0) {
                ksys::gdt::setFlag_PorchItem_Value1(0, idx);
                ksys::gdt::setFlag_PorchItem_EquipFlag(false, idx);
            }
            break;
        }
        ++idx;
    }
}

void PauseMenuDataMgr::restoreMasterSword(bool only_if_broken) {
    const auto lock = sead::makeScopedLock(mCritSection);
    s32 idx = 0;
    for (auto& item : getItems()) {
        if (item.getType() == PouchItemType::Sword && isMasterSwordActorName(item.getName())) {
            if (only_if_broken && item.getValue() > 0)
                break;

            item.mValue = getWeaponInventoryLife(item.getName());
            if (!mIsPouchForQuest && idx >= 0)
                ksys::gdt::setFlag_PorchItem_Value1(item.mValue, idx);

            break;
        }
        ++idx;
    }
}

static s32 checkItemRemoval(const sead::OffsetList<PouchItem>& items, const sead::SafeString& name,
                            int num_to_remove, bool include_equipped_items, bool stackable) {
    s32 total = 0;
    for (const auto& item : items) {
        if (name == item.getName() && (stackable || include_equipped_items || !item.isEquipped())) {
            total += stackable ? item.getValue() : 1;
            if (total >= num_to_remove)
                return true;
        }
    }
    return false;
}

bool PauseMenuDataMgr::checkAddOrRemoveItem(const sead::SafeString& name, int count,
                                            bool include_equipped_items) const {
    const auto lock = sead::makeScopedLock(mCritSection);

    static_cast<void>(getType(name));
    if (count < 0) {
        const auto* info = ksys::act::InfoData::instance();
        const int num_to_remove = -count;
        const auto& items = getItems();
        if (!info->hasTag(name.cstr(), ksys::act::tags::CanStack))
            return checkItemRemoval(items, name, num_to_remove, include_equipped_items, false);
        return checkItemRemoval(items, name, num_to_remove, true, true);
    }

    return !cannotGetItem(name, count);
}

int PauseMenuDataMgr::getFreeSlotCount() const {
    const auto lock = sead::makeScopedLock(mCritSection);

    const s32 num_items = getItems().size();
    const s32 num_weapons = countItems(PouchItemType::Sword, true);
    const s32 num_food = countItems(PouchItemType::Food);

    return NumArmorsMax + NumMaterialsMax + NumKeyItemsMax - num_items + num_weapons + num_food;
}

int PauseMenuDataMgr::calculateEnemyMaterialMamo() const {
    const auto lock = sead::makeScopedLock(mCritSection);
    int value = 0;
    for (const auto& item : getItems()) {
        al::ByamlIter iter;
        if (ksys::act::InfoData::instance()->getActorIter(&iter, item.getName().cstr()) &&
            ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::EnemyMaterial)) {
            value += ksys::act::getMonsterShopSellMamo(iter) * item.getValue();
        }
    }
    return value;
}

void PauseMenuDataMgr::removeAllEnemyMaterials() {
    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    // Materials cannot be removed from the linked list immediately as we need to traverse it
    // at the same time. Instead, only remove a material *after* we have moved to the next item.
    PouchItem* material_to_remove = nullptr;
    for (auto& item : items) {
        if (material_to_remove != nullptr) {
            getItems().erase(material_to_remove);
            destroyAndRecycleItem(material_to_remove);
        }

        auto* info = ksys::act::InfoData::instance();
        material_to_remove =
            info->hasTag(item.getName().cstr(), ksys::act::tags::EnemyMaterial) ? &item : nullptr;
    }

    if (material_to_remove)
        destroyAndRecycleItem(mItemLists, material_to_remove);

    saveToGameData(items);
    updateInventoryInfo(items);
    updateListHeads();
}

int PauseMenuDataMgr::countItemsWithProfile(const sead::SafeString& profile,
                                            bool count_stacked_items) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    s32 count = 0;
    for (const auto& item : getItems()) {
        const char* item_profile;
        al::ByamlIter iter;
        if (ksys::act::InfoData::instance()->getActorIter(&iter, item.getName().cstr()) &&
            ksys::act::InfoData::instance()->getActorProfile(&item_profile, iter) &&
            profile == item_profile) {
            if (count_stacked_items &&
                ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::CanStack)) {
                count += item.getValue();
            } else {
                count += 1;
            }
        }
    }
    return count;
}

int PauseMenuDataMgr::countItemsWithTag(u32 tag, bool count_stacked_items) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    s32 count = 0;
    for (const auto& item : getItems()) {
        al::ByamlIter iter;
        if (ksys::act::InfoData::instance()->getActorIter(&iter, item.getName().cstr()) &&
            ksys::act::InfoData::instance()->hasTag(iter, tag)) {
            if (count_stacked_items &&
                ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::CanStack)) {
                count += item.getValue();
            } else {
                count += 1;
            }
        }
    }
    return count;
}

int PauseMenuDataMgr::countCookResults(const sead::SafeString& name, s32 effect_type,
                                       bool check_effect_type) const {
    const auto lock = sead::makeScopedLock(mCritSection);

    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;

    const bool check_name = !name.isEmpty();
    if (check_name && !info->hasTag(name.cstr(), ksys::act::tags::CookResult))
        return 0;

    s32 count = 0;
    for (auto* item = getItemHead(PouchCategory::Food); item; item = nextItem(item)) {
        if (item->getType() != PouchItemType::Food)
            break;
        if (!item->get25())
            continue;
        if (!info->hasTag(item->getName().cstr(), ksys::act::tags::CookResult))
            continue;
        if (check_effect_type && item->getCookData().mCookEffect0.x != effect_type)
            continue;
        if (check_name && item->getName() != name)
            continue;
        ++count;
    }
    return count;
}

int PauseMenuDataMgr::countItemsWithCategory(PouchCategory category) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    if (u32(category) > 6)
        return 0;
    s32 count = 0;
    for (auto* item = getItemHead(category); item; item = nextItem(item)) {
        const auto type = item->getType();
        if (getCategoryForType(type) != category)
            break;
        count += item->get25();
    }
    return count;
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
PouchCategory PauseMenuDataMgr::getCategoryForType(PouchItemType type) const {
    if (type == PouchItemType::Sword)
        return PouchCategory::Sword;

    if (isPouchItemBowOrArrow(type))
        return PouchCategory::Bow;

    switch (type) {
    case PouchItemType::Shield:
        return PouchCategory::Shield;
    case PouchItemType::ArmorHead:
    case PouchItemType::ArmorUpper:
    case PouchItemType::ArmorLower:
        return PouchCategory::Armor;
    case PouchItemType::Material:
        return PouchCategory::Material;
    case PouchItemType::Food:
        return PouchCategory::Food;
    case PouchItemType::KeyItem:
        return PouchCategory::KeyItem;
    default:
        return PouchCategory::Invalid;
    }
}

// NON_MATCHING: two harmless reorderings
void PauseMenuDataMgr::removeCookResult(const sead::SafeString& name, s32 effect_type,
                                        bool check_effect) {
    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return;

    const bool check_name = !name.isEmpty();
    if (check_name && !info->hasTag(name.cstr(), ksys::act::tags::CookResult))
        return;

    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    auto min_x = std::numeric_limits<s32>::max();
    auto min_y = std::numeric_limits<f32>::infinity();
    auto min_fx = std::numeric_limits<f32>::infinity();
    PouchItem* to_remove = nullptr;

    for (auto* item = getItemHead(PouchCategory::Food); item; item = items.next(item)) {
        if (item->getType() != PouchItemType::Food)
            break;
        if (!item->get25())
            continue;
        if (!info->hasTag(item->getName().cstr(), ksys::act::tags::CookResult))
            continue;
        if (item->getCookData().mCookEffect0.x != effect_type && check_effect)
            continue;
        if (check_name && item->getName() != name)
            continue;

        const auto y = f32(item->getCookData().mStaminaRecoverY) * 30.0f;
        if (y < min_y) {
            min_x = item->getCookData().mStaminaRecoverX;
            min_y = y;
            to_remove = item;
            min_fx = item->getCookData().mCookEffect0.y;
        } else if (y == min_y) {
            const auto x = item->getCookData().mStaminaRecoverX;
            if (x < min_x) {
                min_x = x;
                to_remove = item;
                min_fx = item->getCookData().mCookEffect0.y;
            } else if (check_effect && x == min_x && item->getCookData().mCookEffect0.y < min_fx) {
                min_fx = item->getCookData().mCookEffect0.y;
                to_remove = item;
            }
        }
    }

    if (!to_remove)
        return;

    destroyAndRecycleItem(mItemLists, to_remove);
    ksys::PlayReportMgr::instance()->reportDebug("PouchDeleteFromFlow", name);
    saveToGameData(items);
    updateInventoryInfo(items);
    updateListHeads();
}

bool PauseMenuDataMgr::switchEquipment(const sead::SafeString& name, int* value,
                                       act::WeaponModifierInfo* modifier) {
    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    sead::SafeString group_name;
    getSameGroupActorName(&group_name, name);

    PouchItem* target = nullptr;

    const auto type = getType(group_name);
    if (type <= PouchItemType::Shield) {
        for (auto& item : items) {
            if (item.getType() > PouchItemType::Shield)
                break;
            if (item.getName() == group_name && (!target || item.getValue() < target->getValue()))
                target = &item;
        }
    } else {
        if (type >= PouchItemType::Material)
            return false;
        for (auto& item : items) {
            if (item.getType() >= PouchItemType::Material)
                break;
            if (item.getName() == group_name) {
                target = &item;
                break;
            }
        }
    }

    if (!target)
        return false;

    if (value)
        *value = target->getValue();

    if (type == PouchItemType::Arrow) {
        if (target->getValue() > 0) {
            autoEquip(target, items);
            return true;
        }
        return false;
    }

    autoEquip(target, items);

    const bool is_weapon = type <= PouchItemType::Shield;
    if (modifier && is_weapon)
        modifier->fromItem(*target);

    return true;
}

void PauseMenuDataMgr::initPouchForQuest() {
    mIsPouchForQuest = true;
    resetItemAndPointers();

    {
        const auto lock = sead::makeScopedLock(mCritSection);
        const auto& items = getItems();
        PouchItem* to_remove = nullptr;

        for (auto& item : items) {
            if (to_remove != nullptr) {
                getItems().erase(to_remove);
                destroyAndRecycleItem(to_remove);
            }

            to_remove = item.getType() == PouchItemType::KeyItem ? nullptr : &item;
        }

        if (to_remove) {
            getItems().erase(to_remove);
            destroyAndRecycleItem(to_remove);
        }

        updateInventoryInfo(items);
        updateListHeads();
    }

    ksys::gdt::setFlag_FairyCountCheck(false);
    createPlayerEquipment();
}

void PauseMenuDataMgr::restorePouchForQuest() {
    mIsPouchForQuest = false;
    doLoadFromGameData();
    for (auto& entry : mGrabbedItems)
        entry = {};
    resetItemAndPointers();
    createPlayerEquipment();
}

ItemUse getItemUse(const sead::SafeString& name) {
    const char* profile_c;
    if (!ksys::act::InfoData::instance()->getActorProfile(&profile_c, name.cstr()))
        return ItemUse::Invalid;

    const sead::SafeString profile = profile_c;

    if (profile == sValues.WeaponSmallSword)
        return ItemUse::WeaponSmallSword;

    if (profile == sValues.WeaponLargeSword)
        return ItemUse::WeaponLargeSword;

    if (profile == sValues.WeaponSpear)
        return ItemUse::WeaponSpear;

    if (profile == sValues.WeaponBow)
        return ItemUse::WeaponBow;

    if (profile == sValues.WeaponShield)
        return ItemUse::WeaponShield;

    if (profile == sValues.ArmorHead)
        return ItemUse::ArmorHead;

    if (profile == sValues.ArmorUpper)
        return ItemUse::ArmorUpper;

    if (profile == sValues.ArmorLower)
        return ItemUse::ArmorLower;

    if (profile != sValues.Item && profile != sValues.PlayerItem)
        return ItemUse::Item;

    al::ByamlIter iter;
    if (!ksys::act::InfoData::instance()->getActorIter(&iter, name.cstr()))
        return ItemUse::Item;

    if (ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::CureItem))
        return ItemUse::CureItem;

    if (ksys::act::InfoData::instance()->hasTag(iter, ksys::act::tags::Important))
        return ItemUse::ImportantItem;

    return ItemUse::Item;
}

void PauseMenuDataMgr::sortItems(PouchCategory category, bool do_not_save) {
    const auto lock = sead::makeScopedLock(mCritSection);
    auto& items = getItems();

    if (items.isEmpty())
        return;

    mCategoryToSort = category;
    items.mergeSort(pouchItemSortPredicate);

    switch (category) {
    case PouchCategory::Sword:
        ksys::gdt::setFlag_SortTypeWeaponPouch(!ksys::gdt::getFlag_SortTypeWeaponPouch());
        break;
    case PouchCategory::Bow:
        ksys::gdt::setFlag_SortTypeBowPouch(!ksys::gdt::getFlag_SortTypeBowPouch());
        break;
    case PouchCategory::Shield:
        ksys::gdt::setFlag_SortTypeShieldPouch(!ksys::gdt::getFlag_SortTypeShieldPouch());
        break;
    case PouchCategory::Armor:
        ksys::gdt::setFlag_SortTypeArmorPouch(!ksys::gdt::getFlag_SortTypeArmorPouch());
        break;
    default:
        break;
    }

    if (do_not_save)
        return;

    updateInventoryInfo(items);
    updateListHeads();
    saveToGameData(items);
}

using SortPredicate = int (*)(const PouchItem* lhs, const PouchItem* rhs,
                              ksys::act::InfoData* data);

static PouchCategory getCategoryForTypeWithLookupTable(PouchItemType type) {
    static constexpr sead::SafeArray<PouchCategory, NumPouchItemTypes> sMap{{
        PouchCategory::Sword,     // Weapon
        PouchCategory::Bow,       // Bow
        PouchCategory::Bow,       // Arrow
        PouchCategory::Shield,    // Shield
        PouchCategory::Armor,     // ArmorHead
        PouchCategory::Armor,     // ArmorUpper
        PouchCategory::Armor,     // ArmorLower
        PouchCategory::Material,  // Material
        PouchCategory::Food,      // Food
        PouchCategory::KeyItem,   // KeyItem
    }};
    return sMap[s32(type)];
}

static auto getSortPredicateTable() {
    sead::SafeArray<SortPredicate, 7> table{{compareWeapon, compareBow, compareShield, compareArmor,
                                             compareMaterial, compareFood, compareKeyItem}};
    return table;
}

int pouchItemSortPredicate(const PouchItem* lhs, const PouchItem* rhs) {
    if (!lhs || !rhs)
        return 0;

    auto* info_data = ksys::act::InfoData::instance();
    if (!info_data || !lhs->get25() || !rhs->get25())
        return 0;

    const auto cat1 = getCategoryForTypeWithLookupTable(lhs->getType());
    const auto cat2 = getCategoryForTypeWithLookupTable(rhs->getType());
    if (cat1 != cat2)
        return 0;

    const auto cat3 = PauseMenuDataMgr::instance()->getCategoryToSort();
    if (cat3 != PouchCategory::Invalid && cat1 != cat3)
        return 0;

    auto predicate_table = getSortPredicateTable();
    const auto* fn = &predicate_table[0];
    if (u32(cat1) < u32(predicate_table.size()))
        fn = &predicate_table(u32(cat1));
    return (*fn)(lhs, rhs, info_data);
}

static s32 compareSortKeys(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    const auto a = data->getSortKey(lhs->getName().cstr());
    const auto b = data->getSortKey(rhs->getName().cstr());
    if (a < b)
        return -1;
    if (a > b)
        return 1;
    return 0;
}

static s32 compareItemValues(const PouchItem* lhs, const PouchItem* rhs) {
    const int val1 = lhs->getValue();
    const int val2 = rhs->getValue();
    // Higher is better
    if (val1 > val2)
        return -1;
    if (val1 < val2)
        return 1;
    return 0;
}

static int doCompareWeapon(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    const auto use1 = lhs->getItemUse();
    const auto use2 = rhs->getItemUse();
    if (use1 < use2)
        return -1;
    if (use1 > use2)
        return 1;

    const auto power1 = getWeaponPowerSortValue(lhs, data);
    const auto power2 = getWeaponPowerSortValue(rhs, data);
    if (power1 > power2)
        return -1;
    if (power1 < power2)
        return 1;

    const auto mod1 = getWeaponModifierSortKey(lhs->getWeaponAddFlags());
    const auto mod2 = getWeaponModifierSortKey(rhs->getWeaponAddFlags());
    if (mod1 < mod2)
        return -1;
    if (mod1 > mod2)
        return 1;

    return compareItemValues(lhs, rhs);
}

static int compareWeaponType0(const PouchItem* lhs, const PouchItem* rhs,
                              ksys::act::InfoData* data) {
    if (auto cmp = doCompareWeapon(lhs, rhs, data))
        return cmp;
    return compareSortKeys(lhs, rhs, data);
}

static int compareWeaponType1(const PouchItem* lhs, const PouchItem* rhs,
                              ksys::act::InfoData* data) {
    if (auto cmp = compareSortKeys(lhs, rhs, data))
        return cmp;
    return doCompareWeapon(lhs, rhs, data);
}

static int getShieldGuardPower(const PouchItem* item, ksys::act::InfoData* data) {
    int power = ksys::act::getWeaponCommonGuardPower(data, item->getName().cstr());
    if (item->getWeaponAddFlags().isOn(act::WeaponModifier::AddGuard))
        power += item->getWeaponAddValue();
    return power;
}

static int doCompareShield(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    const int gp1 = getShieldGuardPower(lhs, data);
    const int gp2 = getShieldGuardPower(rhs, data);
    // Higher is better
    if (gp1 > gp2)
        return -1;
    if (gp1 < gp2)
        return 1;

    const int mod1 = getWeaponModifierSortKey(lhs->getWeaponAddFlags());
    const int mod2 = getWeaponModifierSortKey(rhs->getWeaponAddFlags());
    // Lower is better
    if (mod1 < mod2)
        return -1;
    if (mod1 > mod2)
        return 1;

    return compareItemValues(lhs, rhs);
}

int compareWeapon(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    if (ksys::gdt::getFlag_SortTypeWeaponPouch())
        return compareWeaponType1(lhs, rhs, data);
    return compareWeaponType0(lhs, rhs, data);
}

int compareBow(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    if (lhs->getType() == PouchItemType::Arrow)
        return compareSortKeys(lhs, rhs, data);

    if (ksys::gdt::getFlag_SortTypeBowPouch())
        return compareWeaponType1(lhs, rhs, data);
    return compareWeaponType0(lhs, rhs, data);
}

int compareShield(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    if (ksys::gdt::getFlag_SortTypeShieldPouch()) {
        if (auto cmp = compareSortKeys(lhs, rhs, data))
            return cmp;

        return doCompareShield(lhs, rhs, data);

    } else {
        if (auto cmp = doCompareShield(lhs, rhs, data))
            return cmp;

        return compareSortKeys(lhs, rhs, data);
    }
}

int compareArmor(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    if (ksys::gdt::getFlag_SortTypeArmorPouch()) {
        if (auto cmp = compareSortKeys(lhs, rhs, data))
            return cmp;

        if (lhs->getType() < rhs->getType())
            return -1;
        if (lhs->getType() > rhs->getType())
            return 1;
    } else {
        if (lhs->getType() < rhs->getType())
            return -1;
        if (lhs->getType() > rhs->getType())
            return 1;

        if (auto cmp = compareSortKeys(lhs, rhs, data))
            return cmp;
    }

    if (lhs->getCount() < rhs->getCount())
        return -1;
    if (lhs->getCount() > rhs->getCount())
        return 1;

    return 0;
}

int compareMaterial(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    const int order1 = getCookItemOrder(lhs, data);
    const int order2 = getCookItemOrder(rhs, data);
    // Lower is better
    if (order1 < order2)
        return -1;
    if (order1 > order2)
        return 1;

    const int hp1 = getItemHitPointRecover(lhs->getName().cstr());
    const int hp2 = getItemHitPointRecover(rhs->getName().cstr());
    // Higher is better
    if (hp1 > hp2)
        return -1;
    if (hp1 < hp2)
        return 1;

    return compareSortKeys(lhs, rhs, data);
}

int compareFood(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    int e1, e2;
    const int k1 = getFoodSortKey(&e1, lhs);
    const int k2 = getFoodSortKey(&e2, rhs);
    // Lower key is better
    if (k1 < k2)
        return -1;
    if (k1 > k2)
        return 1;

    if (auto cmp = compareSortKeys(lhs, rhs, data))
        return cmp;

    // Higher is better
    if (e1 > e2)
        return -1;
    if (e1 < e2)
        return 1;

    const int st1 = lhs->getCookData().mStaminaRecoverX;
    const int st2 = rhs->getCookData().mStaminaRecoverX;
    // Higher is better
    if (st1 > st2)
        return -1;
    if (st1 < st2)
        return 1;

    const auto sv1 = lhs->getCookData().getStaminaRecoverValue();
    const auto sv2 = rhs->getCookData().getStaminaRecoverValue();
    // Higher is better
    if (sv1 > sv2)
        return -1;
    if (sv1 < sv2)
        return 1;

    return 0;
}

int compareKeyItem(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data) {
    if (auto cmp = compareSortKeys(lhs, rhs, data))
        return cmp;
    return 0;
}

int getCookItemOrder(const PouchItem* item, ksys::act::InfoData* data) {
    const auto& order = sValues.cook_item_order;
    al::ByamlIter iter;
    if (data->getActorIter(&iter, item->getName().cstr())) {
        for (auto it = order.begin(), end = order.end(); it != end; ++it) {
            if (it->is_tag == 0 && item->getName() == it->name.cstr())
                return it.getIndex();
        }

        for (auto it = order.begin(), end = order.end(); it != end; ++it) {
            if (it->is_tag == 1 && data->hasTag(iter, it->hash))
                return it.getIndex();
        }
    }
    return order.size();
}

int pouchItemSortPredicateForArrow(const PouchItem* lhs, const PouchItem* rhs) {
    if (!lhs || !rhs)
        return 0;

    static constexpr sead::SafeArray<int, NumPouchItemTypes> sMap{{0, 1, 2, 3, 4, 4, 4, 7, 8, 9}};
    const auto x1 = sMap[s32(lhs->getType())];
    const auto x2 = sMap[s32(rhs->getType())];
    if (x1 < x2)
        return -1;
    if (x1 > x2)
        return 1;

    if (lhs->getType() != PouchItemType::Arrow)
        return 0;

    auto* info_data = ksys::act::InfoData::instance();
    if (!info_data || !lhs->get25() || !rhs->get25())
        return 0;

    const auto cat1 = getCategoryForTypeWithLookupTable(lhs->getType());
    const auto cat2 = getCategoryForTypeWithLookupTable(rhs->getType());
    if (cat1 != cat2)
        return 0;

    const auto cat3 = PauseMenuDataMgr::instance()->getCategoryToSort();
    if (cat3 != PouchCategory::Invalid && cat1 != cat3)
        return 0;

    const auto predicate_table = getSortPredicateTable();
    const auto* fn = &predicate_table[0];
    if (u32(cat1) < u32(predicate_table.size()))
        fn = &predicate_table(u32(cat1));
    return (*fn)(lhs, rhs, info_data);
}

// NON_MATCHING: branching, but this is so trivial it isn't worth spending time on matching this
const sead::SafeString* PauseMenuDataMgr::getEquippedItemName(PouchItemType type) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    if (!isPouchItemEquipment(type) || items.isEmpty())
        return nullptr;

    auto* first = type <= PouchItemType::Shield ? items.nth(0) : getItemHead(PouchCategory::Armor);
    for (auto* item = first; item; item = items.next(item)) {
        if (item->isEquipped() && item->getType() == type)
            return &item->getName();
    }
    return nullptr;
}

const PouchItem* PauseMenuDataMgr::getEquippedItem(PouchItemType type) const {
    const auto lock = sead::makeScopedLock(mCritSection);
    const auto& items = getItems();

    if (!isPouchItemEquipment(type) || items.isEmpty())
        return nullptr;

    auto* first = type <= PouchItemType::Shield ? items.nth(0) : getItemHead(PouchCategory::Armor);
    for (auto* item = first; item; item = items.next(item)) {
        if (item->isEquipped() && item->getType() == type)
            return item;
    }
    return nullptr;
}

int PauseMenuDataMgr::getItemValue(const sead::SafeString& name) const {
    const auto type = getType(name);
    if (isPouchItemInvalid(type))
        return 0;

    sead::SafeString group_name;
    getSameGroupActorName(&group_name, name);

    if (ksys::act::InfoData::instance()->hasTag(group_name.cstr(), ksys::act::tags::CanStack)) {
        for (const auto& item : mItemLists.buffer) {
            if (item.get25() && item.getType() == type && !group_name.comparen(item.getName(), 64))
                return item.getValue();
        }
        return 0;
    }

    s32 count = 0;
    for (const auto& item : mItemLists.buffer) {
        if (item.get25() && item.getType() == type && !group_name.comparen(item.getName(), 64))
            count++;
    }
    return count;
}

bool PauseMenuDataMgr::getFromShop(const sead::SafeString& name, int value,
                                   const act::WeaponModifierInfo* modifier) {
    const auto lock = sead::makeScopedLock(mCritSection);
    auto& lists = mItemLists;
    const auto type = getType(name);

    al::ByamlIter iter;
    namespace act = ksys::act;
    act::InfoData::instance()->getActorIter(&iter, name.cstr());

    if (iter.isValid() && act::InfoData::instance()->hasTag(iter, act::tags::CanStack)) {
        addToPouch(name, type, lists, value, false, modifier);
    } else if (iter.isValid() && act::InfoData::instance()->hasTag(iter, act::tags::ArmorDye)) {
        addToPouch(name, type, lists, 0, false, modifier);
    } else if (type > PouchItemType::Shield || type == PouchItemType::Arrow) {
        addToPouch(name, type, lists, 1, false, modifier);
    } else {
        int life = getItemGeneralLife(name.cstr());
        if (modifier)
            life += modifier->flags.isOn(uking::act::WeaponModifier::AddLife) ? modifier->value : 0;
        addToPouch(name, type, lists, life, false, modifier);
    }

    ksys::PlayReportMgr::instance()->reportDebug("PouchGetFromShop", name);
    saveToGameData(lists.list1);
    return true;
}

int PauseMenuDataMgr::countArmorDye() const {
    int count = 0;
    using namespace ksys::act;
    for (const auto& item : getItems()) {
        if (item.get25() && InfoData::instance()->hasTag(item.getName().cstr(), tags::ArmorDye))
            ++count;
    }
    return count;
}

int PauseMenuDataMgr::countAlreadyDyedArmor() const {
    int count = 0;
    using namespace ksys::act;
    for (const auto& item : getItems()) {
        if (item.get25() && InfoData::instance()->hasTag(item.getName().cstr(), tags::ArmorDye) &&
            item.getValue() > 0) {
            ++count;
        }
    }
    return count;
}

int PauseMenuDataMgr::getNextGrabbedItemIndex() const {
    for (int i = 0; i < mGrabbedItems.size(); ++i) {
        if (mGrabbedItems[i].item == nullptr)
            return i;
    }
    return mGrabbedItems.size();
}

bool PauseMenuDataMgr::canGrabAnotherItem() const {
    return std::any_of(mGrabbedItems.begin(), mGrabbedItems.end(),
                       [](const auto& entry) { return entry.item == nullptr; });
}

bool PauseMenuDataMgr::isNothingBeingGrabbed() const {
    return std::all_of(mGrabbedItems.begin(), mGrabbedItems.end(),
                       [](const auto& entry) { return entry.item == nullptr; });
}

bool PauseMenuDataMgr::isHeroSoulEnabled(const sead::SafeString& name) const {
    if (name == sValues.Obj_HeroSoul_Zora || name == sValues.Obj_DLC_HeroSoul_Zora) {
        if (mZoraSoulItem)
            return mZoraSoulItem->isEquipped();
    }

    if (name == sValues.Obj_HeroSoul_Rito || name == sValues.Obj_DLC_HeroSoul_Rito) {
        if (mRitoSoulItem)
            return mRitoSoulItem->isEquipped();
    }

    if (name == sValues.Obj_HeroSoul_Goron || name == sValues.Obj_DLC_HeroSoul_Goron) {
        if (mGoronSoulItem)
            return mGoronSoulItem->isEquipped();
    }

    if (name == sValues.Obj_HeroSoul_Gerudo || name == sValues.Obj_DLC_HeroSoul_Gerudo) {
        if (mGerudoSoulItem)
            return mGerudoSoulItem->isEquipped();
    }

    return false;
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool PauseMenuDataMgr::hasRitoSoulPlus() const {
    return ksys::gdt::getFlag_IsGet_Obj_DLC_HeroSoul_Rito() && aoc::Manager::instance()->hasAoc3();
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool PauseMenuDataMgr::hasGoronSoulPlus() const {
    return ksys::gdt::getFlag_IsGet_Obj_DLC_HeroSoul_Goron() && aoc::Manager::instance()->hasAoc3();
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool PauseMenuDataMgr::hasGerudoSoulPlus() const {
    return ksys::gdt::getFlag_IsGet_Obj_DLC_HeroSoul_Gerudo() &&
           aoc::Manager::instance()->hasAoc3();
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
bool PauseMenuDataMgr::hasZoraSoulPlus() const {
    return ksys::gdt::getFlag_IsGet_Obj_DLC_HeroSoul_Zora() && aoc::Manager::instance()->hasAoc3();
}

int PauseMenuDataMgr::countItemsWithCategoryByType(PouchCategory category) const {
    switch (category) {
    case PouchCategory::Sword:
        return countItems(PouchItemType::Sword);
    case PouchCategory::Bow:
        return countItems(PouchItemType::Bow) + countItems(PouchItemType::Arrow);
    case PouchCategory::Shield:
        return countItems(PouchItemType::Shield);
    case PouchCategory::Armor:
        return countItems(PouchItemType::ArmorLower);
    case PouchCategory::Material:
        return countItems(PouchItemType::Material);
    case PouchCategory::Food:
        return countItems(PouchItemType::Food);
    case PouchCategory::KeyItem:
        return countItems(PouchItemType::KeyItem);
    case PouchCategory::Invalid:
        break;
    }
    return 0;
}

const PouchItem* PauseMenuDataMgr::getItemByIndex(PouchItemType type, int index) const {
    const auto& list = getItems();
    PouchItem* item = nullptr;
    switch (type) {
    case PouchItemType::Sword:
        item = getItemHead(PouchCategory::Sword);
        break;
    case PouchItemType::Bow:
        item = getItemHead(PouchCategory::Bow);
        break;
    case PouchItemType::Arrow:
        for (auto* item_ = getItemHead(PouchCategory::Bow);
             item_ && item_->getType() <= PouchItemType::Arrow; item_ = list.next(item_)) {
            if (item_->getType() == PouchItemType::Arrow) {
                item = item_;
                break;
            }
        }
        break;
    case PouchItemType::Shield:
        item = getItemHead(PouchCategory::Shield);
        break;
    case PouchItemType::ArmorHead:
    case PouchItemType::ArmorUpper:
    case PouchItemType::ArmorLower:
        item = getItemHead(PouchCategory::Armor);
        break;
    case PouchItemType::Material:
        item = getItemHead(PouchCategory::Material);
        break;
    case PouchItemType::Food:
        item = getItemHead(PouchCategory::Food);
        break;
    case PouchItemType::KeyItem:
        item = getItemHead(PouchCategory::KeyItem);
        break;
    case PouchItemType::Invalid:
        break;
    }

    if (!item)
        return nullptr;

    for (int i = 0; i < index; ++i) {
        if (!item)
            return nullptr;
        item = list.next(item);
    }

    if (item) {
        if (isPouchItemArmor(type))
            return isPouchItemArmor(item->getType()) ? item : nullptr;
        if (item->getType() == type)
            return item;
    }
    return nullptr;
}

const PouchItem* PauseMenuDataMgr::getItemByIndex(PouchCategory category, int index) const {
    switch (category) {
    case PouchCategory::Sword:
        return getItemByIndex(PouchItemType::Sword, index);
    case PouchCategory::Bow: {
        const auto num_bows = ksys::gdt::getFlag_BowPorchStockNum();
        if (index < num_bows)
            return getItemByIndex(PouchItemType::Bow, index);
        return getItemByIndex(PouchItemType::Arrow, index - num_bows);
    }
    case PouchCategory::Shield:
        return getItemByIndex(PouchItemType::Shield, index);
    case PouchCategory::Armor:
        return getItemByIndex(PouchItemType::ArmorLower, index);
    case PouchCategory::Material:
        return getItemByIndex(PouchItemType::Material, index);
    case PouchCategory::Food:
        return getItemByIndex(PouchItemType::Food, index);
    case PouchCategory::KeyItem:
        return getItemByIndex(PouchItemType::KeyItem, index);
    case PouchCategory::Invalid:
        break;
    }
    return nullptr;
}

bool PauseMenuDataMgr::hasItemDye() const {
    int counts[1 + NumDyeColors]{};
    for (const auto& item : getItems()) {
        auto* info = ksys::act::InfoData::instance();
        const int color = ksys::act::getItemStainColor(info, item.getName().cstr());
        if (color >= FirstDyeColorIndex && color <= LastDyeColorIndex && item.get25()) {
            counts[color] += item.getValue();
            if (counts[color] >= NumRequiredDyeItemsPerColor)
                return true;
        }
    }
    return false;
}

bool PauseMenuDataMgr::hasItemDye(int color) const {
    int count = 0;
    for (const auto& item : getItems()) {
        auto* info = ksys::act::InfoData::instance();
        if (ksys::act::getItemStainColor(info, item.getName().cstr()) == color && item.get25()) {
            count += item.getValue();
            if (count >= NumRequiredDyeItemsPerColor)
                return true;
        }
    }
    return false;
}

const PouchItem* PauseMenuDataMgr::getLastAddedItem() const {
    if (!mNewlyAddedItem.getName().isEmpty())
        return &mNewlyAddedItem;
    if (mLastAddedItem)
        return mLastAddedItem;
    return &mNewlyAddedItem;
}

void PauseMenuDataMgr::updateEquippedItemArray() {
    mEquippedWeapons.fill({});
    const auto lock = sead::makeScopedLock(mCritSection);
    for (auto& item : getItems()) {
        if (item.getType() > PouchItemType::Shield)
            break;
        if (item.isEquipped())
            mEquippedWeapons[u32(item.getType())] = &item;
    }
}

void PauseMenuDataMgr::resetEquippedItemArray() {
    mEquippedWeapons.fill({});
}

bool PauseMenuDataMgr::isOverCategoryLimit(PouchItemType type) const {
    const auto count = countItems(type);
    switch (type) {
    case PouchItemType::Sword:
        return ksys::gdt::getFlag_WeaponPorchStockNum() <= count || count >= NumSwordsMax;
    case PouchItemType::Bow:
        return ksys::gdt::getFlag_BowPorchStockNum() <= count || count >= NumBowsMax;
    case PouchItemType::Arrow:
        return count >= NumArrowItemsMax;
    case PouchItemType::Shield:
        return ksys::gdt::getFlag_ShieldPorchStockNum() <= count || count >= NumShieldsMax;
    case PouchItemType::ArmorHead:
    case PouchItemType::ArmorUpper:
    case PouchItemType::ArmorLower:
        return count >= NumArmorsMax;
    case PouchItemType::Material:
        return count >= NumMaterialsMax;
    case PouchItemType::Food:
        return count >= NumFoodMax;
    case PouchItemType::KeyItem:
        return count >= NumKeyItemsMax;
    case PouchItemType::Invalid:
        break;
    }
    return true;
}

// NON_MATCHING: branching (really weird issue...)
int PauseMenuDataMgr::countArmors(const sead::SafeString& lowest_rank_armor_name) const {
    if (!isPouchItemArmor(getType(lowest_rank_armor_name)))
        return 0;

    if (!getItemHead(PouchCategory::Armor))
        return 0;

    auto* info = ksys::act::InfoData::instance();
    if (!info)
        return 0;

    const auto lock = sead::makeScopedLock(mCritSection);

    int count = 0;
    sead::FixedSafeString<64> armor_name{lowest_rank_armor_name};
    while (!armor_name.isEmpty()) {
        for (auto* item = *mListHeads[u32(PouchCategory::Armor)]; item; item = nextItem(item)) {
            if (item->getType() > PouchItemType::ArmorLower)
                break;
            if (item->get25() && armor_name == item->getName())
                ++count;
        }
        armor_name = ksys::act::getArmorNextRankName(info, armor_name.cstr());
    }
    return count;
}

void PauseMenuDataMgr::addNonDefaultItem(const sead::SafeString& name, int value,
                                         const act::WeaponModifierInfo* modifier) {
    if (name.include("Default") || name.include("Extra"))
        return;

    const auto type = getType(name);
    if (type != PouchItemType::Arrow && value >= 0 && isPouchItemWeapon(type))
        value *= act::WeaponModifierInfo::getLifeMultiplier();

    const auto lock = sead::makeScopedLock(mCritSection);
    addToPouch(name, type, mItemLists, value, false, modifier);
}

void PauseMenuDataMgr::openItemCategoryIfNeeded() const {
    for (s32 i = 0; i < NumPouch50; ++i) {
        const auto type = mArray2[i];
        if (isPouchItemArmor(type)) {
            ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Armor));
        } else {
            switch (type) {
            case PouchItemType::Sword:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Sword));
                break;
            case PouchItemType::Bow:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Bow));
                break;
            case PouchItemType::Shield:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Shield));
                break;
            case PouchItemType::Material:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Material));
                break;
            case PouchItemType::Food:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::Food));
                break;
            case PouchItemType::KeyItem:
                ksys::gdt::setFlag_IsOpenItemCategory(true, u32(PouchCategory::KeyItem));
                break;
            default:
                break;
            }
        }
    }
}

void PauseMenuDataMgr::initInventoryForOpenWorldDemo() {
    if (!GameScene::isOpenWorldDemo())
        return;

    initForNewSave();

    auto* info = ksys::act::InfoData::instance();
    sead::FixedSafeString<64> unused{""};

    addNonDefaultItem("Weapon_Sword_001",
                      info ? ksys::act::getGeneralLife(info, "Weapon_Sword_001") : 30);
    autoEquipLastAddedItem();

    addNonDefaultItem("Weapon_Shield_001",
                      info ? ksys::act::getGeneralLife(info, "Weapon_Shield_001") : 30);
    autoEquipLastAddedItem();

    addNonDefaultItem("Weapon_Bow_001",
                      info ? ksys::act::getGeneralLife(info, "Weapon_Bow_001") : 30);
    autoEquipLastAddedItem();

    addNonDefaultItem("Armor_001_Head", 0);
    autoEquipLastAddedItem();

    addNonDefaultItem("Armor_116_Upper", 0);
    autoEquipLastAddedItem();

    addNonDefaultItem("Armor_001_Lower", 0);
    autoEquipLastAddedItem();

    for (int i = 0; i < 10; ++i) {
        addNonDefaultItem("Obj_ArrowBundle_A_01", 1);
        autoEquipLastAddedItem();
    }

    if (!ksys::util::getDebugHeap()) {
        addItemForDebug("Obj_BombArrow_A_01", 100);
        addItemForDebug("Obj_AncientArrow_A_01", 100);
        addItemForDebug("Obj_FireArrow_A_01", 100);
        addItemForDebug("Obj_ElectricArrow_A_01", 100);
        addItemForDebug("Obj_IceArrow_A_01", 100);
        addItemForDebug("PlayerStole2", 1);
        addItemForDebug("Obj_DRStone_Get", 1);
        addItemForDebug("GameRomHorseSaddle_01", 1);
        addItemForDebug("GameRomHorseSaddle_02", 1);
        addItemForDebug("GameRomHorseSaddle_03", 1);
        addItemForDebug("GameRomHorseSaddle_04", 1);
        addItemForDebug("GameRomHorseSaddle_05", 1);
        addItemForDebug("GameRomHorseReins_01", 1);
        addItemForDebug("GameRomHorseReins_02", 1);
        addItemForDebug("GameRomHorseReins_03", 1);
        addItemForDebug("GameRomHorseReins_04", 1);
        addItemForDebug("GameRomHorseReins_05", 1);
        addItemForDebug("Weapon_Lsword_056", 1);
        addItemForDebug("Weapon_Spear_001", 1);
        addItemForDebug("Weapon_Lsword_032", 1);
        addItemForDebug("Weapon_Shield_002", 1);
        addItemForDebug("Weapon_Bow_002", 1);
        addItemForDebug("Weapon_Bow_027", 1);
        addItemForDebug("Weapon_Sword_070", 1);
        addItemForDebug("Weapon_Sword_043", 1);
        addItemForDebug("Weapon_Sword_006", 1);
    }

    const auto lock = sead::makeScopedLock(mCritSection);
    saveToGameData(getItems());
}

[[gnu::noinline]] void PouchItem::sortIngredients() {
    mIngredients.sort(
        [](const sead::FixedSafeString<64>* lhs, const sead::FixedSafeString<64>* rhs) {
            auto* info = ksys::act::InfoData::instance();
            if (!lhs || !rhs || !info)
                return 0;

            if (rhs->isEmpty()) {
                if (lhs->isEmpty())
                    return 0;
                return -1;
            }

            const s32 key1 = info->getSortKey(lhs->cstr());
            const s32 key2 = info->getSortKey(rhs->cstr());
            if (key1 < key2)
                return -1;
            if (key1 > key2)
                return 1;
            return 0;
        });
}

// NOLINTNEXTLINE(readability-convert-member-functions-to-static)
void PauseMenuDataMgr::updateDivineBeastClearFlags(int num_cleared_beasts) {
    switch (num_cleared_beasts) {
    case 1:
        ksys::gdt::setFlag_Find_4Relic_1stClear(true);
        break;
    case 2:
        ksys::gdt::setFlag_Find_4Relic_2ndClear(true);
        ksys::gdt::setFlag_BattleArena_Level1(false, true);
        ksys::gdt::setFlag_BattleArena_Level2(true, true);
        break;
    case 3:
        ksys::gdt::setFlag_Find_4Relic_3rdClear(true);
        ksys::gdt::setFlag_BattleArena_Level1(false, true);
        ksys::gdt::setFlag_BattleArena_Level2(false, true);
        ksys::gdt::setFlag_BattleArena_Level3(true, true);
        break;
    case 4:
        ksys::gdt::setFlag_Find_4Relic_4thClear(true);
        ksys::gdt::setFlag_BattleArena_Level1(false, true);
        ksys::gdt::setFlag_BattleArena_Level2(false, true);
        ksys::gdt::setFlag_BattleArena_Level3(false, true);
        ksys::gdt::setFlag_BattleArena_Level4(true, true);
        break;
    default:
        break;
    }
}

}  // namespace uking::ui
