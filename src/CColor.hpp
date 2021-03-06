/**/

#ifndef __CCOLOR_HPP__
#define __CCOLOR_HPP__
namespace tsr
{

	class CColor
	{
	public:
		CColor();
        CColor(int r, int g, int b);
		~CColor();

		int GetR() const { return m_r; }
		int GetG() const { return m_g; }
		int GetB() const { return m_b; }

        float GetH() const { return m_h; }
        float GetS() const { return m_s; }
        float GetV() const { return m_v; }

        int GetHi() const { return m_hi; }
        int GetSi() const { return m_si; }
        int GetVi() const { return m_vi; }

        int Tolerance(CColor& c);

		void Set(int r, int g, int b) { m_r = r; m_g = g; m_b = b; }
        void Set(int v) { m_r = v; m_g = v; m_b = v; }

        void Rgb2Hsv();
        void Hsv2Rgb();

        CColor& operator=(const CColor& rhs);
        CColor& operator-=(const CColor& rhs);

        bool IsPureWhite() { return (m_r == 255 && m_g == 255 && m_b == 255); }

        bool IsRed();
        bool IsGreen();

	private:
		int m_r;
		int	m_g;
		int m_b;

        float m_h;
        float m_s;
        float m_v;

        int m_hi;
        int m_si;
        int m_vi;
	};

}

#endif //__CCOLOR_HPP__