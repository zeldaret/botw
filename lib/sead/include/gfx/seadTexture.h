#ifndef SEAD_TEXTURE_H_
#define SEAD_TEXTURE_H_

#include <basis/seadTypes.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead
{
class Texture
{
    SEAD_RTTI_BASE(Texture)

public:
    Texture() {}
    virtual ~Texture() {}

    virtual u32 getWidth() const = 0;
    virtual u32 getHeight() const = 0;
};

}  // namespace sead

#endif  // SEAD_TEXTURE_H_
