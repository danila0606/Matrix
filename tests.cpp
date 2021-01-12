#include <fstream>
#include <gtest/gtest.h>
#include "Matrix.h"


TEST(DETERMINANT, TEST_DOUBLE_1) {

    std::ifstream istr("test_det1.txt");
    std::ifstream istr_ans("test_det1_ans.txt");

    if (!istr.is_open())
        assert(0);

    double ans;
    istr_ans >> ans;

    linal::Matrix m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::tests_eps * ans));
}

TEST(DETERMINANT, TEST_INT_1) {

    std::ifstream istr("test_det2.txt");
    std::ifstream istr_ans("test_det2_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix<int> m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::tests_eps * ans));
}

TEST(DETERMINANT, TEST_DOUBLE_2) {

    std::ifstream istr("test_det3.txt");
    std::ifstream istr_ans("test_det3_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::tests_eps * ans));
}

TEST(DETERMINANT, TEST_INT_2) {

    std::ifstream istr("test_det4.txt");
    std::ifstream istr_ans("test_det4_ans.txt");

    double ans;
    istr_ans >> ans;

    linal::Matrix<int> m;
    istr>>m;

    double res = m.determinantGaus();

    istr.close();
    istr_ans.close();

    EXPECT_TRUE( std::abs(res - ans) < std::abs(linal::tests_eps * ans));
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

TEST(Equal, t1) {
    linal::Matrix<int> m {{1,2,3}, {4,5,6}};
    linal::Matrix<int> d {{1,2,3}, {4,5,6}};
    linal::Matrix<int> c {{1,2,3}, {4,5,6}, {0,0,0}};
    linal::Matrix<int> e {{1,2,3}, {4,5,7}};

    EXPECT_TRUE(m == d);
    EXPECT_TRUE(!(m == c));
    EXPECT_TRUE(!(m == e));

}

TEST(Copy_Ctor, t1) {

    linal::Matrix<int> m {{1,2,3}, {4,5,6}};

    linal::Matrix<int> c(m);


    EXPECT_TRUE(c == m);

}

TEST(Oper_equal, t1) {
    linal::Matrix<int> m {{1,2,3}, {4,5,6}};

    linal::Matrix c = m;

    EXPECT_TRUE(c == m);
}


TEST(Random, Int) {


    linal::Matrix<int> m(5,5);

    for (int i = 0; i < 100; i++) {
        linal::RandomFill(m, -4, 4);

        auto res1 = m.determinant();
        auto res2 = m.determinantGaus();

        EXPECT_TRUE(std::abs(res1 - res2) < linal::tests_eps);
    }
}

TEST(Random, Double) {

    linal::Matrix<double> m(5,5);

    for(int i = 0; i < 100; i++) {
        linal::RandomFill(m, -4, 4);

        auto res1 = m.determinant();
        auto res2 = m.determinantGaus();

        EXPECT_TRUE(std::abs(res1 - res2) < linal::tests_eps);
    }
}