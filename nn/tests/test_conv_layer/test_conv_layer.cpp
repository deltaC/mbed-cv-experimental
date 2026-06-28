#include "test_conv_layer.hpp"

void conv() {

}

TEST(TestConv, TestConvSimple) {
  ASSERT_TRUE(1.f == 1.f);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  ::testing::InitGoogleMock(&argc, argv);
  
  return RUN_ALL_TESTS();
}