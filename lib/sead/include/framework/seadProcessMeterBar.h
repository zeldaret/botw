#pragma once

#include "container/seadBuffer.h"
#include "container/seadSafeArray.h"
#include "gfx/seadColor.h"
#include "heap/seadDisposer.h"
#include "prim/seadNamable.h"
#include "prim/seadSafeString.h"
#include "time/seadTickTime.h"

namespace sead
{
class ProcessMeter;

class ProcessMeterBarBase : public IDisposer, public INamable
{
public:
    struct Section
    {
        TickTime time;
        TickSpan span;
        Color4f color;
        s32 parent;
    };

    ProcessMeterBarBase(Section* sections, s32 num_sections, const SafeString& name,
                        const Color4f& color);
    ~ProcessMeterBarBase() override;

    void measureBegin();
    void measureBegin(const TickTime& start_time);
    void measureBegin(const Color4f& color);
    void measureBegin(const TickTime& start_time, const Color4f& color);

    void measureEnd();
    void measureEnd(const TickTime& end_time);

    const Section* getLastFirstBegin() const;
    TickSpan getLastTotalSpan() const;

    void onEndFrame();

    ProcessMeter* getParentProcessMeter() const { return mParent; }
    void setParentProcessMeter(ProcessMeter* parent);

    void setColor(const Color4f& color) { mColor = color; }

protected:
    void measureBeginImpl_(const TickTime& start_time, Color4f color);
    void measureEndImpl_(const TickTime& end_time);

    void addSection_(const TickTime& time, Color4f color, s32 parent);
    Section* getCurSection_(s32 idx);
    void endSection_(s32 idx, const TickTime& time);

    void* _30 = nullptr;
    void* _38 = nullptr;
    ProcessMeter* mParent = nullptr;
    Color4f mColor;
    SafeArray<Buffer<Section>, 2> mSectionList;
    SafeArray<TickTime, 2> mTicks;
    SafeArray<s32, 2> _88;
    s32 mActiveBufferIdx = 0;
    s32 mTopSection = -1;
    s32 mOverNum = 0;
    bool mEnabled = false;
};

template <s32 N>
class MultiProcessMeterBar : public ProcessMeterBarBase
{
public:
    MultiProcessMeterBar(const SafeString& name = SafeString::cEmptyString,
                         const Color4f& color = Color4f::cRed)
        : ProcessMeterBarBase(mSections, N, name, color)
    {
    }

private:
    Section mSections[2 * N];
};
}  // namespace sead
