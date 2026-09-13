#pragma once

#include "KingSystem/ActorSystem/actAiAi.h"

namespace uking::ai {

class MergedDungeonPartsRoot : public ksys::act::ai::Ai {
    SEAD_RTTI_OVERRIDE(MergedDungeonPartsRoot, ksys::act::ai::Ai)
public:
    explicit MergedDungeonPartsRoot(const InitArg& arg);
    ~MergedDungeonPartsRoot() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    // map_unit_param at offset 0x38
    const sead::Vector3f* mTransFieldBodyGroup00_m{};
    // map_unit_param at offset 0x40
    const sead::Vector3f* mRotateFieldBodyGroup00_m{};
    // map_unit_param at offset 0x48
    const sead::Vector3f* mTransFieldBodyGroup01_m{};
    // map_unit_param at offset 0x50
    const sead::Vector3f* mRotateFieldBodyGroup01_m{};
    // map_unit_param at offset 0x58
    const sead::Vector3f* mTransFieldBodyGroup02_m{};
    // map_unit_param at offset 0x60
    const sead::Vector3f* mRotateFieldBodyGroup02_m{};
    // map_unit_param at offset 0x68
    const sead::Vector3f* mTransFieldBodyGroup03_m{};
    // map_unit_param at offset 0x70
    const sead::Vector3f* mRotateFieldBodyGroup03_m{};
    // map_unit_param at offset 0x78
    const sead::Vector3f* mTransFieldBodyGroup04_m{};
    // map_unit_param at offset 0x80
    const sead::Vector3f* mRotateFieldBodyGroup04_m{};
    // map_unit_param at offset 0x88
    const sead::Vector3f* mTransFieldBodyGroup05_m{};
    // map_unit_param at offset 0x90
    const sead::Vector3f* mRotateFieldBodyGroup05_m{};
    // map_unit_param at offset 0x98
    const sead::Vector3f* mTransFieldBodyGroup06_m{};
    // map_unit_param at offset 0xa0
    const sead::Vector3f* mRotateFieldBodyGroup06_m{};
    // map_unit_param at offset 0xa8
    const sead::Vector3f* mTransFieldBodyGroup07_m{};
    // map_unit_param at offset 0xb0
    const sead::Vector3f* mRotateFieldBodyGroup07_m{};
    // map_unit_param at offset 0xb8
    const sead::Vector3f* mTransFieldBodyGroup08_m{};
    // map_unit_param at offset 0xc0
    const sead::Vector3f* mRotateFieldBodyGroup08_m{};
    // map_unit_param at offset 0xc8
    const sead::Vector3f* mTransFieldBodyGroup09_m{};
    // map_unit_param at offset 0xd0
    const sead::Vector3f* mRotateFieldBodyGroup09_m{};
    // map_unit_param at offset 0xd8
    const sead::Vector3f* mTransFieldBodyGroup10_m{};
    // map_unit_param at offset 0xe0
    const sead::Vector3f* mRotateFieldBodyGroup10_m{};
    // map_unit_param at offset 0xe8
    const sead::Vector3f* mTransFieldBodyGroup11_m{};
    // map_unit_param at offset 0xf0
    const sead::Vector3f* mRotateFieldBodyGroup11_m{};
    // map_unit_param at offset 0xf8
    const sead::Vector3f* mTransFieldBodyGroup12_m{};
    // map_unit_param at offset 0x100
    const sead::Vector3f* mRotateFieldBodyGroup12_m{};
    // map_unit_param at offset 0x108
    const sead::Vector3f* mTransFieldBodyGroup13_m{};
    // map_unit_param at offset 0x110
    const sead::Vector3f* mRotateFieldBodyGroup13_m{};
    // map_unit_param at offset 0x118
    const sead::Vector3f* mTransFieldBodyGroup14_m{};
    // map_unit_param at offset 0x120
    const sead::Vector3f* mRotateFieldBodyGroup14_m{};
    // map_unit_param at offset 0x128
    const sead::Vector3f* mTransFieldBodyGroup15_m{};
    // map_unit_param at offset 0x130
    const sead::Vector3f* mRotateFieldBodyGroup15_m{};
};

}  // namespace uking::ai
