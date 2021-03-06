/*
 * @authur   liyi_whu@163.com
 * @date     20181102
 * @note	 加载图片的相关操作
 */

#ifndef __LOADER_HPP__
#define __LOADER_HPP__
#include <string>
#include "CBitmap.hpp"

namespace tsr
{
	class CPicLoader {
	public:
		CPicLoader(char* pic, CBitmap& bitmap);
		~CPicLoader();

		int Load();
        void SetBitMap(CBitmap& bitmap) { m_bitmap = &bitmap; }
        void SetFile(char* path) { m_file = path; }
        void Set(char* path, CBitmap &bitmap) { SetFile(path); SetBitMap(bitmap); }
		int SaveAsJpg(const char* dst);
	private:
		std::string		m_file;
		CBitmap		    *m_bitmap;
		uint64_t		m_token;
	};
}

#endif // !__LOADER_HPP__
