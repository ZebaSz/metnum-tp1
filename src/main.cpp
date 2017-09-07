#include <iostream>
#include "utils.h"
#include "reconstruct3d.h"

using namespace std;

int main() {
    matrix<double> i1 = Utils::grayscalify(Utils::loadImage("caballo.0.ppm"), 0.25, 0.5, 0.25);
    matrix<double> i2 = Utils::grayscalify(Utils::loadImage("caballo.1.ppm"), 0.25, 0.5, 0.25);
    matrix<double> i3 = Utils::grayscalify(Utils::loadImage("caballo.2.ppm"), 0.25, 0.5, 0.25);
    matrix<row<double>> res = normalField(i1, i2, i3, direction(0.403259, 0.480808, 0.778592), direction(0.0982272, 0.163712, 0.981606), direction(-0.0654826, 0.180077, 0.98147), options(false));
    Utils::saveMatrix3dFiles(res, "mate");
    return 0;
}
