#pragma once

#include "KingSystem/ActorSystem/actAiAction.h"

namespace uking::action {

class ItemAmiiboSelectDropTable : public ksys::act::ai::Action {
    SEAD_RTTI_OVERRIDE(ItemAmiiboSelectDropTable, ksys::act::ai::Action)
public:
    explicit ItemAmiiboSelectDropTable(const InitArg& arg);
    ~ItemAmiiboSelectDropTable() override;

    bool init_(sead::Heap* heap) override;
    void enter_(ksys::act::ai::InlineParamPack* params) override;
    void leave_() override;
    void loadParams_() override;

protected:
    void calc_() override;

    // static_param at offset 0x20
    sead::SafeString mTableCommon_s{};
    // static_param at offset 0x30
    sead::SafeString mTableGanondorf_s{};
    // static_param at offset 0x40
    sead::SafeString mTableToonLink_s{};
    // static_param at offset 0x50
    sead::SafeString mTableSheik_s{};
    // static_param at offset 0x60
    sead::SafeString mTableLink_s{};
    // static_param at offset 0x70
    sead::SafeString mTableZelda_s{};
    // static_param at offset 0x80
    sead::SafeString mTableWolfLink_s{};
    // static_param at offset 0x90
    sead::SafeString mTableGuardian_s{};
    // static_param at offset 0xa0
    sead::SafeString mTableBokoblin_s{};
    // static_param at offset 0xb0
    sead::SafeString mTableCross_Ganondorf_s{};
    // static_param at offset 0xc0
    sead::SafeString mTableCross_ToonLink_s{};
    // static_param at offset 0xd0
    sead::SafeString mTableCross_Sheik_s{};
    // static_param at offset 0xe0
    sead::SafeString mTableCross_Link_s{};
    // static_param at offset 0xf0
    sead::SafeString mTableCross_Zelda_s{};
    // static_param at offset 0x100
    sead::SafeString mTableKing_WolfLink_s{};
    // static_param at offset 0x110
    sead::SafeString mTableKing_Link_Bow_s{};
    // static_param at offset 0x120
    sead::SafeString mTableKing_Link_Horse_s{};
    // static_param at offset 0x130
    sead::SafeString mTableKing_Zelda_Doctor_s{};
    // static_param at offset 0x140
    sead::SafeString mTableKing_Guardian_s{};
    // static_param at offset 0x150
    sead::SafeString mTableKing_Bokoblin_s{};
    // static_param at offset 0x160
    sead::SafeString mTableKing30th_Link_Ocarina_s{};
    // static_param at offset 0x170
    sead::SafeString mTableKing30th_Link_Majora_s{};
    // static_param at offset 0x180
    sead::SafeString mTableKing30th_Link_Takt_s{};
    // static_param at offset 0x190
    sead::SafeString mTableKing30th_Zelda_Takt_s{};
    // static_param at offset 0x1a0
    sead::SafeString mTableKing30th_Link_Twilight_s{};
    // static_param at offset 0x1b0
    sead::SafeString mTableKing30th_Link_Skyward_s{};
    // static_param at offset 0x1c0
    sead::SafeString mTableKing30th_Link_Dot_s{};
    // map_unit_param at offset 0x1d0
    const int* mAmiiboCharacterId_m{};
    // map_unit_param at offset 0x1d8
    const int* mAmiiboNumberingId_m{};
};

}  // namespace uking::action
