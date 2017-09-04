#include <iostream>
#include "utils.h"
#include "calibration.h"

int main() {
<<<<<<< d6ab0c84e03f42ceeaa41f824d593d142fd982c5
    std::string filename;
    std::cout << "Ingresa la imagen a grayscalear" << std::endl;
    std::cin >> filename;
    Utils::saveGrayScaleImage(Utils::grayscalify(Utils::loadImage(filename), 0.25, 0.5, 0.25), "out_"+filename);
    std::cout << "Grayscaled:" << "out_"+filename << std::endl;

    std::cout << "Naxio, este entregable está rancio" << std::endl;
=======
    string filename;
    // cout << "Ingresa la imagen a grayscalear" << endl;
    // cin >> filename;
    matrix<double> img = Utils::grayscalify(Utils::loadImage("mate.0.ppm"), 0.25, 0.5, 0.25);
    // Utils::saveGrayScaleImage(img, "out_"+filename);
    // cout << "Grayscaled:" << "out_"+filename << endl;

    cout << "R: " << Matrix::rows(img) << " C: " << Matrix::columns(img) << endl;

    // cout << "Ingresa la máscara" << endl;
    // cin >> filename;
    matrix<double> mask = Utils::grayscalify(Utils::loadImage("mate.mask.ppm"), 0.25, 0.5, 0.25);

    vector<matrix<double> > imgs;
    imgs.push_back(img);
    vector<direction> lightSources = Calibration::calibrate(imgs, mask);
    for (int i = 0; i < lightSources.size(); i++)
    	cout << lightSources[i];
>>>>>>> Complete calibration, but maybe not working properly
    return 0;
}
