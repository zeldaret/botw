#include "Game/AI/Action/actionItemAmiiboSelectDropTable.h"

namespace uking::action {

ItemAmiiboSelectDropTable::ItemAmiiboSelectDropTable(const InitArg& arg)
    : ksys::act::ai::Action(arg) {}

ItemAmiiboSelectDropTable::~ItemAmiiboSelectDropTable() = default;

bool ItemAmiiboSelectDropTable::init_(sead::Heap* heap) {
    return ksys::act::ai::Action::init_(heap);
}

void ItemAmiiboSelectDropTable::enter_(ksys::act::ai::InlineParamPack* params) {
    ksys::act::ai::Action::enter_(params);
}

void ItemAmiiboSelectDropTable::leave_() {
    ksys::act::ai::Action::leave_();
}

void ItemAmiiboSelectDropTable::loadParams_() {
    getStaticParam(&mTableCommon_s, "TableCommon");
    getStaticParam(&mTableGanondorf_s, "TableGanondorf");
    getStaticParam(&mTableToonLink_s, "TableToonLink");
    getStaticParam(&mTableSheik_s, "TableSheik");
    getStaticParam(&mTableLink_s, "TableLink");
    getStaticParam(&mTableZelda_s, "TableZelda");
    getStaticParam(&mTableWolfLink_s, "TableWolfLink");
    getStaticParam(&mTableGuardian_s, "TableGuardian");
    getStaticParam(&mTableBokoblin_s, "TableBokoblin");
    getStaticParam(&mTableCross_Ganondorf_s, "TableCross_Ganondorf");
    getStaticParam(&mTableCross_ToonLink_s, "TableCross_ToonLink");
    getStaticParam(&mTableCross_Sheik_s, "TableCross_Sheik");
    getStaticParam(&mTableCross_Link_s, "TableCross_Link");
    getStaticParam(&mTableCross_Zelda_s, "TableCross_Zelda");
    getStaticParam(&mTableKing_WolfLink_s, "TableKing_WolfLink");
    getStaticParam(&mTableKing_Link_Bow_s, "TableKing_Link_Bow");
    getStaticParam(&mTableKing_Link_Horse_s, "TableKing_Link_Horse");
    getStaticParam(&mTableKing_Zelda_Doctor_s, "TableKing_Zelda_Doctor");
    getStaticParam(&mTableKing_Guardian_s, "TableKing_Guardian");
    getStaticParam(&mTableKing_Bokoblin_s, "TableKing_Bokoblin");
    getStaticParam(&mTableKing30th_Link_Ocarina_s, "TableKing30th_Link_Ocarina");
    getStaticParam(&mTableKing30th_Link_Majora_s, "TableKing30th_Link_Majora");
    getStaticParam(&mTableKing30th_Link_Takt_s, "TableKing30th_Link_Takt");
    getStaticParam(&mTableKing30th_Zelda_Takt_s, "TableKing30th_Zelda_Takt");
    getStaticParam(&mTableKing30th_Link_Twilight_s, "TableKing30th_Link_Twilight");
    getStaticParam(&mTableKing30th_Link_Skyward_s, "TableKing30th_Link_Skyward");
    getStaticParam(&mTableKing30th_Link_Dot_s, "TableKing30th_Link_Dot");
    getMapUnitParam(&mAmiiboCharacterId_m, "AmiiboCharacterId");
    getMapUnitParam(&mAmiiboNumberingId_m, "AmiiboNumberingId");
}

void ItemAmiiboSelectDropTable::calc_() {
    ksys::act::ai::Action::calc_();
}

}  // namespace uking::action
