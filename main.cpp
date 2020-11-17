#include "tests.h"
//#include <gtest/gtest.h>

#define GTESTS

using namespace linal;

int main(int argc, char *argv[]) {

#ifdef GTESTS
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    try {

        Matrix<int> m(10, 10);
        RandomFill(m, -100, 100);


//  std::cout << m.determinant() << std::endl;
        std::cout << m.determinantGaus() << std::endl;

    } catch (std::exception& e) {

        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}