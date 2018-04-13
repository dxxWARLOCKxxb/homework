/**
 * @file
 * @author Манаев Константин
 * @brief Файл с реализацией объявленных в gil.h и внутренних классов и функций
 */
#include "gil.h"
#include <ostream>
#include <cstring>
#include <cmath>

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
        bmfh.bfType = 0x4D42;
        bmfh.bfReserved1 = 0;
        bmfh.bfReserved2 = 0;

        bmih.biSize = 0x28;
        bmih.biWidth = width;
        bmih.biHeight = height;
        bmih.biPlanes = 0x1;
        bmih.biBitCount = bitCount;
        bmih.biCompression = 0;
        bmih.biSizeImage = height * (width + (4 - width % 4) % 4);
        bmih.biXPelsPerMeter = 0xB13;
        bmih.biYPelsPerMeter = 0xB13;
        bmih.biClrUsed = static_cast<DWORD>(1u << bmih.biBitCount);
        bmih.biClrImportant = static_cast<DWORD>(1u << bmih.biBitCount);

        bmfh.bfOffBits = sizeof(FileHeader) + sizeof(InfoHeader) + sizeof(RGB_32) * bmih.biClrUsed;
        bmfh.bfSize = bmfh.bfOffBits + bmih.biSizeImage;

        aColors = new RGB_32[bmih.biClrUsed];
        for(int i = 0; i < bmih.biClrUsed; ++i) {
            aColors[i].rgbBlue = static_cast<BYTE>(i);
            aColors[i].rgbGreen = static_cast<BYTE>(i);
            aColors[i].rgbRed = static_cast<BYTE>(i);
            aColors[i].rgbReserved = 0;
        }
        aBitmapBits = new BYTE[bmih.biSizeImage];
        memset(aBitmapBits, 0, bmih.biSizeImage * sizeof(BYTE));
    }

    void Bitmap::Save(const char *filename) const {
        FILE *imageFile = fopen(filename, "wb");
        if(nullptr == imageFile) throw std::ios_base::failure("Can't open file");
        if(-1 == fwrite(&bmfh, sizeof(FileHeader), 1, imageFile)) throw std::ios_base::failure("Can't write FileHeader");
        if(-1 == fwrite(&bmih, sizeof(InfoHeader), 1, imageFile)) throw std::ios_base::failure("Can't write InfoHeader");
        if(-1 == fwrite(aColors, sizeof(RGB_32), bmih.biClrUsed, imageFile)) throw std::ios_base::failure("Can't write color's table");
        if(-1 == fwrite(aBitmapBits, bmih.biSizeImage , 1, imageFile)) throw std::ios_base::failure("Can't write color's table");
        fclose(imageFile);
    }

    Bitmap::~Bitmap() {
        if(__last_gistogram != nullptr) delete __last_gistogram;
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
        if(bitmap.bmih.biSizeImage > 512) return os << "is big" << std::endl;
        for(int h = 0; h < bitmap.bmih.biHeight; ++h) {
            for(int w = 0; w < bitmap.bmih.biWidth; ++w) os << (int)bitmap.aBitmapBits[h * (bitmap.bmih.biWidth + (4 - bitmap.bmih.biWidth % 4) % 4) + w] << " ";
            os << std::endl;
        }
        return os;
    }

    Bitmap::Bitmap(const Bitmap &Clone) {
        bmfh = Clone.bmfh;
        bmih = Clone.bmih;
        aColors = new RGB_32[bmih.biClrUsed];
        memcpy(aColors, Clone.aColors, sizeof(RGB_32) * bmih.biClrUsed);
        aBitmapBits = new BYTE[bmih.biSizeImage];
        memcpy(aBitmapBits, Clone.aBitmapBits, sizeof(BYTE) * bmih.biSizeImage);
    }

    Bitmap &Bitmap::blending(const Bitmap &src, const Bitmap &alpha) {
        if(this->bmih.biWidth != src.bmih.biWidth && this->bmih.biHeight != src.bmih.biHeight &&
           this->bmih.biWidth != alpha.bmih.biWidth && this->bmih.biHeight != alpha.bmih.biHeight)
            throw std::invalid_argument("Dimensions do not match");
        if(this->bmih.biBitCount != src.bmih.biBitCount && this->bmih.biBitCount != alpha.bmih.biBitCount)
            throw std::invalid_argument("Depth do not match");

        int index = 0;
        for(int h = 0; h < this->bmih.biHeight; ++h) {
            for(int w = 0; w < this->bmih.biWidth; ++w) {
                index = h * (this->bmih.biWidth + (4 - this->bmih.biWidth % 4) % 4) + w;
                float alpha_value = (float) alpha.aBitmapBits[index] / (alpha.bmih.biClrUsed - 1);
                this->aBitmapBits[index] = (BYTE) ((1 - alpha_value) * src.aBitmapBits[index] + alpha_value * this->aBitmapBits[index]);
            }
        }
        return *this;
    }

    Bitmap & Bitmap::reflection(DIRECTION direction) {
        auto realWidth = this->bmih.biWidth + (4 - this->bmih.biWidth % 4) % 4;
        if(direction == RL_HORIZONTAL) {
            auto tmp_data = new BYTE[this->bmih.biSizeImage];
            memcpy(tmp_data, this->aBitmapBits, this->bmih.biSizeImage);
            BYTE* end_data = tmp_data + this->bmih.biSizeImage;
            for(auto i = 0; i < this->bmih.biHeight; ++i)
                memcpy(this->aBitmapBits + i * realWidth,end_data - (i + 1) * realWidth, realWidth);
            delete[] tmp_data;
        } else {
            BYTE swap = 0;
            for(int h = 0; h < this->bmih.biHeight; ++h) {
                for(int w = 0; w < this->bmih.biWidth / 2; ++w) {
                    swap = this->aBitmapBits[h*realWidth + w];
                    this->aBitmapBits[h*realWidth + w] = this->aBitmapBits[h*realWidth + this->bmih.biWidth - 1 - w];
                    this->aBitmapBits[h*realWidth + this->bmih.biWidth - 1 - w] = swap;
                }
            }
        }
        return *this;
    }

    Bitmap &Bitmap::rotation(const float angle) {
        if(angle != 90)
            throw std::invalid_argument("Rotation work on 90 degree");
        auto old_real_width = bmih.biWidth + (4 - bmih.biWidth % 4) % 4;
        auto new_real_width = bmih.biHeight + (4 - bmih.biHeight % 4) % 4;
        auto tmp_data = aBitmapBits;
        auto swap = bmih.biHeight;
        bmih.biHeight = bmih.biWidth;
        bmih.biWidth = swap;
        aBitmapBits = new BYTE[new_real_width * bmih.biHeight];
        for(auto h = 0; h < bmih.biHeight; ++h) {
            for(auto w = 0; w < bmih.biWidth; ++w) {
                aBitmapBits[h * new_real_width + w] = tmp_data[w * old_real_width + h];
            }
        }
        delete[] tmp_data;
        return *this;
    }

    Gistogram &Bitmap::getGistogram() {
        if(__last_gistogram != nullptr) delete __last_gistogram;
        __last_gistogram = new Gistogram(*this);
        return *__last_gistogram;
    }

    BMP::Gistogram::Gistogram(const Bitmap &image) {
        __mean__  = 0, __variance__ = 0, __entropy__ = 0;
        __uniformity__ = 0, __skewness__ = 0, __kurtosis__ = 0;

        auto real_width = image.bmih.biWidth + (4 - image.bmih.biWidth % 4) % 4;
        size = image.bmih.biClrUsed;
        __data = new DWORD[size];
        memset(__data, 0, sizeof(DWORD) * image.bmih.biClrUsed);

        for(auto h = 0; h < image.bmih.biHeight; ++h)
            for(auto w = 0; w < image.bmih.biWidth; ++w)
                __data[image.aBitmapBits[h * real_width + w]]++;

        point_counts = image.bmih.biWidth * image.bmih.biHeight;

        __scale_col__ = __data[0];
        for(auto i = 0; i < size; ++i) {
            if(__data[i] > __scale_col__) __scale_col__ = __data[i];
            __mean__ += (__data[i] * i);
        }
        __mean__ /= point_counts;
        __scale_col__ /= 140;

        for(auto i = 0; i < size; ++i) {
            __variance__ += pow((__data[i] - __mean__), 2) * i;
            __kurtosis__ += pow((__data[i] - __mean__), 4) * i;
            __skewness__ += pow((__data[i] - __mean__), 3) * i;
            __uniformity__ += pow(__data[i], 2) / point_counts;
            __entropy__ -= __data[i] * log2(__data[i] / point_counts) / point_counts;
        }

        __variance__ /= point_counts;

        __kurtosis__ /= pow(__variance__, 2);
        __kurtosis__ -= 3;

        __skewness__ /= pow(__variance__, 1.5);

        __uniformity__ /= point_counts;

//        __entropy__ /= point_counts;
    }

    ostream &operator<<(ostream &os, const Gistogram &gistogram) {
        for(auto i = 0; i < gistogram.size; ++i) {
            os << "[" << i << "] \t| ";
            for(auto j = 0; j < (int) (gistogram.__data[i] / gistogram.__scale_col__); ++j) os << ":";
            os << "(" << gistogram.__data[i] << ")" << std::endl;
        }
        return os;
    }

    Gistogram::Gistogram(const Gistogram &Clone) {
        *this = Clone;
        __data = new DWORD[size];
        memcpy(__data, Clone.__data, sizeof(DWORD) * size);
    }

    Gistogram::~Gistogram() {
        delete[] __data;
    }

}
