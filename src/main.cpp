#include <iostream>
#include "utils.h"
#include "reconstruct3d.h"

using namespace std;

void saveSampleNormalField() {
    matrix<double> i1 = Utils::grayscalify(Utils::loadImage("mate.0.ppm"), 0.25, 0.5, 0.25);
    matrix<double> i2 = Utils::grayscalify(Utils::loadImage("mate.1.ppm"), 0.25, 0.5, 0.25);
    matrix<double> i3 = Utils::grayscalify(Utils::loadImage("mate.2.ppm"), 0.25, 0.5, 0.25);
    matrix<row<double>> res = normalField(i1, i2, i3, direction(0.403259, 0.480808, 0.778592), direction(0.0982272, 0.163712, 0.981606), direction(-0.0654826, 0.180077, 0.98147), options(true));
    Utils::saveMatrix3dFiles(res, "mate");
}

string SPHERE = "mate";
string FIGURE = "mate";
string PICTURES[3] = {"0", "1", "2"};
double R_GRAYSCALE = 0.25;
double G_GRAYSCALE = 0.5;
double B_GRAYSCALE = 0.25;
options OPTS = options(false);
bool SAVE_NORMAL = true;

matrix<double> loadGrayImage(string filename) {
    return Utils::grayscalify(Utils::loadImage(filename), R_GRAYSCALE, G_GRAYSCALE, B_GRAYSCALE);
}

vector<matrix<double>> loadGrayImages(string figure) {
    return {
        loadGrayImage(figure+"."+PICTURES[0]+".ppm"),
        loadGrayImage(figure+"."+PICTURES[1]+".ppm"),
        loadGrayImage(figure+"."+PICTURES[2]+".ppm")
    };
}

int main() {
    //----CALIBRATION
    matrix<double> sphereMask = loadGrayImage(SPHERE+".mask.ppm");
    vector<matrix<double>> spheres = loadGrayImages(SPHERE);
    vector<direction> calibrations = Calibration::calibrate(spheres, sphereMask);
    //----LOADING
    matrix<double> mask = loadGrayImage(FIGURE+".mask.ppm");
    vector<matrix<double>> imgs = loadGrayImages(FIGURE);
    //----NORMAL-FIELD
    matrix<row<double>> normal = normalField(imgs[0], imgs[1], imgs[2], calibrations[0], calibrations[1], calibrations[2], OPTS);
    if (SAVE_NORMAL) {
        Utils::saveMatrix3dFiles(normal, FIGURE);
    }
    //----DEPTH
    matrix<double> depth = findDepth(normal);
    Utils::saveMatrixFile(depth, FIGURE + ".depth.csv");
    //----END
    return 0;
}
