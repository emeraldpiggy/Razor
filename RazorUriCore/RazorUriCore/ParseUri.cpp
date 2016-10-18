#include "stdafx.h"
#include "ParseUri.h"

#include <locale>
#include <codecvt>
#include <functional>
#include <vector>

bool UriParser::ParseUri::IsValidScheme(const wstring& schemeName)
{
	for (auto s : schemeName)
	{
		if (!isalpha(s) && s != '+' && s != '-' && s != '.')
		{
			return false;
		}
	}
	return true;
}


static wstring ConvertStringToWString(const string& str)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.from_bytes(str);
}

static string WStringToString(const wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;

	return converter.to_bytes(wstr);
}

UriParser::ParseUri UriParser::ParseUri::Parse(const wstring &uri)
{
	UriParser::ParseUri result;

	typedef wstring::const_iterator iterator_t;

	if (uri.length() == 0)
	{
		return ParseUri(NoUriCharacter);
	}

	iterator_t uriEnd = uri.end();

	iterator_t queryStart = find(uri.begin(), uriEnd, L'?');
	iterator_t fragmentStart = find(uri.begin(), uriEnd, L'#');

	iterator_t schemeStart = uri.begin();
	iterator_t schemeEnd = find(schemeStart, uriEnd, L':');

	if (schemeEnd != uriEnd)
	{
		wstring scheme = &*(schemeEnd);
		if ((scheme.length() > 3) && (scheme.substr(0, 3) == L"://"))
		{

			result.WScheme = wstring(schemeStart, schemeEnd);
			schemeEnd += 3;
		}
		else if ((scheme.length() > 3) && (scheme.substr(0, 1) == L":"))
		{
			result.WScheme = wstring(schemeStart, schemeEnd);
			schemeEnd += 1;
		}
		else
		{
			schemeEnd = uri.begin();
		}
		if (!IsValidScheme(result.WScheme))
		{
			return ParseUri(InvalidSchemeName);
		}
	}
	else
	{
		schemeEnd = uri.begin();
		return ParseUri(InvalidSchemeName);
	}

	// user info
	iterator_t userInfoEnd = find(schemeEnd, uriEnd, L'@');
	if (userInfoEnd != uriEnd)
	{
		wstring userFullInfo = wstring(schemeEnd, userInfoEnd);

		vector<wstring> userinfo = Split<wstring>(userFullInfo, L":");

		if (userinfo.size() > 1)
		{
			result.WUserName = userinfo[0];
			result.WPassword = userinfo[1];
		}
		else
			result.WUserName = userinfo[0];

		userInfoEnd += 1;
	}

	iterator_t hostStart = userInfoEnd;
	iterator_t pathStart = find(hostStart, uriEnd, L'/');

	iterator_t hostEnd = find(userInfoEnd,
		(pathStart != uriEnd) ? pathStart : fragmentStart,
		L':');

	result.WHost = wstring(hostStart, hostEnd);


	// port
	if ((hostEnd != uriEnd) && ((&*(hostEnd))[0] == L':'))
	{
		++hostEnd;
		iterator_t portEnd = (pathStart != uriEnd) ? pathStart : fragmentStart;
		result.WPort = wstring(hostEnd, portEnd);
	}

	// path
	if (pathStart != uriEnd)
	{
		result.WPath = wstring(pathStart, queryStart);
		queryStart += 1;
	}

	// query
	if (queryStart != uriEnd)
	{
		result.WQuery = wstring(queryStart, fragmentStart);
		fragmentStart += 1;
	}

	// fragment
	if (fragmentStart != uriEnd)
	{
		result.WFragment = wstring(fragmentStart, uriEnd);
	}

	result.ErrorCode = Ok;
	return result;

}
