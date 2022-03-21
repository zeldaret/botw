#ifndef SEAD_TEXTURE_CAFE_GX2_H_
#define SEAD_TEXTURE_CAFE_GX2_H_

#include <cafe.h>

#include <basis/seadTypes.h>
#include <gfx/seadTexture.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead
{
class TextureCafeGX2 : public Texture
{
    SEAD_RTTI_OVERRIDE(TextureCafeGX2, Texture)

public:
    TextureCafeGX2() {}
    virtual ~TextureCafeGX2() {}

    virtual u32 getWidth() const;
    virtual u32 getHeight() const;

    GX2Texture* mGX2Texture;
};

}  // namespace sead

#endif  // SEAD_TEXTURE_CAFE_GX2_H_
