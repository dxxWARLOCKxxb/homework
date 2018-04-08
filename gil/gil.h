/**
 * @headerfile
 * @author Манаев Константин
 * @brief Классы и функций необходимые для выполнения лаборатоных работ по дисциплине "Компьютерная обработка изображений"
 * @warning Для работы рекомендуется использовать только функции классы, размещенные в namespace BMP
 */
#ifndef GIL_GIL_H
#define GIL_GIL_H

#include <cstdint>

typedef std::uint32_t DWORD;///<@brief 4-х байтовый беззнаковый целочисленный тип (двойное слово)
typedef std::uint16_t WORD;///<@brief 2-х байтовый беззнаковый целочисленный тип (слово)
typedef std::uint8_t  BYTE;///<@brief Байтовый беззнаковый целочисленный тип (байт)

/**
 * @brief Структура, описывающая заголовок BMP файла.
 */
typedef struct {
    WORD  bfType;///<@memberof ^FileHeader @brief Тип BMP, возможные значения: BM, BA, CI, CP, IC, PT. @warning В лаб.работах используется BM.
    DWORD bfSize;///<@brief Размер файла в байтах.
    WORD  bfReserved1;///<@brief служебное поле.
    WORD  bfReserved2;///<@brief служебное поле.
    DWORD bfOffBits;///<@brief Смещение от начала файла до таблицы с пикселами.
} FileHeader;

/**
 * @brief Структура, описывающая информационный блок BMP файла.
 */
typedef struct {
    DWORD biSize;///<@brief Размер информационного блока в байтах.
    DWORD biWidth;///<@brief Ширина изображения в пикселах.
    DWORD biHeight;///<@brief Высота изображения в пикселах.
    WORD  biPlanes;///<@brief служебное поле, всегда равно 1.
    WORD  biBitCount;///<@brief Количество бит, кодирующих цвет пиксела.
    DWORD biCompression;///<@brief Метод сжатия. @warning На данный момент поддерживается только несжатые файлы.
    DWORD biSizeImage;///<@brief Размер таблицы с пикселами в байтах.
    DWORD biXPelsPerMeter;///<@brief Горизонтальное разрешение изображения pixel/m (resolution).
    DWORD biYPelsPerMeter;///<@brief Вертикальное разрешение изображения pixel/m (resolution).
    DWORD biClrUsed;///<@brief Количество цветов в палитре.
    DWORD biClrImportant;///<@brief Количество используемых цветов, 0 если используются все. @warning Как правило не используется.
} InfoHeader;

/***
 * @brief Структура, описывающая цвет.
 * @warning Каналы записаны в обратном порядке, т.е. ABGR,а не RGBA
 */
typedef struct {
    BYTE rgbBlue;///<@brief Значение синего канала
    BYTE rgbGreen;///<@brief Значение зеленого канала
    BYTE rgbRed;///<@brief Значение красного канала
    BYTE rgbReserved;///<@warning Походу всегда 0 в BMP grayscale 8bpp
} RGB_32;

/***
 * @namespace BMP
 * @brief Основное рабочее пространство имен библиотеки.
 * @warning В приложениях не рекомендуется использовать классы и функции, объявленные вне этого пространнства имен.
 */
namespace BMP {
    /***
     * @class Bitmap
     * @brief Класс для работы с файлами формата .bmp
     * @warning На данный момент функциональность ограничена (например, читаются только несжатые файлы).
     */
    class Bitmap {
    private:
        FileHeader bmfh;///<@brief Заголовок файла.
        InfoHeader bmih;///<@brief Информационны блок файла.
        RGB_32     aColors[];///<@brief Таблица цветов, количество цветов можно узнать в bmih.biClrUsed. Каждый цвет представляет RGB_32
        BYTE       aBitmapBits[];///<@brief Таблица пикселов. @warning Используется выравнивание до 4 байт, т.е. если ширина изображение 6 пикселов, то размер строки будет не 6 байт, а 8 байт
    public:
        explicit Bitmap(const char* fileName);///<@brief Конструктор, загружающий изображение из файла. @param [in] fileName Строка, описывающая путь к файлу.
        /***
         * @brief Конструктор, создающий пустое изображение указанного размера.
         * @param [in] width Ширина изображения в пикселах
         * @param [in] height Высота изображения в пикселах
         * @param [in] bitCount Глубина цвета бит/пиксел. По умолчанию 8.
         */
        Bitmap(DWORD width, DWORD height, WORD bitCount = 8);
        void Save(const char* filename) const;///<@brief Метод, сохраняющий изображение в файл. @param [in] fileName Строка, описывающая путь к файлу.
        virtual ~Bitmap();///<Обычный деконструктор.
    };
}
#endif //GIL_GIL_H
