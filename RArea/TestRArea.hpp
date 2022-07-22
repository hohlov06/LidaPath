#pragma once

#include <gtest/gtest.h>
#include "RArea.hpp"

using namespace LidaPath;

class TestRArea : public ::testing::Test {
protected:
    void SetUp();
    
    RArea base1, 
          base2,
          base3,
          base4;
};
