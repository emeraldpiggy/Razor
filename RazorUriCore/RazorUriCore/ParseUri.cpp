#include "stdafx.h"
#include "ParseUri.h"

#include <algorithm>
#include <cstring>
#include <stdlib.h>

static bool isValidScheme(const string& schemeName)
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

UriParser::ParseUri UriParser::ParseUri::Parse(const string& uri)
{
UriParser:ParseUri result;

	const char* curStr = uri.c_str();

	const char* localStr = strchr(curStr, ':');
	if (!localStr)
	{
		return ParseUri(NoUrlCharacter);
	}

	result.Scheme = string(curStr, localStr - curStr);

	if (!isValidScheme(result.Scheme))
	{
		return ParseUri(InvalidSchemeName);
	}

	transform(result.Scheme.begin(), result.Scheme.end(), result.Scheme.begin, ::tolower);

	curStr = localStr + 1;

	if (*curStr++ != '/')
	{
		return ParseUri(NoDoubleSlash);
	}
	if (*curStr++ != '/')
	{
		return ParseUri(NoDoubleSlash);
	}


	bool hasUserName = false;

	const char* localStr = curStr;

	while (*localStr)
	{
		if (*localStr == '@')
		{
			hasUserName = true;
			break;
		}
		else if (*localStr == '/')
		{
			hasUserName = false;
			break;
		}

		localStr++;
	}

	localStr = curStr;

	if (hasUserName)
	{
		while (*localStr && *localStr != ':' && *localStr != '@') localStr++;

		result.UserName = std::string(curStr, localStr - curStr);

		curStr = localStr;

		if (*curStr == ':')
		{
			curStr++;

			localStr = curStr;

			while (*localStr && *localStr != '@') localStr++;

			result.Password = std::string(curStr, localStr - curStr);

			curStr = localStr;
		}

		if (*curStr != '@')
		{
			return ParseUri(NoAtSign);
		}

		curStr++;
	}

	bool hasBracket = (*curStr == '[');

	localStr = curStr;

	while (*localStr)
	{
		if (hasBracket && *localStr == ']')
		{
			localStr++;
			break;
		}
		else if (!hasBracket && (*localStr == ':' || *localStr == '/'))
		{
			break;
		}

		localStr++;
	}

	result.Host = std::string(curStr, localStr - curStr);

	curStr = localStr;

	if (*curStr == ':')
	{
		curStr++;

		localStr = curStr;

		while (*localStr && *localStr != '/') localStr++;

		result.Port = std::string(curStr, localStr - curStr);

		curStr = localStr;
	}

	if (!*curStr)
	{
		return ParseUri(UnexpectedEndOfLine);
	}

	if (*curStr != '/')
	{
		return ParseUri(NoSlash);
	}

	curStr++;

	localStr = curStr;

	while (*localStr && *localStr != '#' && *localStr != '?') localStr++;

	result.Path = std::string(curStr, localStr - curStr);

	curStr = localStr;

	if (*curStr == '?')
	{
		curStr++;

		localStr = curStr;

		while (*localStr && *localStr != '#') localStr++;

		result.Query = std::string(curStr, localStr - curStr);

		curStr = localStr;
	}

	// check for fragment
	if (*curStr == '#')
	{
		// skip '#'
		curStr++;

		// read fragment
		localStr = curStr;

		while (*localStr) localStr++;

		result.Fragment = std::string(curStr, localStr - curStr);

		curStr = localStr;
	}

	result.ErrorCode = Ok;

	return result;
}
