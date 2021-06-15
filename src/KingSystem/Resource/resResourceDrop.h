#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class Drop : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Drop, Resource)
public:
    Drop() : ParamIO("drop", 0) {}

    /// Returns the name of a randomly chosen drop from the specified table or from the Normal table
    /// if the table cannot be found.
    /// The empty string is returned if no drop was chosen.
    const sead::SafeString& getRandomDropFromTable(const sead::SafeString& table_name) const;

    /// Returns the name of a randomly chosen drop from the specified table.
    /// The empty string is returned if no drop was chosen.
    const sead::SafeString& getRandomDropFromTable(s32 table_idx) const;

    /// Returns the index of the specified table. If the table cannot be found, the index of the
    /// first Normal table is returned. Note that it may be equal to -1 if there is no Normal table.
    s32 findTableIndexOrNormal(const sead::SafeString& table_name) const;

    /// Returns the index of the specified table or -1 if it cannot be found.
    s32 findTableIndex(const sead::SafeString& table_name) const;

    s32 getApproachType(s32 table_idx) const;
    s32 getOccurrenceSpeedType(s32 table_idx) const;
    s32 getRepeatNum(s32 table_idx) const;
    s32 getRepeatNum(const sead::SafeString& table_name) const;

    bool ParamIO_m0(char* data) override { return true; }
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }

private:
    struct Item {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<f32> probability;
    };
    KSYS_CHECK_SIZE_NX150(Item, 0x48);

    struct Table {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<s32> repeat_num_min;
        agl::utl::Parameter<s32> repeat_num_max;
        agl::utl::Parameter<s32> approach_type;
        agl::utl::Parameter<s32> occurrence_speed_type;
        agl::utl::Parameter<s32> column_num;
        sead::Buffer<Item> items;
    };
    KSYS_CHECK_SIZE_NX150(Table, 0x108);

    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void parseItems_(s32& table_idx);

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<s32> mTableNum;
    sead::Buffer<void*> _300;
    sead::Buffer<Table> mTables;
};
KSYS_CHECK_SIZE_NX150(Drop, 0x320);

}  // namespace ksys::res
