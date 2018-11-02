/**/

#ifndef __CCOLOR_HPP__
#define __CCOLOR_HPP__
namespace tsr
{

	class CColor
	{
	public:
		CColor();
		~CColor();

		int getR() { return m_r; }
		int getG() { return m_g; }
		int getB() { return m_b; }

		void set(int r, int g, int b) { m_r = r; m_g = g; m_b = b; }

	private:
		int m_r;
		int	m_g;
		int m_b;
	};

}

#endif //__CCOLOR_HPP__