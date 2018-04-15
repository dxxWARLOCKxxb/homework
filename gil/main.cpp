#include <iostream>
#include <unistd.h>

//#include "TheMatrix/matrix.h"
#include "gil.h"

int main() {
    /**
     * @name comp_pi-3
     * @todo Реализовать произвольный поворот, с использованием бикубической интерполяции
     * @}
     * @name comp_pi-4
     * @todo Реализовать преобразование изображения 8 bpp в n bpp (n < 8) с использованием алгоритма рассеяния ошибки Флойда-Стенберга.
     * @note Допускается упрощенная реализация, при которой результат хранится в виде 8 bpp, но каждый пиксел может иметь только одно из 2-х допустимых значений.
     * @}
     * @todo Перевести на многопоточные матрицы!
     */
    auto Image1 = BMP::Bitmap("/home/esdeath/Загрузки/brick.bmp");
    int c = 179, r = 167;
    for(int i = 0; i < 10; i++)
        for(int j = 0; j < 10; j++) {
            std::string s = "/home/esdeath/Загрузки/Image1/" + std::to_string(i) + "_" + std::to_string(j) + ".bmp";
            auto tmp = Image1.getCooccurrenceMatrix(i, j);
            (*tmp).SaveAsBitmap(s.c_str());
            //delete tmp; // Если освобождать память, то на диск пишет фигню почти все белое (что странно, обычно черный т.к. 0)
        }
    auto gist = Image1.getGistogram();
    cout << gist;
    cout << "\nсреднее: " << gist.mean() << "\nдисперсия: " << gist.variance() << "\nэнтропия: " << gist.entropy();
    cout << "\nэнергия: " << gist.uniformity() << "\nасимметрия: " << gist.skewness() << "\nэксцесс: " << gist.kurtosis();
    cout << endl;
//    auto Image2 = BMP::Bitmap("/home/esdeath/Загрузки/image2.bmp");
//    auto AlphaImage = BMP::Bitmap("/home/esdeath/Загрузки/alpha_image.bmp");
//    Image1.blending(Image2, AlphaImage).reflection(BMP::RL_VERTICAL).reflection(BMP::RL_HORIZONTAL);
//    Image1.Save("/home/esdeath/Загрузки/blending_vertical_and_horizontal_reflection.bmp");
//    Image1.rotation(90).Save("/home/esdeath/Загрузки/rotate90_image1.bmp");
    return 0;
}