#include "Game/gamePlayReport.h"
#include <math/seadVector.h>
#include "KingSystem/GameData/gdtCommonFlagsUtils.h"
#include "KingSystem/GameData/gdtManager.h"
#include "KingSystem/GameData/gdtTriggerParam.h"
#include "KingSystem/Quest/qstQuest.h"
#include "KingSystem/System/ProductReporter.h"
#include "KingSystem/System/StageInfo.h"

namespace uking {

unsigned int getQuestId(const sead::SafeString& quest_name);
int positionFunc(const sead::Vector2i& pos);

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

void reportGetItem(const sead::Vector3f& pos, const sead::SafeString* targetActorName) {
    ksys::ProductReporter::getSomeBool();
    PlayReport report(sead::SafeString("getitem"), 7,
                      ksys::PlayReportMgr::instance()->getReporter()->getHeap());
    report.addMapType();

    int name = sead::HashCRC32::calcStringHash(*targetActorName);

    ksys::ProductReporter::getSomeBool();

    report.add(sead::SafeString("name"), name);

    int position = positionFunc({int(pos.x), int(pos.y)});

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
