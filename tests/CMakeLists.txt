find_library(GTEST_LIB gtest)
find_library(GTEST_MAIN_LIB gtest_main)
#IF (NOT GTEST_LIB OR NOT GTEST_MAIN_LIB)
    ADD_SUBDIRECTORY(googletest)
#ENDIF()

SET(BANKS_TESTS_SOURCE_FILES main.cpp)

ADD_EXECUTABLE(BANK_TESTS main.cpp client-tests.cpp transaction-test.cpp helpers.h helpers.cpp)

TARGET_LINK_LIBRARIES(BANK_TESTS PRIVATE gtest gtest_main ${BANKS_LIBRARY})