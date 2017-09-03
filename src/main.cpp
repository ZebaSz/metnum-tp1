#include <iostream>
#include "utils.h"

int main() {
    std::string filename;
    std::cout << "Ingresa la imagen a grayscalear" << std::endl;
    std::cin >> filename;
    Utils::saveGrayScaleImage(Utils::grayscalify(Utils::loadImage(filename), 0.25, 0.5, 0.25), "out_"+filename);
    std::cout << "Grayscaled:" << "out_"+filename << std::endl;

    std::cout << "Naxio, este entregable está rancio" << std::endl;
    return 0;
}
