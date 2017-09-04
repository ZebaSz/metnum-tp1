#include <gtest/gtest.h>
#include "../src/calibration.h"
#include "../src/utils.h"

TEST(CalibrationTest, vs_control_lights) {
    std::vector<direction> control(
            {{ 0.403259,  0.480808, 0.778592},
             { 0.0982272, 0.163712, 0.981606},
             {-0.0654826, 0.180077, 0.98147 },
             {-0.127999,  0.431998, 0.892745},
             {-0.328606,  0.485085, 0.810377},
             {-0.110339,  0.53593,  0.837021},
             { 0.239071,  0.41439,  0.878138},
             { 0.0642302, 0.417497, 0.906406},
             { 0.12931,   0.339438, 0.931698},
             { 0.0323953, 0.340151, 0.939813},
             { 0.0985318, 0.0492659,0.993914},
             {-0.16119,   0.354617, 0.921013}}
    );


    matrix<double> mask(
            Utils::grayscalify(Utils::loadImage("ppmImagenes/mate/mate.mask.ppm")));


    std::vector<matrix<double>> mate;

    for (int i = 0; i < 12; ++i) {
        std::stringstream name;
        name << "ppmImagenes/mate/mate." << i << ".ppm";
        matrix<double> test(
                Utils::grayscalify(Utils::loadImage(name.str())));
        mate.push_back(test);
    }

    std::vector<direction> res = Calibration::calibrate(mate, mask);
    ASSERT_EQ(control.size(), res.size());
    for (size_t i = 0; i < control.size(); ++i) {
        std::cout << "IMAGEN:" << i << endl;
        EXPECT_NEAR(control[i].x, res[i].x, 0.00001)
                            << "x = " << res[i].x
                            << ", dx = " << control[i].x - res[i].x;
        EXPECT_NEAR(control[i].y, res[i].y, 0.00001)
                            << "y = " << res[i].y
                            << ", dy = " << control[i].y - res[i].y;
        EXPECT_NEAR(control[i].z, res[i].z, 0.00001)
                            << "z = " << res[i].z
                            << ", dz = " << control[i].z - res[i].z;
    }
}