
#include "Common.hpp"
#include "CPointSet.hpp"


namespace tsr
{
    CPointSet::CPointSet(int w, int h)
    {
        m_lx = w;
        m_ly = h;
        m_rx = 0;
        m_ry = 0;
    }


    CPointSet::~CPointSet()
    {
    }

    void CPointSet::Add(int x, int y)
    {
        m_ps.push_back(std::make_pair(x, y));
        m_lx = MIN(m_lx, x);
        m_ly = MIN(m_ly, y);
        m_rx = MAX(m_rx, x);
        m_ry = MAX(m_ry, y);
    }

    void CPointSet::push_back(int x, int y)
    {
        Add(x, y);
    }

    std::pair<int, int>& CPointSet::operator[](int i)
    {
        return m_ps[i];
    }
}
