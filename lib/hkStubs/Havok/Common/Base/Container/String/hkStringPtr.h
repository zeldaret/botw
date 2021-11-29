#pragma once

class hkStringPtr {
public:
    hkStringPtr();

    hkStringPtr& operator=(const char* s);

private:
    const char* m_stringAndFlag;
};
