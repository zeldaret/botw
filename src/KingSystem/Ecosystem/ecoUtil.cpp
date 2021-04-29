#include "KingSystem/Ecosystem/ecoUtil.h"

namespace ksys::eco {

bool currentAreaNumIs64(const sead::Vector3f& pos) {
    return Ecosystem::instance()->getFieldMapArea(pos.x, pos.z) == 64;
}

}  // namespace ksys::eco
