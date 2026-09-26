#include "KingSystem/Utils/MathUtil.h"

namespace ksys::util {

void makeMtxFrontUpPos(sead::Matrix34f* result, const sead::Vector3f& front,
                       const sead::Vector3f& up, const sead::Vector3f& pos) {
    sead::Vector3f x_axis;
    x_axis.setCross(up, front);
    x_axis.normalize();

    sead::Vector3f y_axis;
    y_axis.setCross(front, x_axis);
    y_axis.normalize();

    result->setBase(0, x_axis);
    result->setBase(1, y_axis);
    result->setBase(2, front);
    result->setTranslation(pos);
}

}  // namespace ksys::util
