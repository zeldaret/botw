/**
 * @file Material.h
 * @brief UI Material implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace ui2d {
class AnimTransform;
class BuildResultInformation;
struct UserShaderInformation;

class Material {
public:
    Material();

    void Initialize();
    void ReserveMem(s32, s32, s32, s32, bool, s32, bool, s32, bool, bool);
    void SetupUserShaderConstantBufferInformation(nn::ui2d::UserShaderInformation const&);

    virtual ~Material();
    virtual void BindAnimation(nn::ui2d::AnimTransform*);
    virtual void UnbindAnimation(nn::ui2d::AnimTransform*);
};
};  // namespace ui2d
};  // namespace nn