#include <iostream>
#include "utils.h"

using namespace std;

int main() {
    string filename;
    cout << "Ingresa la imagen a grayscalear" << endl;
    cin >> filename;
    Utils::saveGrayScaleImage(Utils::grayscalify(Utils::loadImage(filename), 0.25, 0.5, 0.25), "out_"+filename);
    cout << "Grayscaled:" << "out_"+filename << endl;

    return 0;
}
