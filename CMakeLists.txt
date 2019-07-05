cmake_minimum_required(VERSION 3.13)
project(DPPML)

set(CMAKE_CXX_STANDARD 14)

include_directories(includes/HEAAN/src)

add_executable(DPPML
        includes/HEAAN/src/BootContext.cpp
        includes/HEAAN/src/BootContext.h
        includes/HEAAN/src/Ciphertext.cpp
        includes/HEAAN/src/Ciphertext.h
        includes/HEAAN/src/EvaluatorUtils.cpp
        includes/HEAAN/src/EvaluatorUtils.h
        includes/HEAAN/src/HEAAN.h
        includes/HEAAN/src/Key.cpp
        includes/HEAAN/src/Key.h
        includes/HEAAN/src/Params.h
        includes/HEAAN/src/Plaintext.cpp
        includes/HEAAN/src/Plaintext.h
        includes/HEAAN/src/Ring.cpp
        includes/HEAAN/src/Ring.h
        includes/HEAAN/src/RingMultiplier.cpp
        includes/HEAAN/src/RingMultiplier.h
        includes/HEAAN/src/Scheme.cpp
        includes/HEAAN/src/Scheme.h
        includes/HEAAN/src/SchemeAlgo.cpp
        includes/HEAAN/src/SchemeAlgo.h
        includes/HEAAN/src/SecretKey.cpp
        includes/HEAAN/src/SecretKey.h
        includes/HEAAN/src/SerializationUtils.cpp
        includes/HEAAN/src/SerializationUtils.h
        includes/HEAAN/src/StringUtils.cpp
        includes/HEAAN/src/StringUtils.h
        includes/HEAAN/src/TestScheme.cpp
        includes/HEAAN/src/TestScheme.h
        includes/HEAAN/src/TimeUtils.cpp
        includes/HEAAN/src/TimeUtils.h

        BENCHS/BENCHBuildingBlocks.cpp
        BENCHS/BENCHBuildingBlocks.h

        CRYPTO/DTPKC.cpp
        CRYPTO/DTPKC.h
        CRYPTO/EvalAdd.cpp
        CRYPTO/EvalAdd.h
        CRYPTO/EvalSub.cpp
        CRYPTO/EvalSub.h
        CRYPTO/SkeySwitch.cpp
        CRYPTO/SkeySwitch.h
        CRYPTO/EvalMult.cpp
        CRYPTO/EvalMult.h

        ML/Record.h
        ML/DatasetReader.cpp
        ML/DatasetReader.h

        UTIL/math_util.cc
        UTIL/math_util.hh
        UTIL/mpz_class.hh
        UTIL/num_th_alg.cc
        UTIL/num_th_alg.hh
        UTIL/prime_seq.cc
        UTIL/prime_seq.hh
        UTIL/util_gmp_rand.h
        TestPrimitives.cpp ML/DatasetReader.h ML/LogisticRegression.cpp ML/LogisticRegression.h PPML/PPLogisticRegression.cpp PPML/PPLogisticRegression.h PPML/MLSP.cpp PPML/MLSP.h PPML/CSP.cpp PPML/CSP.h PPML/Worker.cpp PPML/Worker.h)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake-build-debug)

set(CMAKE_C_FLAGS "-lgmp" "-lgmpxx")

set(CMAKE_C_FLAGS "-lntl" "-lm")

file(GLOB Common_sources "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cc" "${CMAKE_CURRENT_SOURCE_DIR}/*/*.c" "${CMAKE_CURRENT_SOURCE_DIR}/*/*.h")

set(CMAKE_MODULE_PATH   ${CMAKE_MODULE_PATH} /home/nassimaab/Desktop/DPPML/cmake-build-debug)
find_package(GMP REQUIRED)

find_library(NTL_LIB ntl)
if(NOT NTL_LIB)
    message(FATAL_ERROR "ntl library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

find_library(GMP_LIB gmp)
if(NOT GMP_LIB)
    message(FATAL_ERROR "gmp library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

find_library(M_LIB m)
if(NOT M_LIB)
    message(FATAL_ERROR "m library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()

find_library(MPFR_LIB mpfr)
if(NOT MPFR_LIB)
    message(FATAL_ERROR "mpfr library not found.  Rerun cmake with -DCMAKE_PREFIX_PATH=\"<path to lib1>;<path to lib2>\"")
endif()


target_link_libraries(DPPML ${NTL_LIB} ${M_LIB} ${GMP_LIB} ${MPFR_LIB} pthread)
