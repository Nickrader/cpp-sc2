#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "sc2api/sc2_unit.h"

namespace {

//////////////////
// Simple Tests //
//////////////////

TEST(Units, Unit) {
    sc2::Unit November;
    November.tag = 41822;

    sc2::Units control_group;
    ASSERT_EQ(0, control_group.size());

    sc2::Unit* Terra = &November;
    control_group.push_back(Terra);
    ASSERT_EQ(1, control_group.size()) << "Terra should be pointing to November.";

    Terra->tag = 777;
    ASSERT_EQ(Terra->tag, 777) << "should be lucky Triple 7s";

    Terra->cloak = sc2::Unit::CloakState::Cloaked;
    ASSERT_EQ(sc2::Unit::CloakState::Cloaked, Terra->cloak);
}

///////////////////
// Test Fixtures //
///////////////////

// Create a class that can be reused for tests.  Changes are not preserved
// between tests.
// TestFixtureClassName: sc2UnitTest
class sc2UnitTest : public ::testing::Test {
public:
    void SetUp() override {
        unit1.tag = 1;
        unit2.tag = 2;
        unit3.tag = 3;
    }

    sc2::Unit unit1;
    sc2::Unit unit2;
    sc2::Unit unit3;

    sc2::UnitPool pool;
    sc2::UnitPool* ptr_pool = &pool;  // need a pointer to use boolean check
                                      // could use &pool directly, but this is more explicit of our intent.
};

TEST_F(sc2UnitTest, TagNumMatchNameNum) {  // TestFixtureClassName must match
                                           // test_fixture.
    EXPECT_EQ(1, unit1.tag);
    EXPECT_EQ(2, unit2.tag);
    EXPECT_EQ(3, unit3.tag);

    unit1.tag = 9001;
    EXPECT_NE(1, unit1.tag) << "It's over 9,000!";  // note: _NE
}

TEST_F(sc2UnitTest, TagUnalteredBetweenTests) {
    EXPECT_EQ(1, unit1.tag) << "Tag should not have been altered between tests";  // note: _EQ
}

TEST_F(sc2UnitTest, UnitPoolExists) {
    EXPECT_TRUE(ptr_pool) << "A UnitPool does not exist.";
    // EXPECT_TRUE(!ptr_pool) << "A UnitPool exists."; // uncomment to see a
    // failing test
}

///////////////////////////////
// Value-Parameterized Tests //
///////////////////////////////

// Extend TestFixtureClass to parameter class.
class sc2UnitTestParam : public sc2UnitTest, public testing::WithParamInterface<sc2::Tag> {
    void SetUp() override {
        pool.CreateUnit(GetParam());
    }
};

TEST_P(sc2UnitTestParam, ParameterTest) {  // using '||' because parameter is
                                           // inserted each run during SetUp()
    EXPECT_TRUE(pool.UnitExists(420) || pool.UnitExists(42) || pool.UnitExists(9000));
}

INSTANTIATE_TEST_SUITE_P(CreateUnitParam, sc2UnitTestParam, testing::Values(420, 42, 9000));

////////////////
// Typed Test //
////////////////
// TODO(Nickrader): Typed & ParamTyped tests could test members.

template <typename T>
class TypedTestTags : public testing::Test {
public:
};

using MyTypes = ::testing::Types<int, double, sc2::Tag>;

TYPED_TEST_SUITE(TypedTestTags, MyTypes);

TYPED_TEST(TypedTestTags, TakesANumber) {
    TypeParam n = 626;  // TODO(Nickrader): In example uses member variable.
    sc2::Unit Tychus;
    Tychus.tag = n;

    EXPECT_EQ(626, Tychus.tag);
};

////////////////////////////////
// Type - Parameterized Tests //
////////////////////////////////
// TODO(Nickrader): Typed & ParamTyped tests could test members.

// Define a test fixture class template
// For simplicity, we reuse typed test class template;
template <typename T>
class TPTestTags : public TypedTestTags<T> {};

// Declare the test case
TYPED_TEST_SUITE_P(TPTestTags);

// Define a test
TYPED_TEST_P(TPTestTags, DoesBlah) {  // at this point is unaware of the types
    TypeParam n = 626;                // In example uses member variable, is this close enough?
    sc2::Unit Tychus;
    Tychus.tag = n;

    EXPECT_EQ(626, Tychus.tag);
}

// Enumerate the tests you defined
REGISTER_TYPED_TEST_SUITE_P(TPTestTags, DoesBlah);

// You are free to instantiate the pattern with the types you want. If you put
// the above code in a header file, you can #include it in multiple C++ source
// files and instantiate it multiple times.
// This appears to be the main contrast to Typed Tests
// typedef ::testing::Types<int, double, sc2::Tag> Numbers;
using Numbers = ::testing::Types<int, double, sc2::Tag>;
INSTANTIATE_TYPED_TEST_SUITE_P(IntDblTag, TPTestTags, Numbers);

//////////////////
// Mock Methods //
//////////////////

class UnitWrapper : public sc2::Unit {
public:
    virtual ~UnitWrapper() = default;
    virtual bool IsBuildFinished() const = 0;
};

class MockUnitWrapper : public UnitWrapper {
public:
    MOCK_METHOD(bool, IsBuildFinished, (), (const, override));
};

TEST(MockUnitTest, finishedBuilding) {
    MockUnitWrapper mockUnit;

    //// Get naggy uninteresting call warning.
    //// https://google.github.io/googletest/gmock_cook_book.html#UseOnCall
    // ON_CALL(mockUnit,
    // IsBuildFinished()).WillByDefault(::testing::Return(false));
    // ON_CALL(mockUnit,
    // IsBuildFinished()).WillByDefault(::testing::Return(true));

    EXPECT_CALL(mockUnit, IsBuildFinished()).WillOnce(::testing::Return(true));
    // EXPECT_CALL(mockUnit,
    // IsBuildFinished()).WillOnce(::testing::Return(false)); // uncomment for
    // failing test

    EXPECT_EQ(true, mockUnit.IsBuildFinished());
};

//// Interfaces.h; sc2::ObservationInterface;
//// it's a pure virtual class, however, requires ALL members be overridden
//// Both ways, same error.
//
// #include "sc2api/sc2_interfaces.h"
////class ObservationInterfaceWrapper : public sc2::ObservationInterface {
////virtual ~ObservationInterfaceWrapper() {};
////virtual void GetPlayerID() = 0;
////};
//
////class MockObservationInterface : public ObservationInterfaceWrapper {
// class MockObservationInterface : public sc2::ObservationInterface {
//	MOCK_METHOD(uint32_t, GetPlayerID, (), (const, override));
//  };
//
//  TEST(MockTest, DoesThis) {
//	 MockObservationInterface mockObs; // Compiler error, must override all
//  };

}  // end anonymous namespace

// Resources:
// https://google.github.io/googletest/primer.html
// https://google.github.io/googletest/reference/testing.html
// https://google.github.io/googletest/advanced.html
// https://google.github.io/googletest/gmock_for_dummies.html
// https://google.github.io/googletest/gmock_cheat_sheet.html
