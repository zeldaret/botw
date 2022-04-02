#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <agl/utl/aglResParameter.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class Handle;
}

namespace ksys::phys {

class ContactMgr;
class GroupFilter;
class MaterialTable;
class RagdollControllerKeyList;

struct LayerTable : agl::utl::IParameterObj {
    sead::SafeArray<agl::utl::Parameter<int>, MaxNumLayersPerType> layer_values;
    GroupFilter* filter;
    ContactLayer layer;
    int num_layers;

protected:
    void postRead_() override;
};
KSYS_CHECK_SIZE_NX150(LayerTable, 0x440);

struct CharacterControllerTable : agl::utl::IParameterObj {
    SEAD_ENUM(Type, Default)

    sead::SafeArray<agl::utl::Parameter<float>, Material::size()> params;
};
KSYS_CHECK_SIZE_NX150(CharacterControllerTable, 0x4b0);

class SystemData {
public:
    template <typename Table, int Count>
    class Tables {
    public:
        auto& Entries() { return mTables; }
        const auto& Entries() const { return mTables; }

    private:
        friend class SystemData;

        void addList(const char* name) { mParamIO.addList(&mParamList, name); }

        sead::SafeArray<Table, Count> mTables;
        agl::utl::ParameterList mParamList;
        agl::utl::IParameterIO mParamIO;
        res::Handle* mResHandle = nullptr;
    };

    SystemData();
    virtual ~SystemData();

    void load(sead::Heap* heap, GroupFilter* entity_group_filter, GroupFilter* sensor_group_filter,
              MaterialTable* material_table, ContactMgr* contact_mgr);

private:
    using LayerMatrix = Tables<LayerTable, MaxNumLayersPerType>;

    void loadLayerTable(sead::Heap* heap, GroupFilter* filter, ContactLayerType type);
    void loadMaterialTable(sead::Heap* heap, MaterialTable* table);
    void loadSubMaterialTable(sead::Heap* heap, MaterialTable* table);
    void loadContactInfoTable(sead::Heap* heap, ContactMgr* mgr, ContactLayerType type);
    void loadCharacterCtrlTable(sead::Heap* heap);
    void loadRagdollCtrlKeyList(sead::Heap* heap);

    agl::utl::ResParameterArchive loadLayerTableRes(const LayerMatrix& matrix,
                                                    ContactLayerType type);
    agl::utl::ResParameterArchive loadMaterialTableRes();
    agl::utl::ResParameterArchive loadSubMaterialTableRes();
    agl::utl::ResParameterArchive loadContactInfoTableRes(ContactLayerType type);
    agl::utl::ResParameterArchive loadCharacterCtrlTableRes();

    sead::SafeArray<LayerMatrix, 2> mLayerMatrices{};
    res::Handle* mMaterialTableHandle{};
    res::Handle* mSubMaterialTableHandle{};
    sead::SafeArray<res::Handle*, 2> mContactInfoTableHandles{};
    Tables<CharacterControllerTable, 1> mCharacterCtrlTable;
    RagdollControllerKeyList* mRagdollCtrlKeyList{};
    res::Handle* mRagdollCtrlKeyListHandle{};
};
KSYS_CHECK_SIZE_NX150(SystemData, 0x11b48);

}  // namespace ksys::phys
