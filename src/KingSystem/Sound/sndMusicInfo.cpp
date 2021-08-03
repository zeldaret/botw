#include "KingSystem/Sound/sndMusicInfo.h"

namespace ksys::snd {

MusicInfo::MusicInfo() : IParameterIO("mscinfo", 0) {}

MusicParam::OtherSub::OtherSub()
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
      mDistanceOfCheckingActiveEnemy('F', "DistanceOfCheckingActiveEnemy",
                                     "警戒以上の敵を調べる範囲", "Min=1, Max=50", &mData),
      mTimeDay(5, "TimeDay", "この時刻以降は昼扱い", "Min=0.f,Max=24.f", &mData),
      mTimeNight(20, "TimeNight", "この時刻以降は夜扱い", "Min=0.f,Max=24.f", &mData),
      mConstVolume(1, 1, "ConstVolume", "固定音量", "Min=0.f,Max=1.f", &mHeader),
      mConstPan(0, 0, "ConstPan", "固定パン", "Min=-1.f,Max=1.f", &mHeader),
      mMasterBeatBase(0xC, "MasterBeatBase", "基本の値", "Min=1,Max=24", &mData),
      mMasterBeatRate(1, 4, "MasterBeatRate", "倍率", "Min=1,Max=4", &mHeader),
      mPart0Volume(0.5, 1, "Part0Volume", "初回以外の音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart0Pan(-0.95, 0.95, "Part0Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader),
      mPart1SegmentAWaitCountBase(0x19, "Part1SegmentAWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentAWaitCountRate(1, 4, "Part1SegmentAWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1SegmentBWaitCountBase(0xF, "Part1SegmentBWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentBWaitCountRate(1, 5, "Part1SegmentBWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1SegmentCWaitCountBase(0x14, "Part1SegmentCWaitCountBase", "基本の値", "Min=0,Max=100",
                                  &mData),
      mPart1SegmentCWaitCountRate(1, 5, "Part1SegmentCWaitCountRate", "倍率", "Min=1,Max=10",
                                  &mHeader),
      mPart1Volume(0.5, 1, "Part1Volume", "初回以外の音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart1Pan(-0.4, 0.4, "Part1Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader),
      mPart2WaitCountBase(0x28, "Part2WaitCountBase", "基本の値", "Min=0,Max=100", &mData),
      mPart2WaitCountRate(1, 3, "Part2WaitCountRate", "倍率", "Min=1,Max=10", &mHeader),
      mPart2Volume(0.4, 1, "Part2Volume", "音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      // mPart2Pan missing?
      mPart3WaitCountBase(0x32, "Part3WaitCountBase", "基本の値", "Min=0,Max=100", &mData),
      mPart3WaitCountRate(1, 4, "Part3WaitCountRate", "倍率", "Min=1,Max=10", &mHeader),
      mPart3Volume(0.4, 1, "Part3Volume", "音量ランダム幅", "Min=0.f,Max=1.f", &mHeader),
      mPart3Pan(-1, 1, "Part3Pan", "パンランダム幅", "Min=-1.f,Max=1.f", &mHeader) {}

}  // namespace ksys::snd
