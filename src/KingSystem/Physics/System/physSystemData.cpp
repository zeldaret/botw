#include "KingSystem/Physics/System/physSystemData.h"
#include "KingSystem/Physics/Ragdoll/physRagdollControllerKeyList.h"
#include "KingSystem/Physics/System/physContactMgr.h"
#include "KingSystem/Physics/System/physGroupFilter.h"
#include "KingSystem/Physics/System/physMaterialTable.h"
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

    deleteAndNull(mLayerMatrices[0].mResHandle);
    deleteAndNull(mContactInfoTableHandles[0]);

    deleteAndNull(mLayerMatrices[1].mResHandle);
    deleteAndNull(mContactInfoTableHandles[1]);

    deleteAndNull(mCharacterCtrlTable.mResHandle);

    if (auto*& handle = mRagdollCtrlKeyListHandle) {
        delete handle;
        handle = nullptr;
        mRagdollCtrlKeyList = nullptr;
    }
}

void SystemData::load(sead::Heap* heap, GroupFilter* entity_group_filter,
                      GroupFilter* sensor_group_filter, MaterialTable* material_table,
                      ContactMgr* contact_mgr) {
    loadLayerTable(heap, entity_group_filter, ContactLayerType::Entity);
    loadLayerTable(heap, sensor_group_filter, ContactLayerType::Sensor);
    loadMaterialTable(heap, material_table);
    loadSubMaterialTable(heap, material_table);
    loadContactInfoTable(heap, contact_mgr, ContactLayerType::Entity);
    loadContactInfoTable(heap, contact_mgr, ContactLayerType::Sensor);
    loadCharacterCtrlTable(heap);
    loadRagdollCtrlKeyList(heap);
}

void SystemData::loadLayerTable(sead::Heap* heap, GroupFilter* filter, ContactLayerType type) {
    auto& matrix = mLayerMatrices[int(type)];
    matrix.addList("LayerTable");

    const int first = filter->getLayerFirst();
    const int last = filter->getLayerLast();
    const int num_layers = 1 + last - first;

    for (int i = 0; i < num_layers; ++i) {
        auto& table = matrix.mTables[i];
        const ContactLayer layer = first + i;
        table.num_layers = num_layers;
        table.filter = filter;
        table.layer = layer;

        matrix.mParamList.addObj(&table, contactLayerToText(layer));

        for (int j = 0; j < num_layers; ++j) {
            const char* other_layer_name = contactLayerToText(first + j);
            table.layer_values[j].init(0, other_layer_name, other_layer_name, &table);
        }
    }

    matrix.mResHandle = new (heap) res::Handle;
    const auto res = loadLayerTableRes(matrix, type);
    matrix.mParamIO.applyResParameterArchive(res);
}

void SystemData::loadMaterialTable(sead::Heap* heap, MaterialTable* table) {
    mMaterialTableHandle = new (heap) res::Handle;
    const auto res = loadMaterialTableRes();
    table->loadMaterialTable(heap, res);
}

void SystemData::loadSubMaterialTable(sead::Heap* heap, MaterialTable* table) {
    mSubMaterialTableHandle = new (heap) res::Handle;
    const auto res = loadSubMaterialTableRes();
    table->loadSubMaterialTable(heap, res);
}

void SystemData::loadContactInfoTable(sead::Heap* heap, ContactMgr* mgr, ContactLayerType type) {
    mContactInfoTableHandles[int(type)] = new (heap) res::Handle;
    const auto res = loadContactInfoTableRes(type);
    mgr->loadContactInfoTable(heap, res, type);
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

agl::utl::ResParameterArchive SystemData::loadLayerTableRes(const SystemData::LayerMatrix& matrix,
                                                            ContactLayerType type) {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path{};
    switch (type) {
    case ContactLayerType::Entity:
        path = "Physics/System/EntityLayerTable.bphyslayer";
        break;
    case ContactLayerType::Sensor:
        path = "Physics/System/SensorLayerTable.bphyslayer";
        break;
    case ContactLayerType::Invalid:
        break;
    }
    const auto& resource = *matrix.mResHandle->load(path, &request);
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

agl::utl::ResParameterArchive SystemData::loadContactInfoTableRes(ContactLayerType type) {
    res::LoadRequest request;
    request.mRequester = "physSystemData";
    const char* path{};
    switch (type) {
    case ContactLayerType::Entity:
        path = "Physics/System/EntityContactInfoTable.bphyscontact";
        break;
    case ContactLayerType::Sensor:
        path = "Physics/System/SensorContactInfoTable.bphyscontact";
        break;
    case ContactLayerType::Invalid:
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

void LayerTable::postRead_() {
    u32 collision_mask = 0;
    u32 custom_mask = 0;

    for (int i = 0; i < num_layers; ++i) {
        const int value = layer_values[i].ref();
        if (value & 1)
            collision_mask |= 1 << i;
        if (value & 2)
            custom_mask |= 1 << i;
    }

    filter->setLayerCollisionEnabledMask(layer, collision_mask);
    filter->setLayerCustomMask(layer, custom_mask);
}

}  // namespace ksys::phys
