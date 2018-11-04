#pragma once

#include <vector>
#include "CRect.hpp"
#include "CBitset.hpp"

namespace tsr
{
    class CPointSet
    {
    public:
        CPointSet(int w, int h);
        ~CPointSet();

        void Add(int x, int y);
        void CalcRect() { m_rect.Set(m_lx, m_ly, m_rx - m_lx, m_ry - m_ly); }
        CRect &GetRect() { return m_rect; }

        void push_back(int x, int y);
        int  size() { return m_ps.size(); }

        std::pair<int, int>& operator[](int i);

    private:
        std::vector<std::pair<int, int> >   m_ps;   // point set
        CRect                               m_rect; 
        int                                 m_lx;
        int                                 m_ly;
        int                                 m_rx;
        int                                 m_ry;
        CBitset                             m_bs;   // bit set
    };
}


