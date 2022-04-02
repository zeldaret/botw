#pragma once

#include <agl/utl/aglParameter.h>
#include <agl/utl/aglParameterIO.h>
#include <agl/utl/aglParameterList.h>
#include <agl/utl/aglParameterObj.h>
#include <agl/utl/aglResParameter.h>
#include <container/seadSafeArray.h>
#include "KingSystem/Physics/physDefines.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::phys {

class MaterialTable {
public:
    /// Properties for interactions between two materials.
    struct MaterialPairProperties {
        float friction;
        float restitution;
    };

    /// Parameter object that stores an entire row of InteractionProperties.
    struct Values : agl::utl::IParameterObj {
        sead::SafeArray<agl::utl::Parameter<sead::Vector2f>, Material::size()> values;
    };
    KSYS_CHECK_SIZE_NX150(Values, 0x4b0);

    struct SubValues : agl::utl::IParameterObj {
        sead::SafeArray<agl::utl::Parameter<sead::FixedSafeString<32>>, 12> values;
        int num_values;
    };
    KSYS_CHECK_SIZE_NX150(SubValues, 0x3f8);

    MaterialTable();
    virtual ~MaterialTable();

    void loadMaterialTable(sead::Heap* heap, agl::utl::ResParameterArchive archive);
    void loadSubMaterialTable(sead::Heap* heap, agl::utl::ResParameterArchive archive);

    MaterialPairProperties getPairProperties(Material mat_a, Material mat_b) const {
        auto& vec = mMaterialTable[mat_a].values[mat_b];
        return {vec->x, vec->y};
    }

    const sead::SafeString& getSubMaterial(Material material, int submat_idx) const;
    const sead::SafeString& getSoundMatchingSubMaterial(Material material, int submat_idx) const;

    int getSubMaterialIdx(Material material, const sead::SafeString& submat_name) const;
    int getSoundSubMaterialIdx(Material material, const sead::SafeString& submat_name) const;

    int getNumSubMaterials(Material material) const;
    bool subMaterialHasSound(Material material, int submat_idx) const;

private:
    void addMaterialTableList(const char* name) {
        mMaterialTablePIO.addList(&mMaterialTablePList, name);
    }

    void addSubMaterialTableList(const char* name) {
        mSubMaterialTablePIO.addList(&mSubMaterialTablePList, name);
    }

    agl::utl::IParameterIO mMaterialTablePIO;
    agl::utl::ParameterList mMaterialTablePList;
    sead::SafeArray<Values, Material::size()> mMaterialTable;

    agl::utl::IParameterIO mSubMaterialTablePIO;
    agl::utl::ParameterList mSubMaterialTablePList;
    sead::SafeArray<SubValues, Material::size()> mSubMaterialTable;

    agl::utl::ParameterList mSoundSubMaterialTablePList;
    sead::SafeArray<SubValues, Material::size()> mSoundSubMaterialTable;

    agl::utl::ParameterList mSoundMatchingSubMaterialTablePList;
    sead::SafeArray<SubValues, Material::size()> mSoundMatchingSubMaterialTable;
};
KSYS_CHECK_SIZE_NX150(MaterialTable, 0x25a28);

}  // namespace ksys::phys
