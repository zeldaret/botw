#pragma once

#include <agl/Utils/aglParameter.h>
#include <agl/Utils/aglParameterIO.h>
#include <agl/Utils/aglParameterList.h>
#include <agl/Utils/aglParameterObj.h>
#include <hostio/seadHostIONode.h>
#include "KingSystem/Utils/Types.h"

namespace ksys::chm {

class IShape {
public:
    virtual const sead::SafeString& getResTypeId() const = 0;
    virtual const sead::SafeString& getName() const = 0;
    virtual float getVolumeOccupancy() const = 0;
    virtual float getElementOcclusion() const = 0;
};

class Shape : public agl::utl::IParameterObj,
              public agl::utl::IParameterIO,
              public sead::hostio::Node,
              public IShape {
public:
    Shape();
    ~Shape() override;

    const sead::SafeString& getResTypeId() const override { return res_type_id.ref(); }
    const sead::SafeString& getName() const override { return name.ref(); }
    float getVolumeOccupancy() const override { return volume_occupancy.ref(); }
    float getElementOcclusion() const override { return element_occlusion.ref(); }

private:
    agl::utl::Parameter<sead::FixedSafeString<32>> name;
    agl::utl::Parameter<sead::FixedSafeString<32>> res_type_id;
    agl::utl::Parameter<float> volume_occupancy;
    agl::utl::Parameter<float> element_occlusion;
};
KSYS_CHECK_SIZE_NX150(Shape, 0x2f0);

}  // namespace ksys::chm
