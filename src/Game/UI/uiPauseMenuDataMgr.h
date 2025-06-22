#pragma once

#include <basis/seadTypes.h>
#include <container/seadBuffer.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
#include "Game/Cooking/cookManager.h"
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace ksys::act {
class BaseProcLink;
class InfoData;
}  // namespace ksys::act

namespace uking::act {
enum class WeaponModifier : u32;
struct WeaponModifierInfo;
}  // namespace uking::act

namespace uking {
struct CookItem;
}  // namespace uking

namespace uking::ui {

enum class CreateEquipmentSlot : u8;

constexpr int NumSwordsMax = 20;
constexpr int NumBowsMax = 14;
constexpr int NumArrowItemsMax = 6;
constexpr int NumShieldsMax = 20;
constexpr int NumArmorsMax = 100;
constexpr int NumMaterialsMax = 160;
constexpr int NumFoodMax = 60;
constexpr int NumKeyItemsMax = 40;

constexpr int NumPouchItemsMax = NumSwordsMax + NumBowsMax + NumArrowItemsMax + NumShieldsMax +
                                 NumArmorsMax + NumMaterialsMax + NumFoodMax + NumKeyItemsMax;

static_assert(NumPouchItemsMax == 420, "NumPouchItemsMax must be 420 for now");

constexpr int ItemStackSizeMax = 999;

// Maximum number of tabs (pages with 20 items) you can have.
// Going beyond this limit will glitch the menu.
constexpr int NumTabMax = 50;
constexpr int NumItemsPerTabMax = 20;

constexpr int NumGrabbableItems = 5;

enum class PouchItemType {
    Sword = 0,
    Bow = 1,
    Arrow = 2,
    Shield = 3,
    ArmorHead = 4,
    ArmorUpper = 5,
    ArmorLower = 6,
    Material = 7,
    Food = 8,
    KeyItem = 9,
    Invalid = -1,
};

constexpr int NumPouchItemTypes = 10;

constexpr bool isPouchItemWeapon(PouchItemType type) {
    return type == PouchItemType::Sword || type == PouchItemType::Bow ||
           type == PouchItemType::Arrow || type == PouchItemType::Shield;
}

constexpr bool isPouchItemBowOrArrow(PouchItemType type) {
    return type == PouchItemType::Bow || type == PouchItemType::Arrow;
}

constexpr bool isPouchItemNotWeapon(PouchItemType type) {
    return !isPouchItemWeapon(type);
}

constexpr bool isPouchItemArmor(PouchItemType type) {
    return PouchItemType::ArmorHead <= type && type <= PouchItemType::ArmorLower;
}

constexpr bool isPouchItemEquipment(PouchItemType type) {
    return isPouchItemWeapon(type) || isPouchItemArmor(type);
}

constexpr bool isPouchItemInvalid(PouchItemType type) {
    return u32(type) > u32(PouchItemType::KeyItem);
}

enum class PouchCategory {
    Sword = 0,
    Bow = 1,
    Shield = 2,
    Armor = 3,
    Material = 4,
    Food = 5,
    KeyItem = 6,
    Invalid = -1,
};

constexpr int NumPouchCategories = 7;

enum class EquipmentSlot {
    WeaponRight = 0,
    WeaponBow = 1,
    WeaponArrow = 2,
    WeaponLeft = 3,
    ArmorHead = 4,
    ArmorUpper = 5,
    ArmorLower = 6,
    Invalid = -1,
};

enum class ItemUse {
    WeaponSmallSword = 0,
    WeaponLargeSword = 1,
    WeaponSpear = 2,
    WeaponBow = 3,
    WeaponShield = 4,
    ArmorHead = 5,
    ArmorUpper = 6,
    ArmorLower = 7,
    Item = 8,
    ImportantItem = 9,
    CureItem = 10,
    Invalid = -1,
};

constexpr int NumDyeColors = 15;
constexpr int FirstDyeColorIndex = 1;
constexpr int LastDyeColorIndex = 15;
static_assert(NumDyeColors == LastDyeColorIndex - FirstDyeColorIndex + 1,
              "Dye color indices must be contiguous");
constexpr int NumRequiredDyeItemsPerColor = 5;

struct CookTagInfo {
    u32 is_tag;
    sead::SafeString name;
    u32 hash;
};

class PouchItem {
public:
    struct CookData {
        f32 getEffectDurationFrames() const { return f32(mEffectDuration) * 30.0f; }
        void setHealthRecover(int hp) { mHealthRecover = hp; }
        void setEffectDuration(int seconds) { mEffectDuration = seconds; }
        void setSellPrice(int price) { mSellPrice = price; }
        void setEffect(const sead::Vector2f& effect) { mEffect = effect; }
        CookEffectId getEffect() const { return static_cast<CookEffectId>(mEffect.x); }
        f32 getEffectId() const { return mEffect.x; }
        f32 getEffectLevel() const { return mEffect.y; }

