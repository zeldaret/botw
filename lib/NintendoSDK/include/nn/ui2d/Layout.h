/**
 * @file Layout.h
 * @brief UI Layout implementation.
 */

#pragma once

#include <nn/types.h>

namespace nn {
namespace ui2d {
class AnimTransform;
class Pane;

class Layout {
public:
    Layout();

    virtual ~Layout();

    virtual void DeleteAnimTransform(nn::ui2d::AnimTransform*);
    virtual void BindAnimation(nn::ui2d::AnimTransform*);
    virtual void UnbindAnimation(nn::ui2d::AnimTransform*);
    virtual void UnbindAnimation(nn::ui2d::Pane*);
    virtual void UnbindAllAnimation();

    virtual void Animate();
    virtual void UpdateAnimFrame(f32 frame);
    virtual void AnimateAndUpdateAnimFrame(f32 frame);

    void SetAllocator(void* (*)(u64, u64, void*), void (*)(void*, void*), void*);
    void AllocateMemory(u64, u64);
    void AllocateMemory(u64);
    void FreeMemory(void* src);

    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    u64 _30;

    u64 _40;
    u64 _48;
    u64 _50;
    u64 _58;
    u64 _60;
};
};  // namespace ui2d
};  // namespace nn