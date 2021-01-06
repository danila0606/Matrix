#include "Matrix.h"
#include <gtest/gtest.h>

using namespace linal;

int main(int argc, char* argv[]) {

#ifdef GTESTS
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#endif

    try {

        Matrix<double> m;
        std::cin>>m;

        std::cout <<std::llround(m.determinantGaus()) << std::endl;

    } catch (std::exception& e) {

        std::cerr<<e.what()<<std::endl;
    }
    return 0;
}