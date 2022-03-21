#include "framework/seadProcessMeterBar.h"
#include "basis/seadRawPrint.h"
#include "framework/seadProcessMeter.h"

namespace sead
{
ProcessMeterBarBase::ProcessMeterBarBase(ProcessMeterBarBase::Section* sections, s32 num_sections,
                                         const SafeString& name, const Color4f& color)
    : INamable(name), mColor(color)
{
    mSectionList(0).setBuffer(num_sections, sections);
    _88(0) = 0;
    mSectionList(1).setBuffer(num_sections, sections + num_sections);
    _88(1) = 0;
}

ProcessMeterBarBase::~ProcessMeterBarBase()
{
    if (mParent)
        mParent->detachProcessMeterBar(this);
}

void ProcessMeterBarBase::measureBegin()
{
    if (mEnabled)
        measureBeginImpl_(TickTime(), mColor);
}

void ProcessMeterBarBase::measureBegin(const TickTime& start_time)
{
    if (mEnabled)
        measureBeginImpl_(start_time, mColor);
}

void ProcessMeterBarBase::measureBegin(const Color4f& color)
{
    if (mEnabled)
        measureBeginImpl_(TickTime(), color);
}

void ProcessMeterBarBase::measureBegin(const TickTime& start_time, const Color4f& color)
{
    if (mEnabled)
        measureBeginImpl_(start_time, color);
}

void ProcessMeterBarBase::measureEnd()
{
    if (mEnabled)
        measureEndImpl_(TickTime());
}

void ProcessMeterBarBase::measureEnd(const TickTime& end_time)
{
    if (mEnabled)
        measureEndImpl_(end_time);
}

const ProcessMeterBarBase::Section* ProcessMeterBarBase::getLastFirstBegin() const
{
    return mSectionList[1 - mActiveBufferIdx].get(0);
}

TickSpan ProcessMeterBarBase::getLastTotalSpan() const
{
    TickSpan total = 0;
    for (s32 i = 0; i < _88[1 - mActiveBufferIdx]; ++i)
    {
        if (mSectionList[1 - mActiveBufferIdx].get(i)->parent == -1)
            total += mSectionList[1 - mActiveBufferIdx].get(i)->span;
    }
    return total;
}

void ProcessMeterBarBase::onEndFrame()
{
    SEAD_ASSERT(mTopSection == -1);
    SEAD_ASSERT(mOverNum == 0);
    mActiveBufferIdx = 1 - mActiveBufferIdx;
    mTopSection = -1;
    mOverNum = 0;
    _88[mActiveBufferIdx] = 0;
    mEnabled = mParent != nullptr;
}

void ProcessMeterBarBase::setParentProcessMeter(ProcessMeter* parent)
{
    SEAD_ASSERT(mParent == nullptr || parent == nullptr);
    mParent = parent;
}

void ProcessMeterBarBase::measureBeginImpl_(const TickTime& start_time, Color4f color)
{
    addSection_(start_time, color, mTopSection);
}

void ProcessMeterBarBase::measureEndImpl_(const TickTime& end_time)
{
    TickTime new_time = end_time;
    mTicks[mActiveBufferIdx] = new_time;

    if (mOverNum > 0)
    {
        --mOverNum;
    }
    else
    {
        TickTime t = getCurSection_(mTopSection)->time;
        if (new_time.diff(t).toS64() < 0)
            new_time = t;

        SEAD_ASSERT_MSG(mTopSection >= 0, "Unmatching measureBegin / measureEnd.");
        endSection_(mTopSection, new_time);
        mTopSection = getCurSection_(mTopSection)->parent;
    }
}

// NON_MATCHING: some stores are paired
void ProcessMeterBarBase::addSection_(const TickTime& time, Color4f color, s32 parent)
{
    if (_88[mActiveBufferIdx] >= mSectionList[0].getSize())
    {
        ++mOverNum;
    }
    else
    {
        Section* sec = getCurSection_(_88[mActiveBufferIdx]);
        sec->time = time;
        sec->span = -1;
        sec->color = color;
        sec->parent = parent;

        mTopSection = _88[mActiveBufferIdx];
        ++_88[mActiveBufferIdx];
    }
}

ProcessMeterBarBase::Section* ProcessMeterBarBase::getCurSection_(s32 idx)
{
    SEAD_ASSERT(idx >= 0 && idx < mSectionList[0].getSize());
    return mSectionList[mActiveBufferIdx].get(idx);
}

void ProcessMeterBarBase::endSection_(s32 idx, const TickTime& time)
{
    SEAD_ASSERT(idx >= 0 && idx < mSectionList[0].getSize());
    Section* sec = getCurSection_(idx);
    SEAD_ASSERT(sec->span.toS64() == -1);
    sec->span = time.diff(sec->time);
}
}  // namespace sead
