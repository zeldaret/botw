#include "KingSystem/Physics/System/physMaterialTable.h"
#include <heap/seadFrameHeap.h>

namespace ksys::phys {

MaterialTable::MaterialTable() = default;

MaterialTable::~MaterialTable() = default;

void MaterialTable::loadMaterialTable(sead::Heap* heap, agl::utl::ResParameterArchive archive) {
    addMaterialTableList("MaterialTable");

    for (int i = 0; i < Material::size(); ++i) {
        const char* material_name = materialToText(i);
        auto& obj = mMaterialTable[i];
        mMaterialTablePList.addObj(&obj, material_name);

        for (int j = 0; j < Material::size(); ++j) {
            const char* target_name = materialToText(j);
            obj.values[j].init(sead::Vector2f::zero, target_name, target_name, &obj);
        }
    }

    mMaterialTablePIO.applyResParameterArchive(archive);
}

void MaterialTable::loadSubMaterialTable(sead::Heap* heap, agl::utl::ResParameterArchive archive) {
    addSubMaterialTableList("SubMaterialTable");

    const auto SubMaterialTable = archive.getRootList().getResParameterList(0);

    auto* str_heap = sead::FrameHeap::create(
        0, "SubMaterialString", heap, 8, sead::Heap::HeapDirection::cHeapDirection_Forward, false);

    for (int i = 0; i < Material::size() && i < SubMaterialTable.getResParameterObjNum(); ++i) {
        const char* material_name = materialToText(i);
        auto& obj = mSubMaterialTable[i];
        mSubMaterialTablePList.addObj(&obj, material_name);
        obj.num_values = SubMaterialTable.getResParameterObj(i).getNum();

        for (int submat = 0; submat < obj.values.size(); ++submat) {
            auto* key = new (str_heap) sead::FormatFixedSafeString<32>("submat_%d", submat);
            obj.values[submat].init(sead::SafeString::cEmptyString, *key, *key, &obj);
        }
    }

    if (archive.getRootList().getResParameterListNum() >= 2) {
        mSubMaterialTablePIO.addList(&mSoundSubMaterialTablePList, "SoundSubMaterialTable");
        for (int i = 0; i < Material::size() && i < SubMaterialTable.getResParameterObjNum(); ++i) {
            const char* material_name = materialToText(i);
            auto& obj = mSoundSubMaterialTable[i];
            mSoundSubMaterialTablePList.addObj(&obj, material_name);
            obj.num_values = SubMaterialTable.getResParameterObj(i).getNum();

            for (int submat = 0; submat < obj.values.size(); ++submat) {
                auto* key = new (str_heap) sead::FormatFixedSafeString<32>("submat_%d", submat);
                obj.values[submat].init(sead::SafeString::cEmptyString, *key, *key, &obj);
            }
        }
    }

    if (archive.getRootList().getResParameterListNum() >= 3) {
        mSubMaterialTablePIO.addList(&mSoundMatchingSubMaterialTablePList,
                                     "SoundMatchingSubMaterialTable");
        const auto list = archive.getRootList().getResParameterList(2);
        for (int i = 0; i < Material::size() && i < list.getResParameterObjNum(); ++i) {
            const char* material_name = materialToText(i);
            auto& obj = mSoundMatchingSubMaterialTable[i];
            mSoundMatchingSubMaterialTablePList.addObj(&obj, material_name);
            obj.num_values = list.getResParameterObj(i).getNum();

            for (int submat = 0; submat < obj.values.size(); ++submat) {
                auto* key = new (str_heap) sead::FormatFixedSafeString<32>("submat_%d", submat);
                obj.values[submat].init(sead::SafeString::cEmptyString, *key, *key, &obj);
            }
        }
    }

    str_heap->adjust();
    mSubMaterialTablePIO.applyResParameterArchive(archive);
}

const sead::SafeString& MaterialTable::getSubMaterial(Material material, int submat_idx) const {
    return mSubMaterialTable[material].values[submat_idx].ref();
}

const sead::SafeString& MaterialTable::getSoundMatchingSubMaterial(Material material,
                                                                   int submat_idx) const {
    return mSoundMatchingSubMaterialTable[material].values[submat_idx].ref();
}

static int getSubMaterialIdx_(const MaterialTable::SubValues& table, Material material,
                              const sead::SafeString& submat_name) {
    for (int i = 0; i < table.num_values; ++i) {
        if (submat_name == table.values[i].ref())
            return i;
    }

    if (submat_name == sead::SafeString::cEmptyString)
        return 0;

    return -1;
}

int MaterialTable::getSubMaterialIdx(Material material, const sead::SafeString& submat_name) const {
    const auto& table = mSubMaterialTable[material];
    return getSubMaterialIdx_(table, material, submat_name);
}

int MaterialTable::getSoundSubMaterialIdx(Material material,
                                          const sead::SafeString& submat_name) const {
    const auto& table = mSoundSubMaterialTable[material];
    return getSubMaterialIdx_(table, material, submat_name);
}

int MaterialTable::getNumSubMaterials(Material material) const {
    return mSubMaterialTable[material].num_values;
}

bool MaterialTable::subMaterialHasSound(Material material, int submat_idx) const {
    return getSoundSubMaterialIdx(material, getSubMaterial(material, submat_idx)) != -1;
}

}  // namespace ksys::phys