        /// Number of quarter-hearts to recover,
        /// for hearty food, this is number of yellow hearts (not quarter-hearts)
        int mHealthRecover;
        int mEffectDuration;  // for potions, in seconds
        int mSellPrice;

        /// x - CookEffectId enum, but stored as f32
        /// y - level:
        ///     - For Hearty (LifeMaxUp), this is also the number of yellow hearts
        ///     - For Stamina (GutsRecover), this is 0.0-3000.0 where each wheel is 1000.0
        ///     - For Endura (ExGutsMaxUp), this is 0-15, where each wheel is 5
        ///       - With 5 endura carrot + crit you can only get to 12
        ///     - For other, this is the level of the effect (1.0f, 2.0f, or 3.0f)
        sead::Vector2f mEffect;
    };

    struct WeaponData {
        u32 mModifierValue;
        u32 mUnused;
        u32 mModifier;
        sead::Vector2f mEffectUnused;

        sead::TypedBitFlag<act::WeaponModifier> getModifier() const {
            return sead::TypedBitFlag<act::WeaponModifier>{mModifier};
        }
    };

    PouchItem();
    virtual ~PouchItem() = default;

    PouchItemType getType() const { return mType; }
    bool isEquipped() const { return mEquipped; }
    void setEquipped(bool equipped) { mEquipped = equipped; }
    bool isInInventory() const { return mInInventory; }
    const sead::SafeString& getName() const { return mName; }
    ItemUse getItemUse() const { return mItemUse; }

    bool isWeapon() const { return getType() <= PouchItemType::Shield; }

    // This is only valid if the item is not a weapon.
    s32 getCount() const { return getValue(); }

    s32 getValue() const { return mValue; }

    // Only valid if this is not a weapon.
    CookData& getCookData() { return mData.cook; }
    const CookData& getCookData() const { return mData.cook; }

    const sead::SafeString& getIngredient(s32 idx) const { return *mIngredients[idx]; }
    void setIngredient(s32 idx, const sead::SafeString& value) const { *mIngredients[idx] = value; }
    void sortIngredients();

    // Only valid if this is a weapon.
    WeaponData& getWeaponData() { return mData.weapon; }
    const WeaponData& getWeaponData() const { return mData.weapon; }

    sead::TypedBitFlag<act::WeaponModifier> getWeaponModifier() const {
        if (!isWeapon())
            return {};
        return mData.weapon.getModifier();
    }

    u32 getWeaponModifierValue() const {
        if (!isWeapon())
            return 0;
        return mData.weapon.mModifierValue;
    }

    void setWeaponModifier(u32 type) {
        if (isWeapon())
            mData.weapon.mModifier = type;
    }

    void setWeaponModifierValue(u32 value) {
        if (isWeapon())
            mData.weapon.mModifierValue = value;
    }
    void setWeaponModifierInfo(const act::WeaponModifierInfo* info);

    static auto getListNodeOffset() { return offsetof(PouchItem, mListNode); }

private:
    friend class PauseMenuDataMgr;

    union Data {
        CookData cook;
        WeaponData weapon;
    };

    static constexpr int NumIngredientsMax = 5;

