#include "KingSystem/Utils/MathUtil.h"

namespace ksys::util {

void calcMatrixFromZAxis(sead::Matrix34f* result, const sead::Vector3f& z_axis,
                         const sead::Vector3f& up_reference, const sead::Vector3f& translation) {
    sead::Vector3f x_axis;
    x_axis.setCross(up_reference, z_axis);
    x_axis.normalize();

    sead::Vector3f y_axis;
    y_axis.setCross(z_axis, x_axis);
    y_axis.normalize();

    result->setBase(0, x_axis);
    result->setBase(1, y_axis);
    result->setBase(2, z_axis);
    result->setTranslation(translation);
}

}  // namespace ksys::util
