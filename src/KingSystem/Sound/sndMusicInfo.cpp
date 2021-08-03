#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

MusicParam::ParamPerType::ParamPerType()
    : mBPM(0x6E, "Bpm", "BPM", "Min=60,Max=180", this),
      mPart0FirstWaitCount(0, "Part0FirstWaitCount", "パート0 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart1FirstWaitCount(1, "Part1FirstWaitCount", "パート1 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart2FirstWaitCount(15, "Part2FirstWaitCount", "パート2 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart3FirstWaitCount(30, "Part3FirstWaitCount", "パート3 初回予約の待ち拍", "Min=0,Max=100",
                           this) {}

MusicParam::MusicParam()
    : mEnableWaitSec(20, "EnableWaitSec", "昼夜切り替えや条件外れた後の開始待ち秒",
                     "Min=0.f, Max=40.f", &mData),
      mDistanceOfCheckingActiveEnemy(70, "DistanceOfCheckingActiveEnemy",
                                     "警戒以上の敵を調べる範囲", "Min=1, Max=50", &mData),
      mTimeDay(5, "TimeDay", "この時刻以降は昼扱い", "Min=0.f,Max=24.f", &mData),
      mTimeNight(20, "TimeNight", "この時刻以降は夜扱い", "Min=0.f,Max=24.f", &mData),
      mConstVolume(1, 1, "ConstVolume", "固定音量", "Min=0.f,Max=1.f", &mHeader),
      mConstPan(0, 0, "ConstPan", "固定パン", "Min=-1.f,Max=1.f", &mHeader),
      mMasterBeatBase(12, "MasterBeatBase", "基本の値", "Min=1,Max=24", &mData),
      mMasterBeatRate(1, 4, "MasterBeatRate", "倍率", "Min=1,Max=4", &mHeader),
      mPart0Volume(0.5, 1, "Part0Volume", "初回以外の音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart0Pan(-0.95, 0.95, "Part0Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader),
      mPart1SegmentAWaitCountBase(25, "Part1SegmentAWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentAWaitCountRate(1, 4, "Part1SegmentAWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1SegmentBWaitCountBase(15, "Part1SegmentBWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentBWaitCountRate(1, 5, "Part1SegmentBWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1SegmentCWaitCountBase(20, "Part1SegmentCWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentCWaitCountRate(1, 5, "Part1SegmentCWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1Volume(0.5, 1, "Part1Volume", "初回以外の音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart1Pan(-0.4, 0.4, "Part1Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader),
      mPart2WaitCountBase(40, "Part2WaitCountBase", "基本の値", "Min=0,Max=100", &mData),
      mPart2WaitCountRate(1, 3, "Part2WaitCountRate", "倍率", "Min=1,Max=10", &mHeader),
      mPart2Volume(0.4, 1, "Part2Volume", "音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      // mPart2Pan missing?
      mPart3WaitCountBase(50, "Part3WaitCountBase", "基本の値", "Min=0,Max=100", &mData),
      mPart3WaitCountRate(1, 4, "Part3WaitCountRate", "倍率", "Min=1,Max=10", &mHeader),
      mPart3Volume(0.4, 1, "Part3Volume", "音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart3Pan(-1, 1, "Part3Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader) {}

void MusicParam::init(sead::Heap* heap) {
    // mData not linked in any way?
    addList(&mHeader, "MusicParam");
    mParamPerTypes.allocBufferAssert(2, heap);
    mHeader.addObj(&mParamPerTypes[0],
                   sead::FormatFixedSafeString<32>("ParamPerType_%s", EnvTimeEnum(0).text()));
    mHeader.addObj(&mParamPerTypes[1],
                   sead::FormatFixedSafeString<32>("ParamPerType_%s", EnvTimeEnum(1).text()));
    sead::DirectResource* sound = loadMusic();
    if (sound) {
        agl::utl::ResParameterArchive archive(sound->getRawData());
        applyResParameterArchive(archive);
    }
}

HorseBgm::HorseBgm()
    : mTimeDay(5, "TimeDay", "この時刻以降は昼扱い", "Min=0.f, Max=24.f", &mData),
      mTimeNight(20, "TimeNight", "この時刻以降は夜扱い", "Min=0.f, Max=24.f", &mData),
      mPlayWaitSec(5, "PlayWaitSec", "快速ギアになってから再生開始までの待ち秒", "Min=0.f,Max=10.f",
                   &mData),
      mFadeInSec(14, "FadeInSec", "フェードイン秒", "Min=0.f,Max=30.f", &mData),
      mMinVolume(0, "MinVolume", "フェードイン開始時点の音量", "Min=0.f,Max=1.f", &mData),
      mFadeOutWaitSec(3, "FadeOutWaitSec", "ギアが下がった時のフェードアウト開始待ち秒",
                      "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(8, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=30.f", &mData),
      mPlayingSecUseOutro(18, "PlayingSecUseOutro",
                          "フェードアウト完了時に再生がこの秒数以上続いてたらアウトロあり",
                          "Min=0.f,Max=60.f", &mData),
      mIgnoreRequestSec(50, "IgnoreRequestSec",
                        "フェードアウト開始時に発動する開始リクエスト禁止秒", "Min=0.f,Max=100.f",
                        &mData) {}

void HorseBgm::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    sead::DirectResource* sound = loadMusic();
    if (sound) {
        agl::utl::ResParameterArchive archive(sound->getRawData());
        applyResParameterArchive(archive);
    }
}

TemperatureBgm::ParamPerType::ParamPerType()
    : mTemperatureThreshold(30, "TemperatureThreshold", "温度の閾値", "Min=-50.f,Max=50.f", this),
      mFadeOutSec(2, "FadeOutSec", "条件を外れた時のフェードアウト秒", "Min=0.f,Max=10.f", this),
      mCancelFadeSec(0.5, "CancelFadeSec", "再度条件に入った時の復帰フェード秒", "Min=0.f,Max=10.f",
                     this) {}

TemperatureBgm::TemperatureBgm() = default;

void TemperatureBgm::init(sead::Heap* heap) {
    addList(&mData, "MusicParam");
    mParamPerTypes.allocBufferAssert(3, heap);
    mData.addObj(&mParamPerTypes[0],
                 sead::FormatFixedSafeString<32>("ParamPerType_%s", TemperatureEnum(0).text()));
    mData.addObj(&mParamPerTypes[1],
                 sead::FormatFixedSafeString<32>("ParamPerType_%s", TemperatureEnum(1).text()));
    mData.addObj(&mParamPerTypes[2],
                 sead::FormatFixedSafeString<32>("ParamPerType_%s", TemperatureEnum(2).text()));
    sead::DirectResource* sound = loadMusic();
    if (sound) {
        agl::utl::ResParameterArchive archive(sound->getRawData());
        applyResParameterArchive(archive);
    }
}

}  // namespace ksys::snd
