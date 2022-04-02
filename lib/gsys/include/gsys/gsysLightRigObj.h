#pragma once

#include <agl/env/aglEnvObj.h>

namespace gsys {

class MaskedSpotLight;
class PointLight;
class SpotLight;

// TODO
template <typename T>
class LightRigObj {
public:
    static const agl::env::TypeInfo* sTypeInfo;
};

extern template class LightRigObj<MaskedSpotLight>;
extern template class LightRigObj<PointLight>;
extern template class LightRigObj<SpotLight>;

}  // namespace gsys
