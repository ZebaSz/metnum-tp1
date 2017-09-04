#ifndef METNUM_TP1_CALIBRATION_H
#define METNUM_TP1_CALIBRATION_H

#include "mask.h"

struct direction{
    direction(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    double x;
    double y;
    double z;
};

ostream& operator<< (ostream& os, const direction& dir) {
    os << "x: " << dir.x  << endl;
    os << "y: " << dir.y << endl;
    os << "z: " << dir.z << endl;
    return os;
}

namespace Calibration {
    /**
     * Calibrate the illumination sources, returning an array of directions
     *
     * @pre imgs must have all the same dimensions. imgs must not be empty.
     * @tparam vector<matrix<double>>
     * @param imgs the vector of matrixes of the images of the sphere
     */
    vector<direction> calibrate(const vector<matrix<double> > &imgs, const matrix<double> &mask) {
        assert(imgs.size() > 0);

        Mask::circle car = Mask::get_center_and_radius(mask);

        cout << "center: (" << car.xCenter << "," << car.yCenter << ")" << endl;
        cout << "radius: " << car.radius << endl;

        vector<direction> directions;
        int width = Matrix::columns(imgs[0]);
        int height = Matrix::rows(imgs[0]);
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

            // cout << "intensity = " << intensity << endl;
            // cout << "x = " << x << endl;
            // cout << "y = " << y << endl;

            double z = sqrt(pow(car.radius, 2) - pow(x - (car.xCenter - width / 2), 2) - pow(y - (height / 2 - car.yCenter), 2));
            // cout << "z = " << z << endl;

            double norm2 = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
            // cout << "norma: " << norm2 << endl;
            direction normal(x / norm2, y / norm2, z / norm2);

            // cout << "nx: " << normal.x << " ny: " << normal.y << " nz: " << normal.z << endl;
            directions.push_back(direction(-normal.x, -normal.y, -normal.z));
        }

        return directions;
    }
}

#endif //METNUM_TP1_CALIBRATION_H
