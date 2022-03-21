#include <basis/seadRawPrint.h>
#include <prim/seadEnum.h>
#include <thread/seadCriticalSection.h>

namespace
{
class EnumParseTextCriticalSection
{
public:
    sead::CriticalSection* getObject()
    {
        static sead::CriticalSection sObject;
        return &sObject;
    }
};
static EnumParseTextCriticalSection sEnumParseTextCriticalSection;

class EnumInitValueArrayCriticalSection
{
public:
    sead::CriticalSection* getObject()
    {
        static sead::CriticalSection sObject;
        return &sObject;
    }
};
static EnumInitValueArrayCriticalSection sEnumInitValueArrayCriticalSection;
}  // namespace

namespace sead
{
CriticalSection* EnumUtil::getParseTextCS_()
{
    return sEnumParseTextCriticalSection.getObject();
}

CriticalSection* EnumUtil::getInitValueArrayCS_()
{
    return sEnumInitValueArrayCriticalSection.getObject();
}

void ParseFailed_([[maybe_unused]] char** text_ptr, [[maybe_unused]] int v)
{
#ifdef SEAD_DEBUG
    system::Print("----------------------------------------\n");
    for (int i = 0; i < v; ++i)
        system::Print("  text[%d] \"%s\"\n", i, text_ptr[i]);
    system::Print("----------------------------------------\n");
    SEAD_ASSERT_MSG(false, "SEAD_ENUM failed to parse text. Is number of comma correct?");
#endif
}

void EnumUtil::parseText_(char** text_ptr, char* text_all, int size)
{
    int index = 0;
    while (*text_all)
    {
        skipToWordStart_(&text_all);
        if (*text_all == 0)
            break;

        text_ptr[index] = text_all;
        ++index;

        char* next;
        skipToWordEnd_(&text_all, &next);
        const char next_char = *next;
        *text_all = 0;

        if (next_char == '=')
        {
            while (!(*++next == '\0' || *next == ',' || *next == '='))
                ;

            if (*next == '\0')
                break;
        }
        else if (next_char == '\0')
        {
            break;
        }

        // TODO: This is missing a call to skipToWordEnd_ and ParseFailed_ for the debug/develop
        // targets.
        if (index >= size)
            break;

        text_all = ++next;
    }

    if (index != size)
        ParseFailed_(text_ptr, index);
}

// Example:
// AoCVerAtLastPlay   ,LatestAoCVerPlayed
// ^               ^  ^
// initial p       |  next (p_next)
//                 end (p_ptr)
void EnumUtil::skipToWordEnd_(char** p_ptr, char** p_next)
{
    char* p = *p_ptr;
    while (!(*p == '\0' || *p == ',' || *p == '='))
        ++p;

    *p_next = p;

    --p;
    while ((*p == '\t' || *p == '\n' || *p == ' ') && intptr_t(p) > intptr_t(*p_ptr))
        --p;

    *p_ptr = p + 1;
}

void EnumUtil::skipToWordStart_(char** p_ptr)
{
    char* p = *p_ptr;
    while (*p == '\t' || *p == '\n' || *p == ' ' || *p == ',')
        ++p;
    *p_ptr = p;
}

}  // namespace sead
