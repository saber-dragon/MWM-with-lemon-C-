//
// Created by saber on 10/6/18.
//

#include <mwm.hpp>
#include <gtest/gtest.h>
#include <random>

using namespace lemonwrap;

class Permutation {
  std::vector<int> _perm;
 public:
  Permutation()  {}
  template <class URBG>
  std::vector<int>&operator()(size_t n, URBG&& g) {
    _perm.clear();
    for ( int i = 0;i < n;++ i ) _perm.push_back(i);
    std::shuffle(_perm.begin(), _perm.end(), g);
    return _perm;
  }
  std::vector<int>&operator()(size_t n){
    _perm.clear();
    for ( int i = 0;i < n;++ i ) _perm.push_back(i);
    std::random_shuffle(_perm.begin(), _perm.end());
    return _perm;
  }
};
class BpMWMTest : public ::testing::Test {
 protected:
  void SetUp() override {
    mwm_obj1 = new MWM(2, 2);
    mwm_obj2 = new MWM(10, 10);
  }

  void TearDown() override {
    delete mwm_obj1;
    delete mwm_obj2;
  }

  MWM *mwm_obj1;
  MWM *mwm_obj2;
};


TEST_F(BpMWMTest, IsEmptyInitially)
{
  for ( size_t i = 0;i < 2;++ i ) {
    for ( size_t o = 0;o < 2;++ o ) {
      EXPECT_EQ(0, mwm_obj1->get(i, o));
    }
  }
  auto mp = mwm_obj1->run();
  EXPECT_EQ(0, mp.second);
}

TEST_F(BpMWMTest, MatchingOfMatching)
{
  mwm_obj1->set(0, 0, 1);
  mwm_obj1->set(1, 1, 1);
  auto mp = mwm_obj1->run();
  EXPECT_EQ(mp.first, std::vector<int>({0, 1}));
  EXPECT_EQ(2, mp.second);
}

TEST_F(BpMWMTest, ComputeMatching){
  Permutation perm;
  for (int k = 0;k < 10;++ k) {
    auto rp = perm(10);
    mwm_obj2->self_increase(rp, -1);
  }
  auto rp = perm(10);
  for ( int i = 0;i < 10;++ i ) {
    mwm_obj2->set(i, rp[i], 100);
  }
  auto mp = mwm_obj2->run();
  EXPECT_EQ(rp, mp.first);
  EXPECT_EQ(100*10, mp.second);
}

int main(int argc, char *argv[])
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}