
#ifndef __CBITMAP_HPP__
#define __CBITMAP_HPP__
#include <vector>
#include "CColor.hpp"

namespace tsr
{
	class CBitmap
	{
	public:
		CBitmap();
		CBitmap(int w, int h);
		CBitmap(const CBitmap& bitmap);
		~CBitmap();

		void setSize(int w, int h);

	private:
		int  m_w;
		int  m_h;
		std::vector<CColor>   m_bitmap;
	public:
		// 获取宽度
		int getW() const;
		// 获取高度
		int getH() const;
		// 获取像素
		CColor& getPixel(int x, int y);
		// 设置坐标颜色
		int setPixel(int x, int y, const CColor& color);
		// 坐标是否合法
		bool isValidPixel(int x, int y);
		// 加载数据
		int load(char* file);
		// 保存位图到文件
		void save(char* file);
	};
}



#endif //__CBITMAP_HPP__
