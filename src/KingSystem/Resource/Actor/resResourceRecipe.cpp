#include "KingSystem/Resource/Actor/resResourceRecipe.h"

namespace ksys::res {

// NON_MATCHING: first line (see also Drop::parse_)
bool Recipe::parse_(u8* data, size_t, sead::Heap* heap) {
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

void Recipe::parseTable_(const s32& table_idx) {
    const s32 num = mTables[table_idx].column_num.ref();
    for (s32 i = 0; i < num; ++i) {
        sead::FormatFixedSafeString<64> name;
        name.format("ItemName%02d", i + 1);
        mTables[table_idx].items[i].name.init("", name, "アイテム名", &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name2;
        name2.format("ItemNum%02d", i + 1);
        mTables[table_idx].items[i].num.init(0, name2, "個数", &mTables[table_idx].obj);
    }
}

}  // namespace ksys::res
