#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <prim/seadTypedBitFlag.h>
#include <thread/seadCriticalSection.h>
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

namespace ksys {
struct CookItem;
}

namespace uking::ui {

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

// TODO: figure out what this is
constexpr int NumPouch50 = 50;

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
        f32 getStaminaRecoverValue() const { return f32(mStaminaRecoverY) * 30.0f; }
        void setStaminaRecoverX(int x) { mStaminaRecoverX = x; }
        void setStaminaRecoverY(int y) { mStaminaRecoverY = y; }
        void setCookEffect1(int effect) { mCookEffect1 = effect; }
        void setCookEffect0(const sead::Vector2f& effect) { mCookEffect0 = effect; }

        int mStaminaRecoverX;
        int mStaminaRecoverY;
        int mCookEffect1;
        sead::Vector2f mCookEffect0;
    };

    struct WeaponData {
        u32 mAddValue;
        u32 b;
        u32 mAddType;
        u32 d;
        u32 e;
    };

    PouchItem();
    virtual ~PouchItem() = default;

    PouchItemType getType() const { return mType; }
    bool isEquipped() const { return mEquipped; }
    u8 get25() const { return _25; }
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

    sead::TypedBitFlag<act::WeaponModifier> getWeaponAddFlags() const {
        if (!isWeapon())
            return {};
        return sead::TypedBitFlag<act::WeaponModifier>{mData.weapon.mAddType};
    }

    u32 getWeaponAddValue() const {
        if (!isWeapon())
            return 0;
        return mData.weapon.mAddValue;
    }

    void setWeaponAddType(u32 type) {
        if (isWeapon())
            mData.weapon.mAddType = type;
    }

    void setWeaponAddValue(u32 value) {
        if (isWeapon())
            mData.weapon.mAddValue = value;
    }

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
    u8 _25 = 1;
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
    void cookItemGet(const ksys::CookItem& cook_item);

    void setCookDataOnLastAddedItem(const ksys::CookItem& cook_item);

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
    bool addGrabbedItem(ksys::act::BaseProcLink* link);

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

        sead::OffsetList<PouchItem> list1;
        sead::OffsetList<PouchItem> list2;
        sead::SafeArray<PouchItem, NumPouchItemsMax> buffer;
    };

    sead::OffsetList<PouchItem>& getItems() { return mItemLists.list1; }
    const sead::OffsetList<PouchItem>& getItems() const { return mItemLists.list1; }

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

    mutable sead::CriticalSection mCritSection;
    Lists mItemLists;
    sead::SafeArray<PouchItem**, NumPouchCategories> mListHeads;
    sead::SafeArray<PouchItem*, NumPouch50> mArray1;
    sead::SafeArray<PouchItemType, NumPouch50> mArray2;
    PouchItem* mLastAddedItem{};
    s32 _44490 = -1;
    s32 _44494 = -1;
    s32 _44498{};
    sead::SafeArray<GrabbedItemInfo, NumGrabbableItems> mGrabbedItems;
    PouchItem* mItem_444f0{};
    s32 _444f8 = -1;
    s32 _444fc{};
    s32 _44500 = -1;
    u32 _44504{};
    u32 _44508{};
    u32 _4450c{};
    u32 _44510{};
    u32 _44514{};
    PouchItem* mRitoSoulItem{};
    PouchItem* mGoronSoulItem{};
    PouchItem* mZoraSoulItem{};
    PouchItem* mGerudoSoulItem{};
    bool _44538 = false;
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
