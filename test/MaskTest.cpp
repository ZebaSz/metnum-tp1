#include <gtest/gtest.h>
#include "../src/matrix.h"
#include "../src/mask.h"

class MaskTest : public testing::Test {
protected:

    virtual void SetUp() {
        mx = {
                {1,2,3,4,5,6},
                {1,2,3,4,5,6},
                {1,2,3,4,5,6},
                {1,2,3,4,5,6},
                {1,2,3,4,5,6},
                {1,2,3,4,5,6}
        };
        msk = {
                {{false,false,false,false,false,false},
                {false,false,true,true,false,false},
                {false,true,true,true,true,false},
                {false,true,true,true,true,false},
                {false,false,true,true,false,false},
                {false,false,false,false,false,false}},
                {1,1,4,4}
        };
    }

    matrix<double> mx;
    Mask::mask msk;
};

TEST_F(MaskTest, apply_mask) {
    matrix<double> expected {
            {0,0,0,0,0,0},
            {0,0,3,4,0,0},
            {0,2,3,4,5,0},
            {0,2,3,4,5,0},
            {0,0,3,4,0,0},
            {0,0,0,0,0,0}
    };
    matrix<double> actual = Mask::apply_mask(mx, msk);
    ASSERT_EQ(expected, actual);
}

TEST_F(MaskTest, apply_clip) {
    matrix<double> expected {
            {2,3,4,5},
            {2,3,4,5},
            {2,3,4,5},
            {2,3,4,5}
    };
    matrix<double> actual = Mask::apply_clip(mx, msk);
    ASSERT_EQ(expected, actual);
}

TEST_F(MaskTest, restore_clip) {
    matrix<double> clipped = Mask::apply_clip(mx, msk);
    matrix<double> actual = Mask::restore_clip(clipped, msk);
    matrix<double> expected {
            {0,0,0,0,0,0},
            {0,2,3,4,5,0},
            {0,2,3,4,5,0},
            {0,2,3,4,5,0},
            {0,2,3,4,5,0},
            {0,0,0,0,0,0}
    };
    ASSERT_EQ(expected, actual);
}

