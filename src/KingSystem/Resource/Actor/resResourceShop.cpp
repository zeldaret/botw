#include "KingSystem/Resource/Actor/resResourceShop.h"

namespace ksys::res {

bool Shop::parse_(u8* data, size_t, sead::Heap* heap) {
    mTableNum.init(0, "TableNum", "テーブルの数", &mObj);
    addObj(&mObj, "Header");

    if (!data)
        return true;

    applyResParameterArchive(agl::utl::ResParameterArchive{data});

    const s32 num_tables = mTableNum.ref();
    if (num_tables < 1)
        return true;

    mTables.allocBufferAssert(num_tables, heap);

    const agl::utl::ResParameterArchive archive{data};
    const auto root = archive.getRootList();
    const auto header_obj = root.getResParameterObj(0);

    for (s32 i = 0; i < num_tables; ++i) {
        sead::FormatFixedSafeString<64> name;
        name.format("Table%02d", i + 1);
        mTables[i].name.init("", name, "テーブル名", &mObj);
    }

    mObj.applyResParameterObj(header_obj);

    for (s32 i = 0; i < num_tables; ++i) {
        const auto obj = root.getResParameterObj(i + 1);
        mTables[i].column_num.init(0, "ColumnNum", "行数", &mTables[i].obj);

        addObj(&mTables[i].obj, mTables[i].name.ref());
        applyResParameterArchive(agl::utl::ResParameterArchive{data});
        mTables[i].obj.applyResParameterObj(obj);

        if (mTables[i].column_num.ref() > 0) {
            mTables[i].items.allocBufferAssert(mTables[i].column_num.ref(), heap);
        }
    }

    for (s32 i = 0; i < num_tables; ++i) {
        parseTable_(i);
    }

    applyResParameterArchive(agl::utl::ResParameterArchive{data});

    return true;
}

void Shop::parseTable_(const s32& table_idx) {
    const s32 num = mTables[table_idx].column_num.ref();
    for (s32 i = 0; i < num; ++i) {
        sead::FormatFixedSafeString<64> name;
        name.format("ItemSort%03d", i + 1);
        mTables[table_idx].items[i].sort_value.init(0, name, "ソート値", &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name2;
        name2.format("ItemName%03d", i + 1);
        mTables[table_idx].items[i].name.init("", name2, "アイテム名", &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name3;
        name3.format("ItemNum%03d", i + 1);
        mTables[table_idx].items[i].num_stock.init(0, name3, "販売個数", &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name4;
        name4.format("ItemAdjustPrice%03d", i + 1);
        mTables[table_idx].items[i].price_adjustment.init(0, name4, "値段調整値",
                                                          &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name5;
        name5.format("ItemLookGetFlg%03d", i + 1);
        mTables[table_idx].items[i].demo_flag.init(false, name5, "ゲットフラグを見るか",
                                                   &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name6;
        name6.format("ItemAmount%03d", i + 1);
        mTables[table_idx].items[i].price.init(0, name6, "価値", &mTables[table_idx].obj);
    }
}

s32 Shop::findTableIndex(const sead::SafeString& table_name) const {
    if (!mTables.isBufferReady())
        return -1;

    const s32 num = mTableNum.ref();
    for (s32 i = 0; i < num; ++i) {
        if (mTables[i].name.ref() == table_name)
            return i;
    }

    return -1;
}

s32 Shop::findTableIndexOrNormal(const sead::SafeString& table_name) const {
    if (!mTables.isBufferReady())
        return -1;

    s32 normal_idx = -1;
    const s32 num = mTableNum.ref();
    for (s32 i = 0; i < num; ++i) {
        if (mTables[i].name.ref() == table_name)
            return i;

        if (normal_idx < 0 && mTables[i].name.ref() == "Normal")
            normal_idx = i;
    }

    return normal_idx;
}

}  // namespace ksys::res
