/**
 * @file Parts.h
 * @brief Layout parts.
 */

#pragma once

#include <nn/ui2d/Pane.h>

namespace nn {
namespace ui2d {
struct BuildArgSet;
struct ResParts;

class Parts : nn::ui2d::Pane {
public:
    Parts();
    Parts(nn::ui2d::ResParts const*, nn::ui2d::ResParts const*, nn::ui2d::BuildArgSet const&);
    Parts(nn::ui2d::Parts const&);

    virtual ~Parts();
    virtual sead::RuntimeTypeInfo::Interface* GetRuntimeTypeInfo() const;

    u64 _E0;
    u64 _E8;
    u32 _F0;
};
};  // namespace ui2d
};  // namespace nn