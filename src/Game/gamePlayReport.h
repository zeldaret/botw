#pragma once

#include <math/seadVector.h>
#include "KingSystem/System/PlayReportMgr.h"

namespace uking {

// TODO
class PlayReport {
public:
    class Report : public ksys::PlayReport {
    public:
        Report(const sead::FixedSafeString<32>& event_id, s32 num_entries, sead::Heap* heap);

        // TODO: requires LayoutResourceMgr
        void addRomVersions();

        void addPlayTimes();
        void addMapType();
        void addPosition(const sead::Vector2f& position);
    };

    static void reportKorok(const sead::Vector3f& position);
    static void reportDungeon(const sead::SafeString& name, const sead::SafeString& event);
};

}  // namespace uking
