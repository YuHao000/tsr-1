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
        m_bs = NULL;
        m_size = 0;
    }
    CBitset::~CBitset()
    {
        if (m_bs != NULL) {
            free(m_bs);
            m_bs = NULL;
        }
    }

    void CBitset::SetSize(int size)
    {
        m_size = size;
        if (NULL != m_bs) {
            free(m_bs);
            m_bs = NULL;
        }
        m_bs = malloc((size + 8) / 8);
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