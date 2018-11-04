#pragma once

#include <vector>
#include <bitset>
#include "CRect.hpp"
#include "CBitset.hpp"
#include "CColor.hpp"

namespace tsr
{
    enum PS_TYPE_E{
        PS_RED_LIGHT = 0,
        PS_GREEN_LIGHT,
        PS_SPEED_LIMIT,
        PS_FORBID_TURN,
        PS_UNMARK,  /*Î´Ê¶±ð¹ý*/
        PS_OTHER
    };
    class CPointSet
    {
    public:
        CPointSet(int w, int h);
        ~CPointSet();

        void Add(int x, int y, CColor& color);
        void CalcRect() { m_rect.Set(m_lx, m_ly, m_rx - m_lx, m_ry - m_ly); }
        CRect &GetRect() { return m_rect; }

        int GetRNum() { return m_redNum; }
        int GetGNum() { return m_greenNum; }

        int GetRectArea() { return m_rect.Aera(); }

        void  SetType(PS_TYPE_E type) { m_type = type; }
        PS_TYPE_E GetType() { return m_type; }

        void push_back(int x, int y, CColor& color);
        int  size() { return m_ps.size(); }

        std::pair<int, int>& operator[](int i);

    private:
        std::vector<std::pair<int, int> >   m_ps;   // point set
        CRect                               m_rect; 
        int                                 m_lx;
        int                                 m_ly;
        int                                 m_rx;
        int                                 m_ry;
        int                                 m_redNum;
        int                                 m_greenNum;

        PS_TYPE_E                           m_type;
    };
}


