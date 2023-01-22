#include "KingSystem/System/PlayReportMgr.h"
#include <nn/account.h>
#include <nn/prepo.h>
#include "KingSystem/System/Account.h"
#include "KingSystem/System/ProductReporter.h"

namespace ksys {

SEAD_SINGLETON_DISPOSER_IMPL(PlayReportMgr)

PlayReportMgr::~PlayReportMgr() {
    if (mReporter)
        delete mReporter;
}

void PlayReportMgr::calc() {
    if (!_30 && mReporter)
        mReporter->updateTimers();
}

void PlayReportMgr::reportDebug(const sead::SafeString& message, const sead::SafeString& data) {
    // Stubbed in release builds
}

bool PlayReportMgr::auto0() const {
    return true;
}

PlayerTrackReporter* PlayReportMgr::getPlayerTrackReporter() const {
    if (!mReporter)
        return nullptr;
    return mReporter->getPlayerTrackReporter();
}

void PlayReportMgr::setPlayerTrackReporter28() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_28 = true;
}

void PlayReportMgr::setPlayerTrackReporter29() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_29 = true;
}

void PlayReportMgr::setPlayerTrackReporter30() {
    if (auto* reporter = getPlayerTrackReporter())
        reporter->_30 = true;
}

bool PlayReport::setEventId(sead::BufferedSafeString& event_id) {
    if (!mHasNinPrepoReport)
        return false;

    event_id.replaceCharList("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz");
    return mNinPlayReport->SetEventId(event_id.cstr()).IsSuccess();
}

[[gnu::noinline]] bool PlayReport::add(const sead::FixedSafeString<48>& key, u32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), s64(value)).IsSuccess();
}

[[gnu::noinline]] bool PlayReport::add(const sead::FixedSafeString<48>& key, s32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), s64(value)).IsSuccess();
}

[[gnu::noinline]] bool PlayReport::add(const sead::FixedSafeString<48>& key, f32 value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), value).IsSuccess();
}

[[gnu::noinline]] bool PlayReport::add(const sead::FixedSafeString<48>& key,
                                       const sead::SafeString& value) {
    return mHasNinPrepoReport && mNinPlayReport->Add(key.cstr(), value.cstr()).IsSuccess();
}

void PlayReport::addPlayTimes() {
    if (!gdt::Manager::instance())
        return;

    if (!PlayReportMgr::instance())
        return;

    if (!PlayReportMgr::instance()->getReporter())
        return;

    s32 playTime =
        PlayReportMgr::instance()->getReporter()->getS32(PlayReportKey::PlayReport_PlayTime);

    s32 allPlayTime =
        PlayReportMgr::instance()->getReporter()->getS32(PlayReportKey::PlayReport_AllPlayTime);

    add(sead::SafeString("PlayTime"), u32(playTime));
    add(sead::SafeString("AllPlayTime"), u32(allPlayTime));
}

void PlayReport::addPosition(const sead::Vector2f& position) {
    add(sead::SafeString("PosX"), position.x);
    add(sead::SafeString("PosZ"), position.y);
}

bool PlayReport::save() {
    if (!mHasNinPrepoReport)
        return false;

    nn::account::Uid uid;
    Account::instance()->getUserId(&uid);
    if (uid.IsValid()) {
        static_cast<void>(mNinPlayReport->GetCount());
        return mNinPlayReport->Save(uid).IsSuccess();
    }
    static_cast<void>(ProductReporter::getSomeBool());
    static_cast<void>(mNinPlayReport->GetCount());
    return mNinPlayReport->Save().IsSuccess();
}

void PlayReport::init(s32 num_entries, sead::Heap* heap) {
    if (mHasNinPrepoReport)
        return;

    auto* report = new (heap) nn::prepo::PlayReport;
    const u32 buffer_size = nn::prepo::PlayReport::CalcBufferSize(num_entries);
    mNinPlayReport = report;
    if (buffer_size > 0 && mBuffer.tryAllocBuffer(buffer_size, heap)) {
        mNinPlayReport->SetBuffer(mBuffer.getBufferPtr(), buffer_size);
        mHasNinPrepoReport = true;
    }
}

PlayReport::~PlayReport() {
    if (!mHasNinPrepoReport)
        return;

    if (mNinPlayReport) {
        delete mNinPlayReport;
        mNinPlayReport = nullptr;
    }

    if (mHasNinPrepoReport)
        mBuffer.freeBuffer();

    mHasNinPrepoReport = false;
}

}  // namespace ksys
