/**
 * @file Pane.h
 * @brief Base UI panel.
 */

#pragma once

#include "sead/runtime.h"  //FIXME this definitely is wrong
#include "types.h"

namespace nn {
namespace ui2d {
class AnimTransform;
class Layout;

class Pane {
public:
    Pane();
    Pane(nn::ui2d::Pane const&);

    virtual ~Pane();

    virtual sead::RuntimeTypeInfo::Interface* GetRuntimeTypeInfo() const;
    virtual s32 GetVertexColor(s32);
    virtual u8 GetColorElement(s32);
    virtual void SetColorElement(u32, u8);
    virtual u8 GetVertexColorElement(s32);
    virtual void SetVertexColorElement(u32, u8);
    virtual u32 GetMaterialCount() const;
    virtual u64* GetMaterial(s32) const;

    virtual void BindAnimation(nn::ui2d::AnimTransform*, bool, bool);
    virtual void UnbindAnimation(nn::ui2d::AnimTransform*, bool);

    void Initialize();
    void SetName(char const*);
    void SetUserData(char const*);
    void AppendChild(nn::ui2d::Pane*);
    void PrependChild(nn::ui2d::Pane*);
    void InsertChild(nn::ui2d::Pane*, nn::ui2d::Pane*);
    void RemoveChild(nn::ui2d::Pane*);
    void GetVertexPos() const;

    u64 _8;
    u64 _10;
    u64 _18;
    u64 _20;
    u64 _28;
    u64 _30;
    u64 _38;
    u64 _40;
    u32 _48;
    u32 _4C;
    u64 _50;
    u16 _58;
    u16 _5A;
    u32 _5C;
    u64 _60;
    nn::ui2d::Layout* mLayout;  // _68
    u128 _70;
    u128 _80;
    u128 _90;
    u64 _A0;
    u64 _A8;
    u64 _B0;
    u64 _B8;
    u64 _C0;
    u64 _C8;
    u64 _D0;
    u16 _D8;
    u16 _DA;
    u32 _DC;
};
};  // namespace ui2d
};  // namespace nn