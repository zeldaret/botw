#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <agl/Utils/aglResParameter.h>
#include <container/seadSafeArray.h>
#include <prim/seadEnum.h>
#include "KingSystem/Physics/System/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {
class Handle;
}

namespace ksys::phys {

class ContactInfoTable;
class LayerTable;
class MaterialTable;
class RagdollControllerKeyList;

constexpr int NumLayers = 32;

struct LayerTableInfo : agl::utl::IParameterObj {
    sead::SafeArray<agl::utl::Parameter<int>, NumLayers> params;
    void* table;  // FIXME: type GroupFilter
    int idx = 0;  // FIXME: ContactLayer
    int count;

protected:
    void postRead_() override;
};
KSYS_CHECK_SIZE_NX150(LayerTableInfo, 0x440);

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

    void load(sead::Heap* heap, LayerTable* entity_layer_table, LayerTable* sensor_layer_table,
              MaterialTable* material_table, ContactInfoTable* contact_info_table);

private:
    using LayerTableInfoContainer = Tables<LayerTableInfo, NumLayers>;

    void loadLayerTable(sead::Heap* heap, LayerTable* table, ContactLayerType type);
    void loadMaterialTable(sead::Heap* heap, MaterialTable* table);
    void loadSubMaterialTable(sead::Heap* heap, MaterialTable* table);
    void loadContactInfoTable(sead::Heap* heap, ContactInfoTable* table, ContactLayerType type);
    void loadCharacterCtrlTable(sead::Heap* heap);
    void loadRagdollCtrlKeyList(sead::Heap* heap);

    agl::utl::ResParameterArchive loadLayerTableRes(const LayerTableInfoContainer& container,
                                                    ContactLayerType type);
    agl::utl::ResParameterArchive loadMaterialTableRes();
    agl::utl::ResParameterArchive loadSubMaterialTableRes();
    agl::utl::ResParameterArchive loadContactInfoTableRes(ContactLayerType type);
    agl::utl::ResParameterArchive loadCharacterCtrlTableRes();

    sead::SafeArray<LayerTableInfoContainer, 2> mLayerTableInfo{};
    res::Handle* mMaterialTableHandle{};
    res::Handle* mSubMaterialTableHandle{};
    sead::SafeArray<res::Handle*, 2> mContactInfoTableHandles{};
    Tables<CharacterControllerTable, 1> mCharacterCtrlTable;
    RagdollControllerKeyList* mRagdollCtrlKeyList{};
    res::Handle* mRagdollCtrlKeyListHandle{};
};
KSYS_CHECK_SIZE_NX150(SystemData, 0x11b48);

}  // namespace ksys::phys
