#pragma once
#include<string>
#include <vector>
using namespace std;
namespace UriParser
{
	enum UriParserError
	{
		Ok = 0,
		Uninitialized = 1,
		NoUriCharacter = 2,
		InvalidSchemeName = 3,
		UnexpectedEndOfLine = 6,
	};


	class ParseUri
	{
	public:

		UriParserError ErrorCode;
		wstring WScheme;
		wstring WUserName;
		wstring WPassword;
		wstring WHost;
		wstring WPort;
		wstring WPath;
		wstring WQuery;
		wstring WFragment;

		ParseUri() :ErrorCode(Uninitialized)
		{}

		bool IsValid() const { return ErrorCode == Ok; }

		static bool IsValidScheme(const wstring& schemeName);

		ParseUri Parse(const wstring& uri);

		template<typename T, typename> struct ignore { typedef T type; };

		template<typename T> vector<T> Split(const T & str, const T & delimiters) {
			vector<T> v;
			typename T::size_type start = 0;
			auto pos = str.find_first_of(delimiters, start);
			while (pos != T::npos) {
				if (pos != start)
					v.emplace_back(str, start, pos - start);
				start = pos + 1;
				pos = str.find_first_of(delimiters, start);
			}
			if (start < str.length())
				v.emplace_back(str, start, str.length() - start);
			return v;
		}

	private:
		explicit ParseUri(UriParserError errorCode) :ErrorCode{ errorCode }
		{}
	};

}

