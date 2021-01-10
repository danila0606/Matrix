#include "Matrix.h"
#include <gtest/gtest.h>

using namespace linal;

int main(int argc, char* argv[]) {

#ifdef GTESTS
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    try {

        Matrix<int> m;
        std::cin>>m;

        std::cout <<m.determinantGaus() << std::endl;
       // std::cout <<m.determinant() << std::endl;

    } catch (std::exception& e) {

        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}