#include "KingSystem/Resource/Actor/resResourceDrop.h"
#include <random/seadGlobalRandom.h>

namespace ksys::res {

bool Drop::parse_(u8* data, size_t, sead::Heap* heap) {
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

        mTables[i].repeat_num_min.init(0, "RepeatNumMin", "抽選回数最小", &mTables[i].obj);
        mTables[i].repeat_num_max.init(0, "RepeatNumMax", "抽選回数最大", &mTables[i].obj);
        mTables[i].approach_type.init(0, "ApproachType", "姿勢", &mTables[i].obj);
        mTables[i].occurrence_speed_type.init(0, "OccurrenceSpeedType", "発生速度",
                                              &mTables[i].obj);
        mTables[i].column_num.init(0, "ColumnNum", "行数", &mTables[i].obj);

        addObj(&mTables[i].obj, mTables[i].name.ref());
        applyResParameterArchive(agl::utl::ResParameterArchive{data});
        mTables[i].obj.applyResParameterObj(obj);

        if (mTables[i].column_num.ref() > 0) {
            mTables[i].items.allocBufferAssert(mTables[i].column_num.ref(), heap);
        }
    }

    for (s32 i = 0; i < num_tables; ++i) {
        parseItems_(i);
    }

    applyResParameterArchive(agl::utl::ResParameterArchive{data});
    return true;
}

void Drop::parseItems_(s32& table_idx) {
    const s32 num = mTables[table_idx].column_num.ref();
    for (s32 i = 0; i < num; ++i) {
        sead::FormatFixedSafeString<64> name;
        name.format("ItemName%02d", i + 1);
        mTables[table_idx].items[i].name.init("", name, "アイテム名", &mTables[table_idx].obj);

        sead::FormatFixedSafeString<64> name2;
        name2.format("ItemProbability%02d", i + 1);
        mTables[table_idx].items[i].probability.init(0.0, name2, "確率", &mTables[table_idx].obj);
    }
}

s32 Drop::findTableIndex(const sead::SafeString& table_name) const {
    if (!mTables.isBufferReady())
        return -1;

    const s32 num = mTableNum.ref();
    for (s32 i = 0; i < num; ++i) {
        if (mTables[i].name.ref() == table_name)
            return i;
    }

    return -1;
}

s32 Drop::findTableIndexOrNormal(const sead::SafeString& table_name) const {
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

const sead::SafeString& Drop::getRandomDropFromTable(const sead::SafeString& table_name) const {
    return getRandomDropFromTable(findTableIndexOrNormal(table_name));
}

const sead::SafeString& Drop::getRandomDropFromTable(s32 table_idx) const {
    if (!mTables.isBufferReady())
        return sead::SafeString::cEmptyString;

    /// @bug The index check should be done first...
    if (!mTables[table_idx].items.isBufferReady() || table_idx < 0)
        return sead::SafeString::cEmptyString;

    f32 x = sead::GlobalRandom::instance()->getF32() * 100.0;

    const Table& table = mTables[table_idx];
    const s32 num_items = table.column_num.ref();
    for (s32 i = 0; i < num_items; ++i) {
        const Item& item = table.items[i];

        const f32 probability = item.probability.ref();
        if (x < probability)
            return item.name.ref();

        x -= probability;
    }

    return sead::SafeString::cEmptyString;
}

s32 Drop::getApproachType(s32 table_idx) const {
    if (!mTables.isBufferReady())
        return 0;

    /// @bug This bounds checking is bugged: the order is absurd and the second check is off-by-one.
    if (!mTables[table_idx].items.isBufferReady() || table_idx < 0 || table_idx > mTables.size())
        return 0;

    return mTables[table_idx].approach_type.ref();
}

s32 Drop::getOccurrenceSpeedType(s32 table_idx) const {
    if (!mTables.isBufferReady())
        return 0;

    /// @bug This bounds checking is bugged: the order is absurd and the second check is off-by-one.
    if (!mTables[table_idx].items.isBufferReady() || table_idx < 0 || table_idx > mTables.size())
        return 0;

    return mTables[table_idx].occurrence_speed_type.ref();
}

s32 Drop::getRepeatNum(s32 table_idx) const {
    if (!mTables.isBufferReady())
        return 0;

    const Table& table = mTables[table_idx];
    if (!mTables[table_idx].items.isBufferReady() || table_idx < 0 || table_idx > mTables.size())
        return 0;

    const s32 num_min = table.repeat_num_min.ref();
    const s32 num_max = table.repeat_num_max.ref();
    if (num_min == num_max)
        return num_min;
    return num_min + sead::GlobalRandom::instance()->getU32(1 - num_min + num_max);
}

s32 Drop::getRepeatNum(const sead::SafeString& table_name) const {
    return getRepeatNum(findTableIndexOrNormal(table_name));
}

}  // namespace ksys::res
