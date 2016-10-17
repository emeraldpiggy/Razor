#include "stdafx.h"
#include "gtest/gtest.h"
#include <iostream>
#include <string>
using namespace std;

namespace UnitTests {
	class UriParsingUnitTests : public::testing::Test{
	protected:
		UriParsingUnitTests()
		{}

		virtual ~UriParsingUnitTests()
		{}

		void When_ParsingUri_Should_Return_Succeess()
		{
			//Arrange
			bool res = true;

			//Act

			//Assert
			ASSERT_EQ(true, res);
		}

		void When_ParsingUri_Should_Valid_schemeName(string& schemeName)
		{

		}
	};

	TEST_F(UriParsingUnitTests, AssignmentOperator)
	{
		When_ParsingUri_Should_Return_Succeess();
	}


	TEST_F(UriParsingUnitTests, AssignmentOperator)
	{
		When_ParsingUri_Should_Valid_schemeName(string("a"));
	}
}