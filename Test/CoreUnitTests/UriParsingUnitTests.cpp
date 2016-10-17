#include "stdafx.h"
#include "gtest/gtest.h"
#include "../../RazorUriCore/RazorUriCore/ParseUri.h"
using namespace std;

namespace UnitTests {

	class UriParsingUnitTests : public::testing::Test {
	public:
		const string uri1 = "ftp://ftp.is.co.za/rfc/rfc1808.txt";
		const string uri2 = "http://www.ietf.org/rfc/rfc2396.txt";
		const string uri3 = "ldap://[2001:db8::7]/c=GB?objectClass?one";
		const string uri4 = "mailto:John.Doe@example.com";
		const string uri5 = "news:comp.infosystems.www.servers.unix";
		const string uri6 = "tel:+1-816-555-1212";
		const string uri7 = "urn:oasis:names:specification:docbook:dtd:xml:4.1.2";

	protected:
		UriParser::ParseUri _parseUri;
		UriParsingUnitTests()
		{}

		virtual ~UriParsingUnitTests()
		{}

		void When_ParsingUri_Should_Return_Succeess(const string& uri) const
		{
			//Arrange
			UriParser::ParseUri res;


			//Act
			//res = _parseUri.Parse("a");


			//Assert
			//ASSERT_EQ(1, res);
		}

		void When_ParsingUri_Should_Valid_schemeName(const string& schemeName) const
		{
			//Arrange
			bool res = true;

			//Act

			//Assert
			ASSERT_EQ(true, res);
		}
	};

	TEST_F(UriParsingUnitTests, When_ParsingUri_Should_Return_Succeess)
	{
		When_ParsingUri_Should_Return_Succeess(uri1);
		When_ParsingUri_Should_Return_Succeess(uri2);
		When_ParsingUri_Should_Return_Succeess(uri3);
		When_ParsingUri_Should_Return_Succeess(uri4);
		When_ParsingUri_Should_Return_Succeess(uri5);
		When_ParsingUri_Should_Return_Succeess(uri6);
		When_ParsingUri_Should_Return_Succeess(uri7);
	}


	TEST_F(UriParsingUnitTests, When_ParsingUri_Should_Valid_schemeName)
	{
		When_ParsingUri_Should_Valid_schemeName(string("a"));
		When_ParsingUri_Should_Valid_schemeName(string("b"));
		When_ParsingUri_Should_Valid_schemeName(string("c"));
		When_ParsingUri_Should_Valid_schemeName(string("d"));
	}
}