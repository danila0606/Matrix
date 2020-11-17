#pragma  once

#include <fstream>
#include <gtest/gtest.h>
#include "Matrix.h"

TEST(DETERMINANT, TEST_DOUBLE_1) {

    std::ifstream istr("../tests/test_det1.txt");
    std::ifstream istr_ans("../tests/test_det1_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::eps * ans));
}

TEST(DETERMINANT, TEST_INT_1) {

    std::ifstream istr("../tests/test_det2.txt");
    std::ifstream istr_ans("../tests/test_det2_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix<int> m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::eps * ans));
}

TEST(DETERMINANT, TEST_DOUBLE_2) {

    std::ifstream istr("../tests/test_det3.txt");
    std::ifstream istr_ans("../tests/test_det3_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::eps * ans));
}

TEST(DETERMINANT, TEST_INT_2) {

    std::ifstream istr("../tests/test_det4.txt");
    std::ifstream istr_ans("../tests/test_det4_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix<int> m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::eps * ans));
}