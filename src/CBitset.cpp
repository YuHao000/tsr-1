/*
* @file CBitset.cpp
* @authur liyi_whu@163.com
* @create 2018-11-03
*/

#include <malloc.h>
#include "Common.hpp"
#include "CBitset.hpp"


namespace tsr
{
    CBitset::CBitset()
    {
        m_bs = nullptr;
        m_size = 0;
    }
    CBitset::~CBitset()
    {
        if (m_bs != nullptr) {
            delete m_bs;
            m_bs = nullptr;
        }
    }

    void CBitset::SetSize(int size)
    {
        m_size = size;
        if (nullptr != m_bs) {
            delete m_bs;
            m_bs = nullptr;
        }
        m_bs = new char[(size + 8) / 8];
    }

    void CBitset::Set(int pos)
    {
        int bytes = pos / 8;
        int bits = pos % 8;

        char* oldvalue = (((char *)m_bs) + bytes);
        char newvalue = *oldvalue | (1 << bits);
        *oldvalue = newvalue;
    }

    bool CBitset::IsSet(int pos)
    {
        int bytes = pos / 8;
        int bits = pos % 8;

        char* value = (((char *)m_bs) + bytes);
        return (*value & (1 << bits));
    }
}