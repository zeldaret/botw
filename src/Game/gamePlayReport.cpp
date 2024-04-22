#include "Game/gamePlayReport.h"
#include <math/seadVector.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Quest/qstQuest.h"
#include "KingSystem/System/ProductReporter.h"
#include "KingSystem/System/StageInfo.h"

namespace uking {

int convertPositionToInt(const sead::Vector2i& pos);

void reportKorok(const sead::Vector3f& position) {
    ksys::ProductReporter::getSomeBool();
    s32 id = ksys::gdt::getFlag_HiddenKorok_Number();

    PlayReport report(sead::SafeString("korok"), 7,
                      ksys::PlayReportMgr::instance()->getReporter()->getHeap());

    report.addMapType();
    report.add(sead::SafeString("Id"), u32(id));

    report.addPlayTimes();
    report.addPosition({position.x, position.z});

    if (ksys::PlayReportMgr::instance()) {
        auto* reporter = ksys::PlayReportMgr::instance()->getReporter();
        if (reporter && reporter->isEnabled())
            reporter->saveReport(&report);
    }
}

void reportDungeon(const sead::SafeString& name, const sead::SafeString& event) {
    ksys::ProductReporter::getSomeBool();
    if (name.findIndex("Remains") == -1 && name.findIndex("Dungeon") == -1 &&
        name.findIndex("FinalTrial") == -1)
        return;

    PlayReport report(sead::SafeString("dungeon"), 6,
                      ksys::PlayReportMgr::instance()->getReporter()->getHeap());

    report.addMapType();

    report.add(sead::SafeString("Name"), name);
    report.add(sead::SafeString("Event"), event);

    report.addPlayTimes();

    if (ksys::PlayReportMgr::instance()) {
        auto* reporter = ksys::PlayReportMgr::instance()->getReporter();
        if (reporter && reporter->isEnabled())
            reporter->saveReport(&report);
    }
}

unsigned int getQuestId(const sead::SafeString& quest_name) {
    const sead::SafeString names[] = {
        "UnknownEvent",
        "Animal_Forest",
        "BloodyMoonRelief",
        "Bottle_Mes",
        "Carnivorous_Boy",
        "CarryingBlueFireEXMini",
        "Cliff_Maze",
        "CompleteDungeon",
        "CursedStatue",
        "DarkWoods",
        "Desert_Maze",
        "DokuroEye",
        "DontDamageFlower",
        "Drag_Hero",
        "Electric_Relic",
        "FairyFountain",
        "FindDungeon",
        "Find_4Relic",
        "Find_Impa",
        "Fire_Relic",
        "FironeMini_GiantHorse",
        "FironeMini_HeartPond",
        "FironeMini_HorseEnemy",
        "FironeMini_TerribleThunder",
        "FirstOhenro",
        "FirstTower",
        "FourJewel",
        "Gaman",
        "GanonQuest",
        "GerudoMiniJewel",
        "Gerudo_CarryIce",
        "Gerudo_CarryIce_mini",
        "Gerudo_Ch_FindingValetta",
        "Gerudo_Ch_Helmet",
        "Gerudo_Ch_Poison",
        "Gerudo_Ch_SandWarm",
        "Gerudo_Ch_SecretClub",
        "Gerudo_Ch_SnowBoots",
        "Gerudo_Ch_SnowMT",
        "Gerudo_HorseBuyer",
        "Gerudo_tsukamidake",
        "Get_MasterSword",
        "Giant_ZoraMini",
        "GodTree",
        "GoronCamp",
        "GoronCamp_mini",
        "GoronCityMini_BeatGolem",
        "GoronMini_ImportGem",
        "GoronMini_WallCrackTBox",
        "GoronsRock",
        "GotoZoraVillage",
        "HateeluMini_Treasure",
        "HatenoMini_BlueFire",
        "HatenoMini_CameraBoy",
        "HatenoMini_DevilSeal",
        "HatenoMini_GoatThief",
        "HatenoMini_LoveInsects",
        "HatenoMini_MyHome",
        "HatenoMini_ThreeTree",
        "HatenoMini_WeaponMania",
        "HatenoMini_WhiteDragon",
        "Hateno_SheikPad_PowerUp",
        "HigakkareMini_RedDragon",
        "HigakkareMini_StrangeMan",
        "HutagoHatago_Ch_001",
        "HyruleDepthMini_WhiteHorse",
        "HyrulePlainMini_Balloon",
        "isso_treasure_mini",
        "Kakariko_Cha_001",
        "Kakariko_Cha_003",
        "Kakariko_Ch_004",
        "Kakariko_Ch_005",
        "Kakariko_Ch_006",
        "Kakariko_Ch_Cooking2",
        "Kakariko_Ch_Cooking3",
        "Kakariko_Ch_Cooking4",
        "KnightDoll",
        "KorokMini_KorokShiren",
        "KorokMini_RiddleShiren",
        "KorokMini_RodShiren",
        "KorokMini_UMAShiren",
        "MacuseIseki",
        "MagneticFld",
        "MarittaMini_BigWhales",
        "MinakkareMini_Dragonfly",
        "MinamihateeluMini_touzoku",
        "MiniGame_Bowling",
        "MiniGame_Crosscountry",
        "MiniGame_GambleTreasureBox",
        "MiniGame_HillTower_BirdMan",
        "MiniGame_HorsebackArchery",
        "MiniGame_HorseRace",
        "MiniGame_KitakkareBF",
        "MiniGame_ParasailArchery",
        "MiniGame_ParasailRide",
        "MiniGame_ShieldSurfing",
        "MiniGame_SmashGolf",
        "MiniGame_TimeLimitHunting",
        "MouthofDragon",
        "MtMotelMini_Landscape",
        "My_Hero",
        "NakedIsland",
        "Oasis_Drug_Challenge",
        "OldKorok_Help",
        "OneHundred",
        "PictureMemory",
        "PrezentationOkamura",
        "Relief_Landing",
        "Remains_Fancier",
        "RinelSearch",
        "RitoMini_Cook",
        "RitoMini_Flint",
        "RitoMini_IceGolem",
        "RitoRabitMountain",
        "RitoSongMystery",
        "RitoUmayadoMini_HotRecipe",
        "Rito_BrosRock",
        "Rito_KeelSearch",
        "RiversideMini_CastleWeapon",
        "RiversideMini_RoyalRecipe",
        "SandStorm",
        "SanrokuMini_Lizard",
        "SearchStone",
        "SecretofObject",
        "SeekerEye",
        "SetugenUmayadoMini_Umahonephoto",
        "Shadow_Sign",
        "ShieldofKolog",
        "ShieldofKolog_mini",
        "Solitary_Maze",
        "StatueofZora",
        "StolenBook",
        "SunazarashiRace",
        "SunazarashiRace_mini",
        "TabantaBridgeMini_Sundial",
        "Threebros_giant",
        "Thunder_Sword",
        "TutorialDungeon",
        "TwoWheels",
        "UMiiMini_GiveCake",
        "UMiiMini_MakeVillage",
        "UMiiMini_RichmansHobby",
        "UotoriMini_RecipeSea",
        "UotoriMini_RecoverBay",
        "UotoriMini_SinkTreasure",
        "Water_Relic",
        "Wind_Relic",
        "ZoraMini_DiveChallenge",
        "ZoraMini_FlowedWife",
        "ZoraMini_HarvestingStone",
        "ZoraMini_ReliefSearch",
        "Zora_FlogMini",
        "100enemy",
        "TreasureHunt01",
        "TreasureHunt02",
        "TreasureHunt_touzoku01",
        "TreasureHunt_touzoku02",
        "TreasureHunt_touzoku03",
        "TreasureHunt_touzoku04",
        "bf2_collabo",
        "BalladOfHeroes",
        "BalladOfHeroGerudo",
        "BalladOfHeroGoron",
        "BalladOfHeroZora",
        "BalladOfHeroRito",
        "AoC_hero_memory",
        "TreasureHunt03",
        "TreasureHunt04",
        "TreasureHunt_touzoku05",
        "TreasureHunt_touzoku06",
        "TreasureHunt_touzoku07",
        "TreasureHunt_touzoku08",
    };

    for (int i = 0, n = std::size(names); i < n; ++i) {
        if (names[i] == quest_name) {
            return i;
        }
    }
    return 0;
}

void reportGetItem(const sead::Vector3f& pos, const sead::SafeString& item_name) {
    ksys::ProductReporter::getSomeBool();
    PlayReport report(sead::SafeString("getitem"), 7,
                      ksys::PlayReportMgr::instance()->getReporter()->getHeap());
    report.addMapType();

    auto name = static_cast<int>(sead::HashCRC32::calcStringHash(item_name));

    ksys::ProductReporter::getSomeBool();

    report.add(sead::SafeString("name"), name);

    int position = convertPositionToInt({int(pos.x), int(pos.y)});

    report.add(sead::SafeString("Position"), position);
    report.addPlayTimes();

    if (ksys::PlayReportMgr::instance()) {
        auto* reporter = ksys::PlayReportMgr::instance()->getReporter();
        if (reporter && reporter->isEnabled())
            reporter->saveReport(&report);
    }
}

void reportQuestStep(const ksys::qst::Quest* quest, int step_index) {
    if (quest && step_index >= 0 && step_index < quest->mSteps.size()) {
        const sead::SafeString& name = quest->mName;
        const sead::SafeString step_name = quest->mSteps[step_index]->name;

        ksys::ProductReporter::getSomeBool();

        const unsigned int quest_id = getQuestId(name);

        PlayReport report(sead::SafeString("challenge"), 7,
                          ksys::PlayReportMgr::instance()->getReporter()->getHeap());

        report.addMapType();
        report.add(sead::SafeString("Id"), quest_id);
        report.add(sead::SafeString("Name"), name);
        report.add(sead::SafeString("Step"), step_index);
        report.add(sead::SafeString("StepName"), step_name);
        report.addPlayTimes();

        if (ksys::PlayReportMgr::instance()) {
            auto* reporter = ksys::PlayReportMgr::instance()->getReporter();
            if (reporter && reporter->isEnabled())
                reporter->saveReport(&report);
        }
    }
}

PlayReport::PlayReport(const sead::FixedSafeString<32>& event_id, s32 num_entries, sead::Heap* heap)
    : ksys::PlayReport(event_id, num_entries, heap) {}

void PlayReport::addMapType() {
    if (!ksys::gdt::Manager::instance())
        return;

    add(sead::SafeString("IsHardMode"), ksys::gdt::getFlag_AoC_HardMode_Enabled());

    const sead::SafeString& current_map = ksys::StageInfo::getCurrentMapType();
    u32 type = 0;

    if (current_map == "MainField")
        type = 1;

    if (current_map == "AocField")
        type = 2;

    if (current_map == "CDungeon")
        type = 3;

    if (current_map == "MainFieldDungeon")
        type = 4;

    add(sead::SafeString("MapType"), type);
}

}  // namespace uking
