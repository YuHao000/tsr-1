#include "CBitmap.hpp"
#include "Common.hpp"
#include <fstream>

namespace tsr
{
	CBitmap::CBitmap()
	{
	}

	CBitmap::CBitmap(int w, int h)
	{
		setSize(w, h);
	}

	CBitmap::CBitmap(const CBitmap& bitmap)
	{
		setSize(bitmap.getW(), bitmap.getH());
		
	}

	CBitmap::~CBitmap()
	{
	}

	void CBitmap::setSize(int w, int h)
	{
		m_w = w;
		m_h = h;
		m_bitmap.resize(w * h);
		return;
	}

	// 获取宽度
	int CBitmap::getW() const
	{
		return m_w;
	}

	// 获取高度
	int CBitmap::getH() const
	{
		return m_h;
	}

	CColor& CBitmap::getPixel(int x, int y)
	{
		return m_bitmap[x * m_h + y];
	}

	int CBitmap::setPixel(int x, int y, const CColor& color)
	{
		TRUE_RET(isValidPixel(x, y), RET_ERR);
	    m_bitmap[x * m_h + y] = color;
		return RET_OK;
	}

	bool CBitmap::isValidPixel(int x, int y)
	{
		return ((x >= 0 && x < m_w) && (y >= 0 && y < m_h));
	}

	int CBitmap::load(char* file)
	{
		std::ifstream fin(file);

		fin >> m_w >> m_h;
		setSize(m_w, m_h);

		int red, green, blue;
		for (int x = 0; x < m_w; x++)
		{
			for (int y = 0; y < m_h; y++)
			{
				CColor& color = getPixel(x, y);
				fin >> red >> green >> blue;
				color.set(red, green, blue);
			}
		}
		return RET_OK;
	}

	void CBitmap::save(char* file)
	{
		std::ofstream  fout(file);
		
		fout << m_w << " " << m_h << std::endl;

		for (int i = 0; i < m_w; i++)
		{
			for (int j = 0; j < m_h; j++)
			{
				CColor& color = getPixel(i, j);
				fout << color.getR() << " " << color.getG() << " " << color.getB() << std::endl;
			}
		}
		return;
	}
}


