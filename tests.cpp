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

TEST(Ctor, t1) {

    struct Widget {
        int a;
        double b;
    };

    Widget w = {1,2.3};

    linal::Matrix<Widget> m(3,3, w);

    EXPECT_TRUE(1 == m.at(1,2).a);
    EXPECT_TRUE(2.3 == m.at(1,2).b);
}

TEST(Random, Int) {


    linal::Matrix<int> m(5,5);

    for (int i = 0; i < 100; i++) {
        linal::RandomFill(m, -4, 4);

        auto res1 = m.determinant();
        auto res2 = m.determinantGaus();

        EXPECT_TRUE(std::abs(res1 - res2) < linal::eps);
    }
}

TEST(Random, Double) {

    linal::Matrix<double> m(5,5);

    for(int i = 0; i < 100; i++) {
        linal::RandomFill(m, -4, 4);

        auto res1 = m.determinant();
        auto res2 = m.determinantGaus();

        EXPECT_TRUE(std::abs(res1 - res2) < linal::eps);
    }
}