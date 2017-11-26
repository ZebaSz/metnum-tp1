#ifndef METNUM_TP1_CALIBRATION_H
#define METNUM_TP1_CALIBRATION_H

#include "mask.h"

struct direction {
    direction() = default;
    direction(double X, double Y, double Z) : x(X), y(Y), z(Z) {}
    double x;
    double y;
    double z;
};

struct circle {
    size_t xCenter;
    size_t yCenter;
    size_t radius;
};

std::ostream& operator<< (std::ostream& os, const direction& dir) {
    os << "x: " << dir.x << std::endl;
    os << "y: " << dir.y << std::endl;
    os << "z: " << dir.z << std::endl;
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
    std::vector<direction> calibrate(const std::vector<matrix<double>> &imgs, const Mask::mask &msk) {
        assert(imgs.size() > 0);


        auto& clip = msk.clip;
        size_t radius = (clip.right - clip.left + 1) / 2;
        size_t xCenter = clip.left + radius + 1;
        size_t yCenter = clip.top + radius + 1;

        circle circ = {xCenter, yCenter, radius};

        std::vector<direction> directions;
        int width = Matrix::columns(imgs[0]);
        int height = Matrix::rows(imgs[0]);
        for (size_t k = 0; k < imgs.size(); k++) {
            double x(0);
            double y(0);
            double intensity(0);
            for (int i = 0; i < height; i++) {
                for (int j = 0; j < width; j++) {
                    if (imgs[k][i][j] > intensity) {
                        intensity = imgs[k][i][j];
                        x = j;
                        y = i;
                    }
                }
            }

            // 1: image center
            double z = sqrt(pow(circ.radius, 2) - pow(x - circ.xCenter, 2) - pow(y - circ.yCenter, 2));
            x = x - width / 2;
            y = height / 2 - y;
            /*
            // vs circle center
            x = x - circ.xCenter;
            y = circ.yCenter - y;
            double z = sqrt(pow(circ.radius, 2) - pow(x, 2) - pow(y, 2));
            */

            // normalize
            double norm = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
            direction s(x / norm, y / norm, z / norm);
            directions.push_back(s);
        }
        return directions;
    }

    std::vector<direction> load_lights(const std::string& fname) {
        std::ifstream file(fname);
        size_t count;
        file >> count;
        std::vector<direction> res(count);
        for (auto& light : res) {
            file >> light.x >> light.y >> light.z;
        }
        return res;
    }
}

#endif //METNUM_TP1_CALIBRATION_H
