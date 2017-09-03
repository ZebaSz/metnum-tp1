#ifndef METNUM_TP1_CALIBRATION_H
#define METNUM_TP1_CALIBRATION_H

#include "mask.h"

struct direction{
    direction(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    double x;
    double y;
    double z;
};

/**
 * Calibrate the illumination sources, returning an array of directions
 *
 * @pre imgs must have all the same dimensions. imgs must not be empty.
 * @tparam vector<matrix<double>>
 * @param imgs the vector of matrixes of the images of the sphere
 */
vector<direction> calibrate(const vector<matrix<double> > &imgs, const &matrix<double> &mask) {
    assert(imgs.size() > 0);

    center_and_radius car = get_center_and_radius(mask);

    vector<direction> directions;
    int width = columns(imgs[0]);
    int height = height(imgs[0]);
    for (int k = 0; k < imgs.size(); k++) {
        double x;
        double y;
        double intensity = 0;
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (imgs[k][i][j] > intensity) {
                    intensity = imgs[k][i][j];
                    x = j - width / 2;
                    y = height / 2 - i;
                }
            }
        }

        double z = sqrt(pow(car.radius, 2) - pow(x - car.xCenter, 2) - pow(y - car.yCenter, 2));
        double norm2 = 
        direction normal()
    }
}

#endif //METNUM_TP1_CALIBRATION_H
