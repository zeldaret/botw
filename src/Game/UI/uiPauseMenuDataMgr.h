#pragma once

#include <basis/seadTypes.h>
#include <container/seadListImpl.h>
#include <container/seadObjArray.h>
#include <container/seadOffsetList.h>
#include <container/seadSafeArray.h>
#include <heap/seadDisposer.h>
#include <math/seadVector.h>
#include <prim/seadSafeString.h>
#include <thread/seadCriticalSection.h>
#include "KingSystem/Utils/Types.h"

namespace al {
class ByamlIter;
}

namespace uking::ui {

constexpr int NumPouchItemsMax = 420;
// TODO: figure out what this is
constexpr int NumPouch50 = 50;

enum class PouchItemType {
    Weapon = 0,
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

constexpr bool isPouchItemWeapon(PouchItemType type) {
    return type == PouchItemType::Weapon || type == PouchItemType::Bow ||
           type == PouchItemType::Arrow || type == PouchItemType::Shield;
}

constexpr bool isPouchItemNotWeapon(PouchItemType type) {
    return !isPouchItemWeapon(type);
}

enum class PouchCategory {
    Weapon = 0,
    Bow = 1,
    Shield = 2,
    Armor = 3,
    Material = 4,
    Food = 5,
    KeyItem = 6,
};

constexpr int NumPouchCategories = 7;

struct CookTagInfo {
    u32 is_tag;
    sead::SafeString name;
    u32 hash;
};

class PouchItem {
public:
    PouchItem();
    virtual ~PouchItem() = default;

    PouchItemType getType() const { return mType; }
    bool isValid() const { return mValid; }
    const sead::SafeString& getName() const { return mName; }

    // This is only valid if the item is not a weapon.
    s32 getCount() const { return getValue(); }

    s32 getValue() const { return mValue; }
    void setValue(s32 value) { mValue = value; }

    static auto getListNodeOffset() { return offsetof(PouchItem, mListNode); }

private:
    friend class PauseMenuDataMgr;

    struct CookData {
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

    union Data {
        CookData cook;
        WeaponData weapon;
    };

    static constexpr int NumIngredientsMax = 5;

    sead::ListNode mListNode;
    PouchItemType mType = PouchItemType::Invalid;
    s32 _1c = -1;
    s32 mValue = 0;
    bool mValid = false;
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

    static PouchItemType getType(const sead::SafeString& item, al::ByamlIter* iter);

    void removeArrow(const sead::SafeString& arrow_name, int count = 1);
    int getItemCount(const sead::SafeString& name, bool x = true) const;
    void setWeaponItemValue(s32 value, PouchItemType type);
    const sead::SafeString& getDefaultEquipment(u32 idx) const;
    bool hasItem(const sead::SafeString& name) const;
    PouchItem* getMasterSword() const;

private:
    // TODO: rename
    struct ItemInfo {
        PouchItem* item{};
        u8 _8{};
        u8 _9{};
    };
    KSYS_CHECK_SIZE_NX150(ItemInfo, 0x10);

    struct Lists {
        Lists() {
            list1.initOffset(PouchItem::getListNodeOffset());
            list2.initOffset(PouchItem::getListNodeOffset());
            for (auto& item : buffer) {
                new (&item) PouchItem();
                list2.pushFront(&item);
            }
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

    /// @param num_cleared_beasts The number of divine beasts that have been done.
    void updateDivineBeastClearFlags(int num_cleared_beasts);

    mutable sead::CriticalSection mCritSection;
    Lists mItemLists;
    sead::SafeArray<PouchItem**, NumPouchCategories> mListHeads;
    sead::SafeArray<PouchItem*, NumPouch50> mArray1;
    sead::SafeArray<int, NumPouch50> mArray2;
    PouchItem* mItem_44488{};
    s32 _44490 = -1;
    s32 _44494 = -1;
    s32 _44498{};
    sead::SafeArray<ItemInfo, 5> mArray3;
    PouchItem* mItem_444f0{};
    s32 _444f8 = -1;
    s32 _444fc{};
    s32 _44500 = -1;
    u32 _44504{};
    u32 _44508{};
    u32 _4450c{};
    u32 _44510{};
    u32 _44514{};
    u64 _44518{};
    u64 _44520{};
    u64 _44528{};
    PouchItem* _44530{};
    bool _44538 = false;
    PouchItem mItem;

    /// Indicates if a temporary inventory ("pouch for quest") is being used.
    bool mIsPouchForQuest = false;

    u64 _447e0;
    u64 _447e8;
    u64 _447f0;
    u64 _447f8;
    s32 _44800 = -1;
};
KSYS_CHECK_SIZE_NX150(PauseMenuDataMgr, 0x44808);

}  // namespace uking::ui
