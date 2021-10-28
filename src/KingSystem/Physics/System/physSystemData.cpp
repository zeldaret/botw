#include "KingSystem/Physics/System/physSystemData.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
#include "KingSystem/Physics/System/physRagdollControllerKeyList.h"
#include "KingSystem/Resource/resHandle.h"
#include "KingSystem/Resource/resLoadRequest.h"

namespace ksys::phys {

SystemData::SystemData() = default;

template <typename T>
static void deleteAndNull(T*& ptr) {
    if (ptr) {
        delete ptr;
        ptr = nullptr;
    }
}

SystemData::~SystemData() {
    deleteAndNull(mMaterialTableHandle);
    deleteAndNull(mSubMaterialTableHandle);

    deleteAndNull(mLayerTableInfo[0].mResHandle);
    deleteAndNull(mContactInfoTableHandles[0]);

    deleteAndNull(mLayerTableInfo[1].mResHandle);
    deleteAndNull(mContactInfoTableHandles[1]);

    deleteAndNull(mCharacterCtrlTable.mResHandle);

    if (auto*& handle = mRagdollCtrlKeyListHandle) {
        delete handle;
        handle = nullptr;
        mRagdollCtrlKeyList = nullptr;
    }
}

void SystemData::load(sead::Heap* heap, LayerTable* entity_layer_table,
                      LayerTable* sensor_layer_table, MaterialTable* material_table,
                      ContactInfoTable* contact_info_table) {
    loadLayerTable(heap, entity_layer_table, LayerTableType::Entity);
    loadLayerTable(heap, sensor_layer_table, LayerTableType::Sensor);
    loadMaterialTable(heap, material_table);
    loadSubMaterialTable(heap, material_table);
    loadContactInfoTable(heap, contact_info_table, LayerTableType::Entity);
    loadContactInfoTable(heap, contact_info_table, LayerTableType::Sensor);
    loadCharacterCtrlTable(heap);
    loadRagdollCtrlKeyList(heap);
}

void SystemData::loadMaterialTable(sead::Heap* heap, MaterialTable* table) {
    mMaterialTableHandle = new (heap) res::Handle;
    const auto res = loadMaterialTableRes();
    table->loadMaterialTable(heap, res);
}

void SystemData::loadCharacterCtrlTable(sead::Heap* heap) {
    mCharacterCtrlTable.addList("CharacterControllerTable");

    auto& obj = mCharacterCtrlTable.mTables[0];
    mCharacterCtrlTable.mParamList.addObj(
        &obj, CharacterControllerTable::Type(CharacterControllerTable::Type::Default).text());

    for (int i = 0; i < Material::size(); ++i) {
        const char* material_text = materialToText(i);
        obj.params[i].init(0.0, material_text, material_text, &obj);
    }

    mCharacterCtrlTable.mResHandle = new (heap) res::Handle;
    const auto res = loadCharacterCtrlTableRes();
    mCharacterCtrlTable.mParamIO.applyResParameterArchive(res);
}

void SystemData::loadRagdollCtrlKeyList(sead::Heap* heap) {
    mRagdollCtrlKeyListHandle = new (heap) res::Handle;

    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path = "Physics/System/RagdollControllerKeyList.brgcon";
    auto* res = mRagdollCtrlKeyListHandle->load(path, &request);
    mRagdollCtrlKeyList = sead::DynamicCast<RagdollControllerKeyList>(res);
}

agl::utl::ResParameterArchive
SystemData::loadLayerTableRes(const SystemData::LayerTableInfoContainer& container,
                              SystemData::LayerTableType type) {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path{};
    switch (type) {
    case LayerTableType::Entity:
        path = "Physics/System/EntityLayerTable.bphyslayer";
        break;
    case LayerTableType::Sensor:
        path = "Physics/System/SensorLayerTable.bphyslayer";
        break;
    }
    const auto& resource = *container.mResHandle->load(path, &request);
    auto* direct_resource = sead::DynamicCast<const sead::DirectResource>(&resource);
    return agl::utl::ResParameterArchive{direct_resource->getRawData()};
}

agl::utl::ResParameterArchive SystemData::loadMaterialTableRes() {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path = "Physics/System/PhysicsMaterialTable.bphysmaterial";
    const auto& resource = *mMaterialTableHandle->load(path, &request);
    auto* direct_resource = sead::DynamicCast<const sead::DirectResource>(&resource);
    return agl::utl::ResParameterArchive{direct_resource->getRawData()};
}

agl::utl::ResParameterArchive SystemData::loadSubMaterialTableRes() {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path = "Physics/System/PhysicsSubMaterialTable.bphyssubmat";
    const auto& resource = *mSubMaterialTableHandle->load(path, &request);
    auto* direct_resource = sead::DynamicCast<const sead::DirectResource>(&resource);
    return agl::utl::ResParameterArchive{direct_resource->getRawData()};
}

agl::utl::ResParameterArchive SystemData::loadContactInfoTableRes(SystemData::LayerTableType type) {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path{};
    switch (type) {
    case LayerTableType::Entity:
        path = "Physics/System/EntityContactInfoTable.bphyscontact";
        break;
    case LayerTableType::Sensor:
        path = "Physics/System/SensorContactInfoTable.bphyscontact";
        break;
    }
    /// @bug Possible bug? The request is never used.
    const auto& resource = *mContactInfoTableHandles[int(type)]->load(path, nullptr);
    auto* direct_resource = sead::DynamicCast<const sead::DirectResource>(&resource);
    return agl::utl::ResParameterArchive{direct_resource->getRawData()};
}

agl::utl::ResParameterArchive SystemData::loadCharacterCtrlTableRes() {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path = "Physics/System/CharacterControllerTable.bphyscharcon";
    const auto& resource = *mCharacterCtrlTable.mResHandle->load(path, &request);
    auto* direct_resource = sead::DynamicCast<const sead::DirectResource>(&resource);
    return agl::utl::ResParameterArchive{direct_resource->getRawData()};
}

void LayerTableInfo::postRead_() {
    // FIXME
}

}  // namespace ksys::phys
