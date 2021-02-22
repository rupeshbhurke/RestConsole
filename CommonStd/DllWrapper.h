#pragma once
#include <libloaderapi.h>
#include <string>

#include "StringUtilities.h"

namespace commonStd
{

template <class F> class DllWrapper
	{
		HMODULE m_module;
		F * m_fun;

	private:
		DllWrapper(const DllWrapper&): m_module(nullptr), m_fun(nullptr)
		{
		}

		DllWrapper& operator=(const DllWrapper&)	{	return *this;	}

	public:
		DllWrapper() : m_fun(nullptr), m_module(nullptr) {};
		DllWrapper(const std::wstring & _path, const std::wstring & _fun_name)
			: m_fun(nullptr), m_module(nullptr)
		{
			m_module = ::LoadLibraryExW(_path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (m_module)
			{
				const std::string str = ToString(_fun_name);
				m_fun = static_cast<F*>(GetProcAddress(m_module, str.c_str()));
			}
		};

		bool Open(const std::wstring & _path, const std::wstring & _fun_name)
		{
			if (m_fun || m_module) return false;
			m_module = ::LoadLibraryEx(_path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH);
			if (m_module)
			{
				const std::string str = ToString(_fun_name);
				m_fun = reinterpret_cast<F*>(GetProcAddress(m_module, str.c_str()));
			}
			return m_fun ? true : false;
		};

		~DllWrapper()
		{
			/*if (m_module)::FreeLibrary(m_module);*/
		};

		F * f() { return m_fun; };

		FARPROC GetFunPtr(const std::wstring & _fun_name) const
		{
			if (m_module)
			{
				const std::string str = ToString(_fun_name);
				return GetProcAddress(m_module, str.c_str());
			}
			return nullptr;
		};
	};
} // namespace commonStd