#include <iostream>
#include "utils.h"
#include "reconstruct3d.h"

using namespace std;

#define PICTURE_NO(pic,n) figure+"."+PICTURES[n]+".ppm"
#define PICTURE_MASK(pic) pic+".mask.ppm"

void saveSampleNormalField() {
    matrix<double> i1 = Utils::loadGrayImage("mate.0.ppm");
    matrix<double> i2 = Utils::loadGrayImage("mate.1.ppm");
    matrix<double> i3 = Utils::loadGrayImage("mate.2.ppm");
    matrix<row<double>> res = normalField(
            i1, i2, i3,
            direction(0.403259, 0.480808, 0.778592),
            direction(0.0982272, 0.163712, 0.981606),
            direction(-0.0654826, 0.180077, 0.98147),
            options(true));
    Utils::saveMatrix3dFiles(res, "mate");
}

string SPHERE = "mate";
string FIGURE = "caballo";
string PICTURES[3] = {"0", "1", "2"};
options OPTS = options(false);
bool SAVE_NORMAL = true;

vector<matrix<double>> loadGrayImages(string figure) {
    return {
        Utils::loadGrayImage(PICTURE_NO(figure, 0)),
        Utils::loadGrayImage(PICTURE_NO(figure, 1)),
        Utils::loadGrayImage(PICTURE_NO(figure, 2))
    };
}

int main() {
    //----CALIBRATION
    matrix<double> sphereMask = Utils::loadGrayImage(PICTURE_MASK(SPHERE));
    vector<matrix<double>> spheres = loadGrayImages(SPHERE);
    vector<direction> calibrations = Calibration::calibrate(spheres, sphereMask);
    //----LOADING
    matrix<double> mask = Utils::loadGrayImage(PICTURE_MASK(FIGURE));
    vector<matrix<double>> imgs = loadGrayImages(FIGURE);
    //----NORMAL-FIELD
    matrix<row<double>> normal = normalField(
            imgs[0], imgs[1], imgs[2],
            calibrations[0], calibrations[1], calibrations[2], OPTS);
    if (SAVE_NORMAL) {
        Utils::saveMatrix3dFiles(normal, FIGURE);
    }
    //----DEPTH
    matrix<double> depth = findDepth(normal);
    Utils::saveMatrixFile(depth, FIGURE + ".depth.csv");
    //----END
    return 0;
}
