#include "Game/UI/uiPauseMenuDataMgr.h"
#include <container/seadBuffer.h>
#include <limits>
#include <prim/seadScopedLock.h>
#include "KingSystem/ActorSystem/actActorUtil.h"
#include "KingSystem/ActorSystem/actInfoData.h"
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/Utils/Byaml/Byaml.h"
#include "KingSystem/Utils/InitTimeInfo.h"

namespace uking::ui {

SEAD_SINGLETON_DISPOSER_IMPL(PauseMenuDataMgr)

sead::Vector2f sDummyCookEffect0{-1, 0};

namespace {

sead::SafeArray<CookTagInfo, 11> sCookTagInfo_{{
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

struct PouchConstants {
    ksys::util::InitTimeInfoEx info;

    void* _18{};
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

    sead::Buffer<CookTagInfo> cook_tag_info{sCookTagInfo_.size(), sCookTagInfo_.getBufferPtr()};

    sead::SafeArray<sead::SafeString, 7> default_equipment_names{{
        "Weapon_Default_Right",
        "Weapon_Default_Bow",
        "Weapon_Default_Arrow",
        "Weapon_Default_Left",
        "Armor_Default_Head",
        "Armor_Default_Upper",
        "Armor_Default_Lower",
    }};

    sead::SafeString Armor_168_Head = "Armor_168_Head";
    sead::SafeString Armor_169_Head = "Armor_169_Head";
    sead::SafeString Armor_181_Head = "Armor_181_Head";
    sead::SafeString Armor_182_Head = "Armor_182_Head";
    sead::SafeString Armor_183_Head = "Armor_183_Head";
    sead::SafeString Armor_184_Head = "Armor_184_Head";
    sead::SafeString Armor_186_Head = "Armor_186_Head";
    sead::SafeString Armor_187_Head = "Armor_187_Head";
    sead::SafeString Armor_188_Head = "Armor_188_Head";
    sead::SafeString Armor_189_Head = "Armor_189_Head";
    sead::SafeString Armor_190_Head = "Armor_190_Head";
    sead::SafeString Armor_191_Head = "Armor_191_Head";
    sead::SafeString Armor_192_Head = "Armor_192_Head";
    sead::SafeString Armor_193_Head = "Armor_193_Head";
    sead::SafeString Armor_194_Head = "Armor_194_Head";
    sead::SafeString Armor_195_Head = "Armor_195_Head";
    sead::SafeString Armor_196_Head = "Armor_196_Head";
    sead::SafeString Armor_197_Head = "Armor_197_Head";
    sead::SafeString Armor_198_Head = "Armor_198_Head";
    sead::SafeString Armor_199_Head = "Armor_199_Head";
};

PouchConstants sValues;

}  // namespace

PauseMenuDataMgr::PauseMenuDataMgr() {
    mListHeads.fill(nullptr);
    for (s32 i = 0; i < NumPouch50; ++i) {
        mArray1[i] = nullptr;
        mArray2[i] = -1;
    }
    for (auto& x : mArray3)
        x = {};
    _447e0 = {};
    _447e8 = {};
    _447f0 = {};
    _447f8 = {};
}

PauseMenuDataMgr::~PauseMenuDataMgr() = default;

PouchItem::PouchItem() {
    mData.cook.mCookEffect0 = sDummyCookEffect0;
    for (s32 i = 0; i < NumIngredientsMax; ++i)
        mIngredients.emplaceBack();
}

void PauseMenuDataMgr::init(sead::Heap* heap) {}

PouchItemType PauseMenuDataMgr::getType(const sead::SafeString& item, al::ByamlIter* iter) {
    sead::SafeString group;
    if (iter) {
        ksys::act::getSameGroupActorName(&group, item, iter);
    } else {
        ksys::act::getSameGroupActorName(&group, item);
    }

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
        return PouchItemType::Weapon;
    if (profile == sValues.WeaponLargeSword)
        return PouchItemType::Weapon;
    if (profile == sValues.WeaponSpear)
        return PouchItemType::Weapon;

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

void PauseMenuDataMgr::setWeaponItemValue(s32 value, PouchItemType type) {
    if (isPouchItemNotWeapon(type))
        return;

    const auto lock = sead::makeScopedLock(mCritSection);

    s32 idx = 0;
    for (auto& item : getItems()) {
        if (!item.isValid() || item.getType() != type) {
            ++idx;
            continue;
        }

        item.setValue(value);
        if (idx >= 0 && !mIsPouchForQuest)
            ksys::gdt::setFlag_PorchItem_Value1(value, idx);

        return;
    }
}

const sead::SafeString& PauseMenuDataMgr::getDefaultEquipment(u32 idx) const {
    if (idx != 2 && idx < u32(sValues.default_equipment_names.size()))
        return sValues.default_equipment_names(idx);
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

    for (auto* item = getItemHead(PouchCategory::Weapon); item; item = getItems().next(item)) {
        if (item->getType() != PouchItemType::Weapon)
            return nullptr;
        if (item->_25 && item->getName() == "Weapon_Sword_070")
            return item;
    }

    return nullptr;
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