    sead::ListNode mListNode;
    PouchItemType mType = PouchItemType::Invalid;
    ItemUse mItemUse = ItemUse::Invalid;
    s32 mValue = 0;
    bool mEquipped = false;
    bool mInInventory = true;
    sead::FixedSafeString<64> mName;
    Data mData{};
    sead::FixedObjArray<sead::FixedSafeString<64>, NumIngredientsMax> mIngredients;
};
KSYS_CHECK_SIZE_NX150(PouchItem, 0x298);

// TODO
class PauseMenuDataMgr {
    SEAD_SINGLETON_DISPOSER(PauseMenuDataMgr)
    PauseMenuDataMgr();
    virtual ~PauseMenuDataMgr();

public:
    void init(sead::Heap* heap);
    void initForNewSave();
    void loadFromGameData();

    bool cannotGetItem(const sead::SafeString& name, int n) const;

    static PouchItemType getType(const sead::SafeString& item, al::ByamlIter* iter = nullptr);

    int countItems(PouchItemType type, bool count_any_weapon = false) const;
    bool isWeaponSectionFull(const sead::SafeString& get_flag) const;

    void itemGet(const sead::SafeString& name, int value, const act::WeaponModifierInfo* modifier);
    void cookItemGet(const uking::CookItem& cook_item);

    void setCookDataOnLastAddedItem(const uking::CookItem& cook_item);

    void autoEquipLastAddedItem();
    const sead::SafeString& autoEquip(PouchItem* item, const sead::OffsetList<PouchItem>& list);
    /// Unequip all inventory items with the specified type.
    /// If type is PouchItemType::Invalid, all inventory items will be unequipped.
    void unequipAll(PouchItemType type = PouchItemType::Invalid);

    void removeItem(const sead::SafeString& name);
    void removeWeaponIfEquipped(const sead::SafeString& name);
    void removeArrow(const sead::SafeString& arrow_name, int count = 1);

    int getItemCount(const sead::SafeString& name, bool count_equipped = true) const;

    // TODO: requires CreatePlayerEquipActorMgr
    void createPlayerEquipment();
    void setEquippedWeaponItemValue(s32 value, PouchItemType type);
    const sead::SafeString& getDefaultEquipment(EquipmentSlot idx) const;

    bool hasItem(const sead::SafeString& name) const;
    PouchItem* getMasterSword() const;

    void removeGrabbedItems();
    bool removeGrabbedItem(ksys::act::BaseProcLink* link);

    bool getEquippedArrowType(sead::BufferedSafeString* name, int* count) const;
    int getArrowCount(const sead::SafeString& name) const;
    /// Get the number of arrows in the real inventory (ignoring any temporary inventory data).
    /// This was added in 1.3.1 to patch the Trial of the Sword arrow restock glitch.
    int getRealArrowCount(const sead::SafeString& name) const;

    void breakMasterSword();
    void restoreMasterSword(bool only_if_broken);

    bool checkAddOrRemoveItem(const sead::SafeString& name, int count,
                              bool include_equipped_items) const;
    int getFreeSlotCount() const;

    int calculateEnemyMaterialMamo() const;
    void removeAllEnemyMaterials();

    int countItemsWithProfile(const sead::SafeString& profile, bool count_stacked_items) const;
    int countItemsWithTag(u32 tag, bool count_stacked_items) const;
    int countCookResults(const sead::SafeString& name = {}, s32 effect_type = 0x11,
                         bool check_effect_type = false) const;
    int countItemsWithCategory(PouchCategory category) const;
    PouchCategory getCategoryForType(PouchItemType type) const;

    void removeCookResult(const sead::SafeString& name = {}, s32 effect_type = 0x11,
                          bool check_effect = false);

    bool switchEquipment(const sead::SafeString& name, int* value = nullptr,
                         act::WeaponModifierInfo* modifier = nullptr);

    void initPouchForQuest();
    void restorePouchForQuest();

    void sortItems(PouchCategory category, bool do_not_save = false);

    const sead::SafeString* getEquippedItemName(PouchItemType type) const;
    const PouchItem* getEquippedItem(PouchItemType type) const;
    int getItemValue(const sead::SafeString& name) const;

