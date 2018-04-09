/**
 * @file
 * @author Манаев Константин
 * @brief Файл с реализацией объявленных в gil.h и внутренних классов и функций
 */
#include "gil.h"
#include <ostream>

namespace BMP {
    Bitmap::Bitmap(const char *fileName) {
        FILE *imageFile = fopen(fileName, "rb");
        if(nullptr == imageFile) throw std::ios_base::failure("Can't open file");
        if(-1 == fread(&bmfh, sizeof(FileHeader), 1, imageFile)) throw std::ios_base::failure("Can't read FileHeader");
        if(-1 == fread(&bmih, sizeof(InfoHeader), 1, imageFile)) throw std::ios_base::failure("Can't read InfoHeader");
        aColors = new RGB_32[bmih.biClrUsed];
        if(-1 == fread(aColors, sizeof(RGB_32), bmih.biClrUsed, imageFile)) throw std::ios_base::failure("Can't read color's table");
        aBitmapBits = new BYTE[bmih.biSizeImage];
        if(-1 == fread(aBitmapBits, bmih.biSizeImage , 1, imageFile)) throw std::ios_base::failure("Can't read color's table");
        fclose(imageFile);
    }

    Bitmap::Bitmap(DWORD width, DWORD height, WORD bitCount) {
        //@todo Реализовать конструктор Bitmap::Bitmap(DWORD width, DWORD height, WORD bitCount)
    }

    void Bitmap::Save(const char *filename) const {
        //@todo Реализовать метод void Bitmap::Save(const char *filename)
    }

    Bitmap::~Bitmap() {
        delete[] aColors;
        delete[] aBitmapBits;
    }

    ostream &operator<<(ostream &os, const Bitmap &bitmap) {
        os << "File header:" << std::endl;
        auto type = (char*)&bitmap.bmfh.bfType;
        os << "\tType: " << type[0] << type[1] << std::endl;
        os << "\tSize: " << bitmap.bmfh.bfSize << " byte" << std::endl;
        os << "\tOffset: " << bitmap.bmfh.bfOffBits << " byte" << std::endl;
        os << "Info:" << std::endl;
        os << "\tSize this block: " << bitmap.bmih.biSize << " byte" << std::endl;
        os << "\tImage width: " << bitmap.bmih.biWidth << " px" << std::endl;
        os << "\tImage height: " << bitmap.bmih.biHeight << " px" << std::endl;
        os << "\tColor planes: " << bitmap.bmih.biPlanes << std::endl;
        os << "\tImage height: " << bitmap.bmih.biHeight << " px" << std::endl;
        os << "\tDepth: " << bitmap.bmih.biBitCount << " bpp" << std::endl;
        os << "\tCompression: " << (bitmap.bmih.biCompression ? "true" : "false") << std::endl;
        os << "\tImage data size: " << bitmap.bmih.biSizeImage << " byte" << std::endl;
        os << "\tHorizontal resolution: " << bitmap.bmih.biXPelsPerMeter / 39 << " dpi" << std::endl;
        os << "\tVertical resolution: " << bitmap.bmih.biYPelsPerMeter / 39 << " dpi" << std::endl;
        os << "\tNumber of colors: " << bitmap.bmih.biClrUsed << std::endl;
        os << "\tNumber of important colors: " << bitmap.bmih.biClrImportant << std::endl;
        os << "Color's table:" << std::endl << "\t";
        char tmp[8];
        for(int i = 0; i < bitmap.bmih.biClrUsed; ++i) {
            if(i && !(i % 16)) os << std::endl << "\t";
            sprintf(tmp, "#%02X%02X%02X", bitmap.aColors[i].rgbRed, bitmap.aColors[i].rgbGreen, bitmap.aColors[i].rgbBlue);
            os << tmp << " ";
        }
        os << std::endl << "Image data:" << std::endl;
        for(int h = 0; h < bitmap.bmih.biHeight; ++h) {
            for(int w = 0; w < bitmap.bmih.biWidth; ++w) os << (int)bitmap.aBitmapBits[h * (4 - bitmap.bmih.biWidth % 4) % 4 + w] << " ";
            os << std::endl;
        }
        return os;
    }
}
