// RazorBridge.h

#pragma once
#include <Windows.h>
#include <vector>
#include <string>
#include <msclr\marshal_cppstd.h>
#include "ParseUri.h";


namespace RazorBridge {

	public ref class RazorBridgeWrapper
	{

	public:
		RazorBridgeWrapper() { parseUri = new UriParser::ParseUri(); }
		~RazorBridgeWrapper() { this->!RazorBridgeWrapper(); }
		!RazorBridgeWrapper()
		{
			delete parseUri;
			parseUri = NULL;
		}

		virtual System::String^ __clrcall Parse(System::String^ uri) {
			std::wstring wuri = msclr::interop::marshal_as<std::wstring>(uri);
			UriParser::ParseUri res= parseUri->Parse(wuri);
			return gcnew System::String(res.WScheme.c_str());
		}

	private:
		UriParser::ParseUri* parseUri;
	};
}