    bool getFromShop(const sead::SafeString& name, int value,
                     const act::WeaponModifierInfo* modifier = nullptr);

    int countArmorDye() const;
    int countAlreadyDyedArmor() const;

    int getNextGrabbedItemIndex() const;
    bool canGrabAnotherItem() const;
    bool isNothingBeingGrabbed() const;

    bool isHeroSoulEnabled(const sead::SafeString& name) const;
    bool hasRitoSoulPlus() const;
    bool hasGoronSoulPlus() const;
    bool hasGerudoSoulPlus() const;
    bool hasZoraSoulPlus() const;

    int countItemsWithCategoryByType(PouchCategory category) const;
    const PouchItem* getItemByIndex(PouchCategory category, int index) const;

    bool hasItemDye() const;
    bool hasItemDye(int color) const;

    const PouchItem* getLastAddedItem() const;

    void updateEquippedItemArray();
    void resetEquippedItemArray();

    bool isOverCategoryLimit(PouchItemType type) const;

    int countArmors(const sead::SafeString& lowest_rank_armor_name) const;

    void openItemCategoryIfNeeded() const;

    void initInventoryForOpenWorldDemo();

    PouchCategory getCategoryToSort() const { return mCategoryToSort; }

    void equipWeapon(PouchItem* weapon);
    void unequip(PouchItem* item);

    // FIXME: types
    bool useItemFromRecipeAndSave(void* unk, int multiplier, PouchItem* item);

    void grabbedItemStuff(PouchItem* item);
    PouchCategory getTabCategory(int tab_index);
    const sead::SafeString* getNameFromTabSlot(int tab_index, int slot_index) const;
    PouchItem* getPouchItemFromTabSlot(int tab_index, int slot_index) const;
    bool isInInventoryFromTabSlot(int tab_index, int slot_index) const;
    bool isEquippedFromTabSlot(int tab_index, int slot_index) const;
    const sead::SafeString* equipFromTabSlot(int tab_index, int slot_index);
    void useMaybe(int tab_index, int slot_index, int quantity);
    void sellItem(PouchItem* target_item, int quantity);
    int getWeaponsForDpad(sead::SafeArray<PouchItem*, NumItemsPerTabMax>* result_array,
                          PouchItemType target_type) const;

private:
    // TODO: rename
    struct GrabbedItemInfo {
        PouchItem* item{};
        bool _8{};
        bool _9{};
    };
    KSYS_CHECK_SIZE_NX150(GrabbedItemInfo, 0x10);

    struct Lists {
        Lists() {
            list1.initOffset(PouchItem::getListNodeOffset());
            list2.initOffset(PouchItem::getListNodeOffset());
            for (auto& item : buffer) {
                new (&item) PouchItem();
                list2.pushFront(&item);
            }
        }

        void destroyAndRecycleItem(PouchItem* item) {
            list1.erase(item);
            item->~PouchItem();
            new (item) PouchItem;
            list2.pushFront(item);
        }

        PouchItem* pushNewItem() {
            auto* item = list2.popFront();
            if (item) {
                list1.pushBack(item);
            }
            return item;
        }

        sead::OffsetList<PouchItem> list1;
        sead::OffsetList<PouchItem> list2;
        sead::SafeArray<PouchItem, NumPouchItemsMax> buffer;
    };

    sead::OffsetList<PouchItem>& getItems() { return mItemLists.list1; }
    const sead::OffsetList<PouchItem>& getItems() const { return mItemLists.list1; }

    // FIXME: types
    bool useItemFromRecipe(Lists* lists, void* unk, int multiplier, PouchItem* item);

    PouchItem* getItemHead(PouchCategory category) const {
        auto* p_head = mListHeads[u32(category)];
        if (!p_head)
            return nullptr;
        return *p_head;
    }

    PouchItem** getItemHeadp(PouchCategory category) const { return mListHeads[u32(category)]; }

    PouchItem* nextItem(const PouchItem* item) const { return getItems().next(item); }
    bool isList2Empty() const { return mItemLists.list2.isEmpty(); }

    const PouchItem* getItemByIndex(PouchItemType type, int index) const;

