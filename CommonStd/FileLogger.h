#pragma once

#include <fstream>
#include <list>
#include <string>
#include <sstream>

namespace commonStd
{

template<intmax_t WriteStep, bool truncate>
class FileLogger
{
	static_assert(WriteStep > 0,
		"Write step cannot be zero or negative.");
	
public:
	static std::shared_ptr<FileLogger<WriteStep, truncate> > MakePtr( const std::wstring & filePath);
	static std::shared_ptr<FileLogger<WriteStep, truncate> > MakePtr( const std::wstring & filePath, const std::wstring& headerString);
	
	void Disable(bool disable);
	void Append(const std::wstring & string );
	void AppendLine(const std::wstring & string );
	void Commit();
	
	virtual ~FileLogger();

protected:
	FileLogger( const std::wstring & filePath);
	FileLogger( const std::wstring & filePath, const std::wstring& headerString);

	
private:
	void OpenFile(const std::wstring& filePath);
	
	std::list<std::wstring> m_logStrings;
	const std::wstring _filePath;
	const std::wstring _headerString;
	bool _headerStringWritten;
	std::wofstream m_logFile;
	bool _disable;
	static constexpr int step_at = WriteStep;

	
};

template<intmax_t WriteStep, bool truncate>
inline FileLogger<WriteStep, truncate>::FileLogger(const std::wstring& filePath)
	: _filePath(filePath), _headerString(L""), _headerStringWritten(false), _disable(false)
{}

template<intmax_t WriteStep, bool truncate>
inline FileLogger<WriteStep, truncate>::FileLogger(const std::wstring& filePath, const std::wstring& headerString)
	: _filePath(filePath), _headerString(headerString), _headerStringWritten(false), _disable(false)
{}

template<intmax_t WriteStep, bool truncate>
inline FileLogger<WriteStep, truncate>::~FileLogger()
{
	//destructor must not throw!
	try
	{
		if(m_logStrings.size() > 0)
			m_logStrings.clear();
		if ( m_logFile.is_open() )
			m_logFile.close();
	}
	catch (...) {}
}

template<intmax_t WriteStep, bool truncate>
std::shared_ptr<FileLogger<WriteStep, truncate> > FileLogger<WriteStep, truncate>::MakePtr(const std::wstring& filePath)
{
	return std::shared_ptr<FileLogger<WriteStep, truncate> >(new FileLogger<WriteStep, truncate>(filePath));
}

template<intmax_t WriteStep, bool truncate>
std::shared_ptr<FileLogger<WriteStep, truncate> > FileLogger<WriteStep, truncate>::MakePtr(const std::wstring& filePath,
	const std::wstring& headerString)
{
	return std::shared_ptr<FileLogger<WriteStep, truncate> >(new FileLogger<WriteStep, truncate>(filePath, headerString));
}

template <intmax_t WriteStep, bool truncate>
void FileLogger<WriteStep, truncate>::Disable(bool disable)
{
	_disable = disable;
}

template<intmax_t WriteStep, bool truncate>
inline void FileLogger<WriteStep, truncate>::Append(const std::wstring & string)
{
	if ( _disable ) return;
	m_logStrings.insert(m_logStrings.end(), string);
	if (m_logStrings.size() == step_at)
	{
		Commit();
	}
}

template<intmax_t WriteStep, bool truncate>
inline void FileLogger<WriteStep, truncate>::AppendLine(const std::wstring & string)
{
	if ( _disable ) return;
	std::wstringstream ws;
	ws << string << std::endl;
	Append(ws.str());
}
template<intmax_t WriteStep, bool truncate>
inline void FileLogger<WriteStep, truncate>::Commit()
{
	if ( _disable ) return;
	if ( !m_logFile.is_open())
	{
		OpenFile(_filePath);
	}

	if ( !_headerString.empty() && !_headerStringWritten)
	{
		_headerStringWritten = true;
		m_logFile << _headerString << std::endl;
	}

	for (const auto& cs : m_logStrings)
	{
		m_logFile << cs;
	}
	m_logStrings.clear();
	m_logFile.close();
}

template<intmax_t WriteStep, bool truncate>
inline void FileLogger<WriteStep, truncate>::OpenFile(const std::wstring& filePath)
{
	m_logFile.open(filePath, truncate ? std::ios::trunc : std::ios::app);
}

} // namespace commonStd
