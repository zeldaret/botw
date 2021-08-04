#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

void MusicInfo::applySoundResource() {
    sead::DirectResource* sound = loadMusic();
    if (sound) {
        agl::utl::ResParameterArchive archive(sound->getRawData());
        applyResParameterArchive(archive);
    }
}

EnvBgmInfo::ParamPerType::ParamPerType()
    : mBpm(110, "Bpm", "BPM", "Min=60,Max=180", this),
      mPart0FirstWaitCount(0, "Part0FirstWaitCount", "パート0 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart1FirstWaitCount(1, "Part1FirstWaitCount", "パート1 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart2FirstWaitCount(15, "Part2FirstWaitCount", "パート2 初回予約の待ち拍", "Min=0,Max=100",
                           this),
      mPart3FirstWaitCount(30, "Part3FirstWaitCount", "パート3 初回予約の待ち拍", "Min=0,Max=100",
                           this) {}

EnvBgmInfo::EnvBgmInfo()
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

void EnvBgmInfo::init(sead::Heap* heap) {
    // mData not linked in any way?
    addList(&mHeader, "MusicParam");
    mParamPerTypes.allocBufferAssert(EnvTimeEnum::size(), heap);
    for (int i = 0; i < EnvTimeEnum::size(); i++) {
        mHeader.addObj(&mParamPerTypes[i],
                       sead::FormatFixedSafeString<32>("ParamPerType_%s", EnvTimeEnum(i).text()));
    }
    applySoundResource();
}

HorseBgmInfo::HorseBgmInfo()
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

void HorseBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

TemperatureBgmInfo::ParamPerType::ParamPerType()
    : mTemperatureThreshold(30, "TemperatureThreshold", "温度の閾値", "Min=-50.f,Max=50.f", this),
      mFadeOutSec(2, "FadeOutSec", "条件を外れた時のフェードアウト秒", "Min=0.f,Max=10.f", this),
      mCancelFadeSec(0.5, "CancelFadeSec", "再度条件に入った時の復帰フェード秒", "Min=0.f,Max=10.f",
                     this) {}

void TemperatureBgmInfo::init(sead::Heap* heap) {
    addList(&mData, "MusicParam");
    mParamPerTypes.allocBufferAssert(TemperatureEnum::size(), heap);
    for (int i = 0; i < TemperatureEnum::size(); i++) {
        mData.addObj(&mParamPerTypes[i],
                     sead::FormatFixedSafeString<32>("ParamPerType_%s", TemperatureEnum(i).text()));
    }
    applySoundResource();
}

TemperatureBgmInfo::~TemperatureBgmInfo() = default;

SpotBgmInfo::SpotBgmInfo()
    : mTimeDay(3.5, "TimeDay", "この時刻以降は昼扱い", "Min=0.f, Max=24.f", &mData),
      mTimeNight(20, "TimeNight", "この時刻以降は夜扱い", "Min=0.f, Max=24.f", &mData),
      mFilterOnFadeSec(8, "FilterOnFadeSec", "フィルタOnの時のフェード秒", "Min=0.f,Max=30.f",
                       &mData),
      mFilterOffFadeSec(5, "FilterOffFadeSec", "フィルタOffの時のフェード秒", "Min=0.f,Max=30.f",
                        &mData),
      mFilterValueLo(0.65, "FilterValueLo", "フィルタの値（ローパス）", "Min=0.f,Max=1.f", &mData),
      mFilterValueHi(0.65, "FilterValueHi", "フィルタの値（ハイパス）", "Min=0.f,Max=1.f", &mData),
      mSubTrackNearDistance(10, "SubTrackNearDistance", "音量最大になる距離（m）",
                            "Min=0.f,Max=50.f", &mData),
      mSubTrackFarDistance(30, "SubTrackFarDistance", "音量最小になる距離（m）", "Min=0.f,Max=50.f",
                           &mData),
      mSubTrackVolumeMaxDelta(1, "SubTrackVolumeMaxDelta",
                              "音量の変化度合の上限（大きくすると急な変化を抑えられる）",
                              "Min=0.01f,Max=1.f", &mData),
      mAllowFadeInSec(1, "AllowFadeInSec", "フェードイン秒", "Min=0.f, Max=3.f", &mData),
      mAllowFadeOutSec(3, "AllowFadeOutSec", "フェードアウト秒", "Min=0.f, Max=3.f", &mData),
      mFadeOutSec(3, "FadeOutSec", "シグナル切断によるフェードアウト秒", "Min=0.f, Max=3.f",
                  &mData),
      mCullingYFadeOutSec(3, "CullingYFadeOutSec", "エリア外によるフェードアウト秒",
                          "Min=0.f, Max=5.f", &mData),
      mCullingYFadeInSec(1, "CullingYFadeInSec", "エリア内復帰によるフェードイン秒",
                         "Min=0.f, Max=5.f", &mData) {}

void SpotBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

MazeForestBgmInfo::MazeForestBgmInfo()
    : mPlayWaitSec(3, "PlayWaitSec", "エリアに入ってからの再生開始待ち秒", "Min=0.f, Max=10.f",
                   &mData),
      mFadeInSec(5, "FadeInSec", "再生開始時のフェードイン秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(9, "FadeOutSec", "エリアから出た時のフェードアウト秒", "Min=0.f,Max=10.f",
                  &mData),
      mVolumeNormal(0.34, "VolumeNormal", "エリア内通常状態の音量", "Min=0.f,Max=1.f", &mData),
      mLostBoostSec(1.5, "LostBoostSec", "迷い状態になった時の音量上げ秒", "Min=0.f,Max=10.f",
                    &mData),
      mLostBoostCancelSec(2, "LostBoostCancelSec", "迷い状態を脱した時の音量戻し秒",
                          "Min=0.f,Max=10.f", &mData) {}

void MazeForestBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

CastleBgmInfo::CastleBgmInfo()
    : mFadeOutWaitSec(3, "FadeOutWaitSec", "フェードアウト待ち秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(8, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mToIndoorWaitSec(3, "ToIndoorWaitSec", "外→内時のクロスフェード開始待ち秒",
                       "Min=0.f,Max=10.f", &mData),
      mToIndoorFadeSec(5, "ToIndoorFadeSec", "外→内時のクロスフェード秒", "Min=0.f,Max=10.f",
                       &mData),
      mToOutdoorFadeSec(5, "ToOutdoorFadeSec", "内→外時のクロスフェード秒", "Min=0.f,Max=10.f",
                        &mData),
      mBattleWaitSec(1, "BattleWaitSec", "戦闘トラックフェードイン待ち秒", "Min=0.f,Max=10.f",
                     &mData),
      mBattleFadeInSec(5, "BattleFadeInSec", "戦闘トラックフェードイン秒", "Min=0.f,Max=10.f",
                       &mData),
      mBattleFadeOutSec(5, "BattleFadeOutSec", "戦闘トラックフェードアウト秒", "Min=0.f,Max=10.f",
                        &mData) {}

void CastleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

BigMazeBgmInfo::BigMazeBgmInfo()
    : mPlayWaitSec(3, "PlayWaitSec", "エリアに入ってからの再生開始待ち秒", "Min=0.f, Max=10.f",
                   &mData),
      mFadeInSec(5, "FadeInSec", "再生開始時のフェードイン秒", "Min=0.f, Max=10.f", &mData),
      mFadeOutSec(10, "FadeOutSec", "再生停止時のフェードアウト秒", "Min=0.f, Max=20.f", &mData) {}

void BigMazeBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

AnimalMasterBgmInfo::AnimalMasterBgmInfo()
    : mPlayWaitSec(2, "PlayWaitSec", "エリアに入ってからの再生開始待ち秒", "Min=0.f, Max=10.f",
                   &mData),
      mFadeInSec(5, "FadeInSec", "再生開始時のフェードイン秒", "Min=0.f, Max=10.f", &mData),
      mFadeOutSec(6, "FadeOutSec", "再生停止時のフェードアウト秒", "Min=0.f, Max=20.f", &mData) {}

void AnimalMasterBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

FieldBattleBgmInfo::FieldBattleBgmInfo()
    : mBpm(130, "Bpm", "BPM", "Min=90,Max=180", &mData),
      mPlayWaitSec(1, "PlayWaitSec", "緊迫発生から再生開始までの待ち秒", "Min=0.f,Max=10.f",
                   &mData),
      mFadeInSec(5, "FadeInSec", "再生開始時のフェードイン秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(5, "FadeOutSec", "緊迫解除時のフェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(3, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData),
      mEasy1_OddsByKey0(40, "Easy1_OddsByKey0", "Easy1の前で調0を選ぶ確率", "Min=0.f,Max=100.f",
                        &mData),
      mEasy1_OddsByKey1(30, "Easy1_OddsByKey1", "Easy1の前で調1を選ぶ確率", "Min=0.f,Max=100.f",
                        &mData),
      mEasy1R_OddsBySameKey(20, "Easy1R_OddsBySameKey", "Easy1に再度戻る時に同調を継続する確率",
                            "Min=0.f,Max=100.f", &mData),
      mEasy5_OddsBySameKey(40, "Easy5_OddsBySameKey", "Easy5の前で同調を継続する確率",
                           "Min=0.f,Max=100.f", &mData),
      mMiddle0_OddsBySameKey(40, "Middle0_OddsBySameKey", "Middle0の前で同調を継続する確率",
                             "Min=0.f,Max=100.f", &mData),
      mHard0_OddsBySameKey(100, "Hard0_OddsBySameKey", "Hard0の前で同調を継続する確率",
                           "Min=0.f,Max=100.f", &mData),
      mHard1_OddsBySameKey(40, "Hard1_OddsBySameKey", "Hard1の前で同調を継続する確率",
                           "Min=0.f,Max=100.f", &mData),
      mHard1F_OddsBySameKey(20, "Hard1F_OddsBySameKey", "Hard1の後で同調を継続する確率",
                            "Min=0.f,Max=100.f", &mData),
      mOddsByKeySubId0(50, "OddsByKeySubId0", "調内タイプのAorBの確率", "Min=0.f,Max=100.f",
                       &mData),
      mTension_SkipEasy2(25, "Tension_SkipEasy2", "Easy2をスキップする緊迫度", "Min=0,Max=100",
                         &mData),
      mTension_SkipEasy5(50, "Tension_SkipEasy5", "Easy5をスキップする緊迫度", "Min=0,Max=100",
                         &mData),
      mTension_SkipMiddle1(70, "Tension_SkipMiddle1", "Middle1をスキップする緊迫度",
                           "Min=0,Max=100", &mData),
      mTension_SkipHard(39, "Tension_SkipHard", "Hardに進む緊迫度", "Min=0,Max=100", &mData),
      mReserveHitWaitBeat(1, "ReserveHitWaitBeat", "何拍先に予約するか", "Min=0,Max=10", &mData),
      mHitChainGridThreshold(18, "HitChainGridThreshold",
                             "このグリッド以上ヒット間隔が空いたらコンボをリセット", "Min=1,Max=20",
                             &mData),
      mIgnoreReserveHitGrid_Chain0(3, "IgnoreReserveHitGrid_Chain0", "ヒット波形0", "Min=0,Max=10",
                                   &mData),
      mIgnoreReserveHitGrid_Chain1(2, "IgnoreReserveHitGrid_Chain1", "ヒット波形1", "Min=0,Max=10",
                                   &mData),
      mIgnoreReserveHitGrid_Chain2(5, "IgnoreReserveHitGrid_Chain2", "ヒット波形2", "Min=0,Max=10",
                                   &mData),
      mStopMainBgmWaitBeat(0, "StopMainBgmWaitBeat", "何拍先に通常波形を止めるか", "Min=0,Max=5",
                           &mData),
      mReserveOutroWaitBeat(0, "ReserveOutroWaitBeat", "何拍先にアウトロ予約するか", "Min=0,Max=10",
                            &mData) {}

void FieldBattleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

BossBgmInfo::BossBgmInfo()
    : mPlayWaitSec(2, "PlayWaitSec", "再生開始までの待ち秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(5, "FadeOutSec", "見失った時のフェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mOutroWaitSec(0, "OutroWaitSec", "アウトロ開始待ち秒", "Min=0.f,Max=10.f", &mData),
      mChangeTypeFadeOutSec(4, "ChangeTypeFadeOutSec", "ゲージ表示敵切替時のフェードアウト秒",
                            "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(3, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData) {}

void BossBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

// GolemBgmInfo and GiantBgmInfo functions never defined in code, but are just references to
// BossBgmInfo functions
GolemBgmInfo::GolemBgmInfo() = default;

GiantBgmInfo::GiantBgmInfo() = default;

SandwormBgmInfo::SandwormBgmInfo()
    : mAngryStartFadeSec(1, "AngryStartFadeSec", "怒り開始時クロスフェード秒", "Min=0.f,Max=5.f",
                         &mData),
      mAngryEndFadeSec(1, "AngryEndFadeSec", "怒り終了時クロスフェード秒", "Min=0.f,Max=5.f",
                       &mData),
      mChanceStartWaitSec(0.5, "ChanceStartWaitSec", "チャンスタイム開始待ち秒", "Min=0.f,Max=5.f",
                          &mData) {}

AssassinSeniorBgmInfo::AssassinSeniorBgmInfo()
    : mFadeOutSec(5, "FadeOutSec", "範囲外によるフェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mToDemoFadeSec(0.5, "ToDemoFadeSec", "デモ開始時トラックフェードアウト秒", "Min=0.f,Max=10.f",
                     &mData),
      mToBattleFadeSec(0.5, "ToBattleFadeSec", "デモ終了時トラックフェードイン秒",
                       "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(0.4, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData) {}

void AssassinSeniorBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

GuardianBgmInfo::GuardianBgmInfo()
    : mPlayWaitSec(0.35, "PlayWaitSec", "再生開始までの待ち秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutWaitSec(3, "FadeOutWaitSec", "フェードアウト待ち秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(5, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(0.4, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData),
      mDamageThresholdHitReserve(100, "DamageThresholdHitReserve", "ヒット予約するダメージ量",
                                 "Min=10,Max=500", &mData),
      mCancelHitSec(1.8, "CancelHitSec", "ヒット予約後マーカーがすぐこない場合の予約破棄までの秒数",
                    "Min=0.1f,Max=10.f", &mData),
      mIgnoreReserveCountDownSec(3.9, "IgnoreReserveCountDownSec",
                                 "ヒット波形再生開始後、再予約を許可するまでの秒数",
                                 "Min=0.f,Max=10.f", &mData),
      mMarkerIdHitSectionB(39, "MarkerIdHitSectionB", "次がこのID以上なら「Ｂ」", "Min=0,Max=100",
                           &mData),
      mMarkerIdHitSectionC(54, "MarkerIdHitSectionC", "次がこのID以上なら「Ｃ」", "Min=0,Max=100",
                           &mData),
      mMarkerIdHitSectionA(61, "MarkerIdHitSectionA", "次がこのID以上ならまわって「Ａ」",
                           "Min=0,Max=100", &mData),
      mMarkerCallbackOffsetSample(
          -2850, "MarkerCallbackOffsetSample",
          "マーカーコールバックのオフセットサンプル数（負にすると実際より手前で返る）",
          "Min=-32000,Max=32000", &mData) {}

void GuardianBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

GuardianFixedBgmInfo::GuardianFixedBgmInfo()
    : mPlayWaitSec(0.35, "PlayWaitSec", "再生開始までの待ち秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(5, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mFadeWaitSec(1, "FadeWaitSec", "フェードアウト開始までの待ち秒", "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(0.4, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData) {}

void GuardianFixedBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

DragonBgmInfo::ParamPerType::ParamPerType()
    : mDistanceThreshold(200, "DistanceThreshold", "再生開始する距離", "Min = 50.f,Max=400.f",
                         this),
      mPlayWaitSec(1, "PlayWaitSec", "再生待ち秒", "Min=0.f,Max=10.f", this),
      mFadeInSec(6, "FadeInSec", "フェードイン秒", "Min=0.f,Max=20.f", this),
      mFadeWaitSec(3, "FadeWaitSec", "再生終了待ち秒", "Min=0.f,Max=20.f", this),
      mFadeOutSec(8, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=20.f", this) {}

void DragonBgmInfo::init(sead::Heap* heap) {
    addList(&mData, "MusicParam");
    mParamPerTypes.allocBufferAssert(DragonEnum::size(), heap);
    for (int i = 0; i < DragonEnum::size(); i++) {
        mData.addObj(&mParamPerTypes[i],
                     sead::FormatFixedSafeString<32>("ParamPerType_%s", DragonEnum(i).text()));
    }
    applySoundResource();
}

GanonGrudgeBattleBgmInfo::GanonGrudgeBattleBgmInfo()
    : mFadeInSec(1, "FadeInSec", "フェードイン秒", "Min=0.f,Max=10.f", &mData),
      mFadeOutSec(2, "FadeOutSec", "フェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mFeelPlayingSec(0.4, "FeelPlayingSec",
                      "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                      "Min=0.f,Max=10.f", &mData) {}

void GanonGrudgeBattleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

EventBgmRemainsElecBattleInfo::EventBgmRemainsElecBattleInfo()
    : mMinVolumeOutStorm(0.2, "MinVolumeOutStorm", "条件外の時の音量", "Min=0.f, Max=1.f", &mData),
      mFadeInSecOutStorm(3, "FadeInSecOutStorm", "フェードイン秒", "Min=0.f,Max=5.f", &mData),
      mFadeOutSecOutStorm(3, "FadeOutSecOutStorm", "フェードアウト秒", "Min=0.f,Max=5.f", &mData),
      mMinVolumeWakeBoarding(0, "MinVolumeWakeBoarding", "条件外の時の音量", "Min=0.f,Max=1.f",
                             &mData),
      mFadeInSecWakeBoarding(0.1, "FadeInSecWakeBoarding", "フェードイン秒", "Min=0.f,Max=5.f",
                             &mData),
      mFadeOutSecWakeBoarding(0.1, "FadeOutSecWakeBoarding", "フェードアウト秒", "Min=0.f,Max=5.f",
                              &mData) {}

void EventBgmRemainsElecBattleInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

EventBgmRemainsFireBattleInfo::EventBgmRemainsFireBattleInfo()
    : mFoundFadeOutSec(0.1, "FoundFadeOutSec", "警報時フェードアウト秒", "Min=0.f, Max=5.f",
                       &mData),
      mFoundWaitSec(2, "FoundWaitSec", "警報時（初回）の次のkey再生待ち秒", "Min=0.f,Max=5.f",
                    &mData),
      mFoundAgainWaitSec(1, "FoundAgainWaitSec", "警報時（二回目以降）の次のkey再生待ち秒",
                         "Min=0.f,Max=5.f", &mData) {}

void EventBgmRemainsFireBattleInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

DungeonNormalBgmInfo::PartChangeOdds::PartChangeOdds()
    : mOdds_1To1(50, "Odds_1To1", "今回パート数1を選ぶ確率（％）", "Min=0.f,Max=100.f", this),
      mOdds_2To1(50, "Odds_2To1", "今回パート数1を選ぶ確率（％）", "Min=0.f,Max=100.f", this),
      mOdds_2To2(50, "Odds_2To2", "今回パート数2を選ぶ確率（％）", "Min=0.f,Max=100.f", this),
      mOdds_3To2(50, "Odds_3To2", "今回パート数2を選ぶ確率（％）", "Min=0.f,Max=100.f", this),
      mOdds_3To3(50, "Odds_3To3", "今回パート数3を選ぶ確率（％）", "Min=0.f,Max=100.f", this),
      mOdds_4To3(50, "Odds_4To3", "今回パート数3を選ぶ確率（％）", "Min=0.f,Max=100.f", this) {}

DungeonNormalBgmInfo::DungeonNormalBgmInfo()
    : mLoopNumForOddsId2(10, "LoopNumForOddsId2", "確率パターンが2になるループ回数", "Min=0,Max=50",
                         &mData),
      mLoopNumForOddsId3(20, "LoopNumForOddsId3", "確率パターンが3になるループ回数", "Min=0,Max=50",
                         &mData),
      mMaxPartChainThreshold(4, "MaxPartChainThreshold",
                             "パート数最大が何回続いたらループ回数リセットするか", "Min=0,Max=10",
                             &mData),
      mOdds_FirstArp(50, "Odds_FirstArp",
                     "初回にアルペジオorストリングベースでアルペジオを選ぶ確率（％）",
                     "Min=0.f,Max=100.f", &mData),
      mTitleDelaySec(0, "TitleDelaySec", "ダンジョンのタイトルが消えてから再生開始までの時間(秒)",
                     "Min=0.f,Max=10.f", &mData) {}

void DungeonNormalBgmInfo::init(sead::Heap* heap) {
    addList(&mHeader, "MusicParam");
    static constexpr int NumPartChangeOdds = 3;
    mPartChangeOdds.allocBufferAssert(NumPartChangeOdds, heap);
    for (int i = 0; i < NumPartChangeOdds; i++)
        mHeader.addObj(&mPartChangeOdds[i], sead::FormatFixedSafeString<32>("PartChangeOdds%d", i));
    applySoundResource();
}

DungeonRewardBgmInfo::DungeonRewardBgmInfo()
    : mOddsPlayableString(50, "OddsPlayableString", "ストリングスが選ばれる確率（％）",
                          "Min=0.f, Max=100.f", &mData),
      mTitleDelaySec(0, "TitleDelaySec", "ダンジョンのタイトルが消えてから再生開始までの時間(秒)",
                     "Min=0.f,Max=10.f", &mData) {}

void DungeonRewardBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

DungeonBattleBgmInfo::DungeonBattleBgmInfo()
    : mPlayWaitSec(1, "PlayWaitSec", "緊迫発生から再生開始までの待ち秒", "Min=0.f, Max=10.f",
                   &mData),
      mFadeOutSec(5, "FadeOutSec", "緊迫解除時のフェードアウト秒", "Min=0.f,Max=10.f", &mData),
      mVolumeNormal(3, "VolumeNormal", "再生開始後、この秒数を越えたら他セクションに再生中と通知",
                    "Min=0.f,Max=10.f", &mData) {}

void DungeonBattleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

RemainsNormalBgmInfo::RemainsNormalBgmInfo()
    : mFadeOutSecA(2, "FadeOutSecA", "A→Bの時のAのフェードアウト秒", "Min=0.f, Max=10.f", &mData),
      mFadeOutSecB(0, "FadeOutSecB", "B→Zの時のBのフェードアウト秒", "Min=0.f, Max=10.f", &mData),
      mFadeOutSecZ(2, "FadeOutSecZ", "Z→ボスの時のZのフェードアウト秒", "Min=0.f, Max=10.f",
                   &mData),
      mCrossFadeSec(1, "CrossFadeSec", "B内のクロスフェード秒", "Min=0.f, Max=10.f", &mData) {}

void RemainsNormalBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

TutorialDungeonBattleBgmInfo::TutorialDungeonBattleBgmInfo()
    : mTransitionDelaySec(0.46, "TransitionDelaySec", "ステップ間の再生待ち秒", &mData),
      mOutroDelaySec(0, "OutroDelaySec", "アウトロ開始前の待ち秒", &mData) {}

void TutorialDungeonBattleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

GanonBeastBgmInfo::GanonBeastBgmInfo()
    : mStartDelaySec(0.5, "StartDelaySec", "開始時の再生待ち秒", &mData),
      mRetryDelaySec(0.5, "RetryDelaySec", "リトライ時の再生待ち秒", &mData),
      m1To2TransitionDelaySec(1, "1To2TransitionDelaySec", "レベル1→2の再生待ち秒", &mData),
      m2To3TransitionDelaySec(1, "2To3TransitionDelaySec", "レベル2→3の再生待ち秒", &mData),
      mFadeOutSec(0.25, "FadeOutSec", "切り替わり時のフェードアウト秒", &mData) {}

void GanonBeastBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

FinalTrialBossBattleBgmInfo::FinalTrialBossBattleBgmInfo()
    : mTransformDemoWaitSec(1, "TransformDemoWaitSec", "変化デモトラックチェンジ待ち秒", &mData),
      mFadeSecToTransformDemo(1, "FadeSecToTransformDemo", "変化デモトラックへのクロスフェード秒",
                              &mData),
      mCurveTypeToTransformDemo(
          1, "CurveTypeToTransformDemo",
          "変化デモトラックへのカーブタイプ(0=リニア,1=二乗,2=平方根,3=サイン)", &mData),
      mFadeSecFromTransformDemo(1, "FadeSecFromTransformDemo",
                                "変化デモからインゲームへのクロスフェード秒", &mData),
      mCurveTypeFromTransformDemo(
          1, "CurveTypeFromTransformDemo",
          "変化デモからインゲームへのカーブタイプ(0=リニア,1=二乗,2=平方根,3=サイン)", &mData),
      mFadeSeLevel3To4(1, "FadeSecLevel3To4", "レベル3から4へのクロスフェード秒", &mData),
      mCurveTypeLevel3To4(1, "CurveTypeLevel3To4",
                          "レベル3から4へのカーブタイプ(0=リニア,1=二乗,2=平方根,3=サイン)",
                          &mData),
      mStopFadeSec(1, "StopFadeSec", "停止時のフェード秒", &mData) {}

void FinalTrialBossBattleBgmInfo::init(sead::Heap* heap) {
    addObj(&mData, "MusicParam");
    applySoundResource();
}

EnvPaletteReactiveBgmInfo::ParamPerType::ParamPerType()
    : mPlayWaitSec(2, "PlayWaitSec", "再生待ち秒", "Min = 0.1f, Max = 10.f", this),
      mFadeInSec(5, "FadeInSec", "フェードイン秒", this),
      mFadeOutSec(3, "FadeOutSec", "フェードアウト秒", this) {}

void EnvPaletteReactiveBgmInfo::init(sead::Heap* heap) {
    addList(&mData, "MusicParam");
    mParamPerTypes.allocBufferAssert(EnvPaletteReactiveBgmEnum::size(), heap);
    for (int i = 0; i < EnvPaletteReactiveBgmEnum::size(); i++) {
        mData.addObj(&mParamPerTypes[i],
                     sead::FormatFixedSafeString<32>("ParamPerType_%s",
                                                     EnvPaletteReactiveBgmEnum(i).text()));
    }
    applySoundResource();
}

}  // namespace ksys::snd