    void destroyAndRecycleItem(PouchItem* item) {
        item->~PouchItem();
        new (item) PouchItem;
        mItemLists.list2.pushFront(item);
    }

    void destroyAndRecycleItem(Lists& lists, PouchItem* item) {
        if (mItem_444f0 == item)
            mItem_444f0 = nullptr;
        if (mLastAddedItem == item)
            mLastAddedItem = nullptr;

        lists.destroyAndRecycleItem(item);
    }

    void resetItem();

    void resetItemAndPointers() {
        mLastAddedItem = nullptr;
        mItem_444f0 = nullptr;
        _444f8 = -1;
        resetItem();
    }

    void setItemModifier(PouchItem& item, const act::WeaponModifierInfo* modifier);

    void doLoadFromGameData();

    // 710096c954
    void updateInventoryInfo(const sead::OffsetList<PouchItem>& list);
    void updateListHeads();
    void saveToGameData(const sead::OffsetList<PouchItem>& list) const;
    void updateAfterAddingItem(bool only_sort);

    void addToPouch(const sead::SafeString& name, PouchItemType type, Lists& lists, int value,
                    bool equipped, const act::WeaponModifierInfo* modifier = nullptr,
                    bool is_inventory_load = false);

    void doAddToPouch(PouchItemType type, const sead::SafeString& name, Lists& lists, int value,
                      bool equipped, const act::WeaponModifierInfo* modifier = nullptr,
                      bool is_inventory_load = false);

    void deleteItem_(const sead::OffsetList<PouchItem>& list, PouchItem* item,
                     const sead::SafeString& name);

    void addNonDefaultItem(const sead::SafeString& name, int value,
                           const act::WeaponModifierInfo* modifier = nullptr);

    bool hasFreeSpaceForItem(const Lists& lists, const sead::SafeString& name, int n = 1) const;

    /// @param num_cleared_beasts The number of divine beasts that have been done.
    void updateDivineBeastClearFlags(int num_cleared_beasts);

    int getNumberOfItemsInTab(int tab_index) const;

    mutable sead::CriticalSection mCritSection;
    Lists mItemLists;
    sead::SafeArray<PouchItem**, NumPouchCategories> mListHeads;
    sead::SafeArray<PouchItem*, NumTabMax> mTabs;
    sead::SafeArray<PouchItemType, NumTabMax> mTabsType;
    PouchItem* mLastAddedItem{};
    s32 mLastAddedItemTab = -1;
    s32 mLastAddedItemSlot = -1;
    s32 mNumTabs = 0;
    sead::SafeArray<GrabbedItemInfo, NumGrabbableItems> mGrabbedItems;
    PouchItem* mItem_444f0{};
    s32 _444f8 = -1;
    s32 _444fc{};
    s32 _44500 = -1;
    u32 mNumSmallSwords{};
    u32 mNumLargeSwords{};
    u32 mNumSpears{};
    u32 mNumShields{};
    u32 mNumBows{};
    PouchItem* mRitoSoulItem{};
    PouchItem* mGoronSoulItem{};
    PouchItem* mZoraSoulItem{};
    PouchItem* mGerudoSoulItem{};

    // Indicates if the Champion's Tunic or a divine helm is equipped
    // and whether the player can see enemy HP.
    bool mCanSeeHealthBar = false;
    PouchItem mNewlyAddedItem;

    /// Indicates if a temporary inventory ("pouch for quest") is being used.
    bool mIsPouchForQuest = false;

    sead::SafeArray<PouchItem*, 4> mEquippedWeapons;
    PouchCategory mCategoryToSort = PouchCategory::Invalid;
};
KSYS_CHECK_SIZE_NX150(PauseMenuDataMgr, 0x44808);

int compareWeapon(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareBow(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareShield(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareArmor(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareMaterial(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareFood(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);
int compareKeyItem(const PouchItem* lhs, const PouchItem* rhs, ksys::act::InfoData* data);

int getCookItemOrder(const PouchItem* item, ksys::act::InfoData* data);

ItemUse getItemUse(const sead::SafeString& name);

}  // namespace uking::ui
