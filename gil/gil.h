/**
 * @headerfile
 * @author Манаев Константин
 * @brief Классы и функций необходимые для выполнения лаборатоных работ по дисциплине "Компьютерная обработка изображений"
 * @warning Для работы рекомендуется использовать только функции классы, размещенные в namespace BMP
 */
#ifndef GIL_GIL_H
#define GIL_GIL_H

#include <cstdint>
#include <ostream>
using namespace std;

typedef std::uint32_t DWORD;///<@brief 4-х байтовый беззнаковый целочисленный тип (двойное слово)
typedef std::uint16_t WORD;///<@brief 2-х байтовый беззнаковый целочисленный тип (слово)
typedef std::uint8_t  BYTE;///<@brief Байтовый беззнаковый целочисленный тип (байт)

/**
 * @brief Структура, описывающая заголовок BMP файла.
 */
#pragma pack(push, 1)
typedef struct {
    WORD  bfType;///<@memberof ^FileHeader @brief Тип BMP, возможные значения: BM, BA, CI, CP, IC, PT. @warning В лаб.работах используется BM.
    DWORD bfSize;///<@brief Размер файла в байтах.
    WORD  bfReserved1;///<@brief служебное поле.
    WORD  bfReserved2;///<@brief служебное поле.
    DWORD bfOffBits;///<@brief Смещение от начала файла до таблицы с пикселами.
} FileHeader;
#pragma pack(pop)

/**
 * @brief Структура, описывающая информационный блок BMP файла.
 */
#pragma pack(push, 1)
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
#pragma pack(pop)

/***
 * @brief Структура, описывающая цвет.
 * @warning Каналы записаны в обратном порядке, т.е. ABGR,а не RGBA
 */
#pragma pack(push, 1)
typedef struct {
    BYTE rgbBlue;///<@brief Значение синего канала
    BYTE rgbGreen;///<@brief Значение зеленого канала
    BYTE rgbRed;///<@brief Значение красного канала
    BYTE rgbReserved;///<@warning Походу всегда 0 в BMP grayscale 8bpp
} RGB_32;
#pragma pack(pop)

/***
 * @namespace BMP
 * @brief Основное рабочее пространство имен библиотеки.
 * @warning В приложениях не рекомендуется использовать классы и функции, объявленные вне этого пространнства имен.
 */
namespace BMP {
    typedef bool DIRECTION ;
    const DIRECTION RL_VERTICAL = false;
    const DIRECTION RL_HORIZONTAL = true;

    /***
     * @class Bitmap
     * @brief Класс для работы с файлами формата .bmp
     * @warning На данный момент функциональность ограничена (например, читаются только несжатые файлы).
     */
    class Bitmap {
    private:
        FileHeader bmfh;///<@brief Заголовок файла.
        InfoHeader bmih;///<@brief Информационны блок файла.
        RGB_32     *aColors;///<@brief Таблица цветов, количество цветов можно узнать в bmih.biClrUsed. Каждый цвет представляет RGB_32
        BYTE       *aBitmapBits;///<@brief Таблица пикселов. @warning Используется выравнивание до 4 байт, т.е. если ширина изображение 6 пикселов, то размер строки будет не 6 байт, а 8 байт
    public:
        explicit Bitmap(const char* fileName) noexcept(false);///<@brief Конструктор, загружающий изображение из файла. @param [in] fileName Строка, описывающая путь к файлу.
        /***
         * @brief Конструктор, создающий пустое изображение указанного размера.
         * @param [in] width Ширина изображения в пикселах
         * @param [in] height Высота изображения в пикселах
         * @param [in] bitCount Глубина цвета бит/пиксел. По умолчанию 8.
         */
        Bitmap(DWORD width, DWORD height, WORD bitCount = 8);
        /***
         * @brief Конструктор клонирования
         * @param [in] Clone - клонируемое изображение
         */
        Bitmap(const Bitmap &Clone);
        void Save(const char* filename) const noexcept(false);///<@brief Метод, сохраняющий изображение в файл. @param [in] fileName Строка, описывающая путь к файлу.
        friend ostream &operator<<(ostream &os, const Bitmap &bitmap);
        virtual ~Bitmap();///<Обычный деконструктор.

        /***
         * @brief Смешивание двух изображений одинакого размера, используя тертье в качестве альфа-канала
         * @param src - второе смешиваемое изображение
         * @param alpha - изображение альфа-канал
         * @return Ссылку на измененное изображение
         * @throw std::invalid_argument, если размеры изображения или глубина цвета не совпадают.
         * @warning Изменяет текущий объект!
         */
        Bitmap& blending(const Bitmap &src, const Bitmap &alpha) noexcept(false);
        /***
         * @brief Отражает текущее изображение
         * @param [in] direction - определяет направление отражения, значения: [RL_VERTICAL, RL_HORIZONTAL]
         * @return Ссылку на измененное изображение
         */
        Bitmap & reflection(DIRECTION direction);
    };
}

#endif //GIL_GIL_H
