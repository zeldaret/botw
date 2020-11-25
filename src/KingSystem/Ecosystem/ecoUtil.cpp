#include "KingSystem/Ecosystem/ecoUtil.h"

namespace ksys::eco {

bool currentAreaNumIs64(const sead::Vector3f& pos) {
    return Ecosystem::instance()->getCurrentAreaNum(&Ecosystem::instance()->mFieldMapArea, pos.x,
                                                    pos.z) == 64;
}

}  // namespace ksys::eco
