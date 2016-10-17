#pragma once
#include<string>
using namespace std;
namespace UriParser
{
	enum UriParserError
	{
		Ok = 0,
		Uninitialized = 1,
		NoUrlCharacter = 2,
		InvalidSchemeName = 3,
		NoDoubleSlash = 4,
		NoAtSign = 5,
		UnexpectedEndOfLine = 6,
		NoSlash = 7,
	};

	class ParseUri
	{
	public:
		UriParserError ErrorCode;
		std::string Scheme;
		std::string UserName;
		std::string Password;
		std::string Host;
		std::string Port;
		std::string Path;
		std::string Query;
		std::string Fragment;

		ParseUri() :ErrorCode(Uninitialized)
		{}

		bool IsValid() const { return ErrorCode == Ok; }

		static ParseUri Parse(const string& uri);

	private:
		explicit ParseUri(UriParserError errorCode) :ErrorCode{ errorCode }
		{}

	};
}

