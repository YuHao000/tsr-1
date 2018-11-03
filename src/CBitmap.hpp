
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
		CBitmap(CBitmap& bitmap);
		~CBitmap();

		void SetSize(int w, int h);

	private:
		int  m_w;
		int  m_h;
		std::vector<CColor>   m_bitmap;
	public:
		// 获取宽度
		int GetW() const;
		// 获取高度
		int GetH() const;
		// 获取像素
		CColor& GetPixel(int x, int y);
		// 设置坐标颜色
		int SetPixel(int x, int y, const CColor& color);
		// 坐标是否合法
		bool IsValidPixel(int x, int y);
		// 加载数据
		int Load(char* file);
		// 保存位图到文件 RGB格式
		void Save(char* file);
        // 以HSV格式保存
        void SaveAsHsv(char* file);
        // 生成HSV信息
        void Rgb2Hsv();
        // 生成RGB信息
        void Hsv2Rgb();

        CBitmap& operator=(CBitmap& rhs);
	};
}



#endif //__CBITMAP_HPP__
