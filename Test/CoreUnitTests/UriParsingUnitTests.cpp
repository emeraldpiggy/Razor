#include "stdafx.h"
#include "gtest/gtest.h"
#include "../../RazorUriCore/RazorUriCore/ParseUri.h"
using namespace std;

namespace UnitTests {

	class UriParsingUnitTests : public::testing::Test {
	public:
		const wstring uri1 = L"ftp://ftp.is.co.za/rfc/rfc1808.txt";
		const wstring uri2 = L"http://www.ietf.org/rfc/rfc2396.txt";
		const wstring uri3 = L"abc://username:password@example.com:123/path/data?key=value&key2=value2#fragid1";
		const wstring uri4 = L"mailto:John.Doe@example.com";
		const wstring uri5 = L"news:comp.infosystems.www.servers.unix";
		const wstring uri6 = L"tel:+1-816-555-1212";
		const wstring uri7 = L"urn:oasis:names:specification:docbook:dtd:xml:4.1.2";
		

		const wstring scehmeName1 = L"urn";
		const wstring scehmeName2 = L"tel";
		const wstring scehmeName3 = L"news";
		const wstring scehmeName4 = L"ldap";


	protected:
		
		UriParsingUnitTests()
		{}

		virtual ~UriParsingUnitTests()
		{}

		void When_ParsingUri_Should_Return_Succeess(const wstring& uri, const wstring& scheme, 
			const wstring& host, const wstring& username, const wstring& password, const wstring& port) const
		{
			//Arrange
			UriParser::ParseUri _parseUri;
			//Act
			auto res = _parseUri.Parse(uri);


			//Assert
			ASSERT_EQ(UriParser::Ok, res.ErrorCode);
		}

		void When_ParsingUri_Should_Valid_schemeName(const wstring& schemeName) const
		{
			//Arrange
			UriParser::ParseUri _parseUri;
			//Act
			auto validScheme = _parseUri.IsValidScheme(schemeName);

			//Assert
			ASSERT_EQ(true, validScheme);
		}

		void When_ParsingUri_Should_Check_Default_Constructor() const
		{
			//Arrange
			UriParser::ParseUri _parseUri;

			bool res = _parseUri.IsValid();

			ASSERT_EQ(false, res);
		}
	};

	TEST_F(UriParsingUnitTests, When_ParsingUri_Should_Return_Succeess)
	{
		When_ParsingUri_Should_Return_Succeess(uri1,L"ftp.is.co.za",L"ftp",L"",L"",L"");
		When_ParsingUri_Should_Return_Succeess(uri2,L"www.ietf.org",L"http",L"",L"",L"");
		When_ParsingUri_Should_Return_Succeess(uri3,L"example.com",L"abc",L"username",L"password",L"123");
		When_ParsingUri_Should_Return_Succeess(uri4,L"example.com",L"mailto",L"John.Doe",L"",L"");
		When_ParsingUri_Should_Return_Succeess(uri5,L"comp.infosystems.www.servers.unix",L"news",L"",L"",L"");
		When_ParsingUri_Should_Return_Succeess(uri6,L"+1-816-555-1212",L"tel",L"",L"",L"");
		When_ParsingUri_Should_Return_Succeess(uri7,L"oasis:names:specification:docbook:dtd:xml:4.1.2",L"urn",L"",L"",L"");
	}




	TEST_F(UriParsingUnitTests, When_ParsingUri_Should_Valid_schemeName)
	{
		When_ParsingUri_Should_Valid_schemeName(scehmeName1);
		When_ParsingUri_Should_Valid_schemeName(scehmeName2);
		When_ParsingUri_Should_Valid_schemeName(scehmeName3);
		When_ParsingUri_Should_Valid_schemeName(scehmeName4);
	}

	TEST_F(UriParsingUnitTests, When_ParsingUri_Should_Check_Default_Constructor)
	{
		When_ParsingUri_Should_Check_Default_Constructor();
	}
}