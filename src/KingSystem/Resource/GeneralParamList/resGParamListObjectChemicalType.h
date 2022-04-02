#pragma once

#include <agl/utl/aglParameter.h>
#include "KingSystem/Resource/GeneralParamList/resGParamListObject.h"
#include "KingSystem/Utils/Types.h"

namespace ksys::res {

class GParamListObjectChemicalType : public GParamListObject {
public:
    GParamListObjectChemicalType() {
        auto* const obj = &mObj;

        mChemicalType.init("Normal", "ChemicalType", "", obj);
        mEmitChemicalActor.init("", "EmitChemicalActor", "", obj);
    }

    const char* getName() const override { return "ChemicalType"; }

    agl::utl::Parameter<sead::SafeString> mChemicalType;
    agl::utl::Parameter<sead::SafeString> mEmitChemicalActor;
};
KSYS_CHECK_SIZE_NX150(GParamListObjectChemicalType, 0x88);

}  // namespace ksys::res
