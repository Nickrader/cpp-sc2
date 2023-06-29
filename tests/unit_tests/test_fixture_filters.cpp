// #include "gmock/gmock.h"
// #include "gtest/gtest.h"
// #include "sc2api/sc2_unit.h"
// #include "sc2api/sc2_unit_filters.h"
//
// class FiltersFixture : public ::testing::Test {
// public:
//	bool val = false;
//	sc2::Unit EmptyUnit;
//   sc2::IsUnit CentCom(sc2::UNIT_TYPEID TERRAN_COMMANDCENTER);
//	//sc2::IsUnit CentCom; //C2280 no appropriate default constructor
//	void SetUp() {
//		val = CentCom(EmptyUnit);
//	}
// 1
//	virtual void TearDown() {}
// };
//
// TEST_F(FiltersFixture, FixtureIsUnitTest) {
//	//CentCom(EmptyUnit);
//	ASSERT_TRUE(val);
//	//ASSERT_TRUE(CentCom(EmptyUnit));
// }
// TEST(FIlter, filter) {
//	ASSERT_TRUE(true);
// }

////----------------------------------------------------------------
//// Seems using test fixutres would reduce duplication
//// However there is some class stuff happening, I do not understand
//// Attempted: default constructor, SetUp(), TearDown(), etc...
//// comeback to at later date, after more practice with object functions
//// Compiler is seeing function without definition,

// Need to find an example of TEST_F with function objects, to show
// me this is indeed possible. Otherwise, could be wasting time on dead-end.

//  Seems like I'd need to mock it? Looking at my mock sample, if it
// insists these objects are functions. But if a mock is derived from
// it's parent class, then that is EVEN MORE l;ksf;lasjk than just using
// simple tests.

////  TL;DR:  Simple Tests is the fix for now, but would like to understand
///  Why test fixture fails, for future knowledge.  Seems like this would be
///  encountered a lot.
