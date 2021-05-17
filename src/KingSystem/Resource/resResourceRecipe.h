#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterObj.h>
#include <container/seadBuffer.h>
#include "KingSystem/Resource/resResource.h"
#include "KingSystem/Utils/ParamIO.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class Recipe : public ParamIO, public Resource {
    SEAD_RTTI_OVERRIDE(Recipe, Resource)
public:
    struct Item {
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<s32> num;
    };
    KSYS_CHECK_SIZE_NX150(Item, 0x48);

    struct Table {
        agl::utl::ParameterObj obj;
        agl::utl::Parameter<sead::SafeString> name;
        agl::utl::Parameter<s32> column_num;
        sead::Buffer<Item> items;
    };
    KSYS_CHECK_SIZE_NX150(Table, 0x88);

    Recipe() : ParamIO("recipe", 0) {}

    bool ParamIO_m0(char* data) override { return true; }
    void doCreate_(u8*, u32, sead::Heap*) override {}
    bool needsParse() const override { return true; }

    const sead::Buffer<Table>& getTables() const { return mTables; }

private:
    bool parse_(u8* data, size_t size, sead::Heap* heap) override;
    void parseTable_(const s32& table_idx);

    agl::utl::ParameterObj mObj;
    agl::utl::Parameter<s32> mTableNum;
    sead::Buffer<void*> _300;
    sead::Buffer<Table> mTables;
};
KSYS_CHECK_SIZE_NX150(Recipe, 0x320);

}  // namespace ksys::res
