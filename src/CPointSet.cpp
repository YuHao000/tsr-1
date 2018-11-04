
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
        m_greenNum = 0;
        m_redNum = 0;
        m_type = PS_UNMARK;
    }

    CPointSet::~CPointSet()
    {
    }

    void CPointSet::Add(int x, int y, CColor& color)
    {
        m_ps.push_back(std::make_pair(x, y));
        m_lx = MIN(m_lx, x);
        m_ly = MIN(m_ly, y);
        m_rx = MAX(m_rx, x);
        m_ry = MAX(m_ry, y);

        if (color.IsGreen()) {
            m_greenNum++;
        }
        else if (color.IsRed()) {
            m_redNum++;
        }
    }

    void CPointSet::push_back(int x, int y, CColor& color)
    {
        Add(x, y, color);
    }

    std::pair<int, int>& CPointSet::operator[](int i)
    {
        return m_ps[i];
    }

    //PS_TYPE_E CPointSet::GetType()
    //{
    //    /* 如果绿点占了90%以上，则认为是绿灯 */
    //    if ((float)m_greenNum > (m_ps.size() * 0.9)) {
    //        return PS_GREEN_LIGHT;
    //    }

    //    /* 红绿灯是实心 */
    //    if (m_ps.size() > m_rect.Aera() * 0.5) {
    //        return PS_RED_LIGHT;
    //    }


    //}
}
