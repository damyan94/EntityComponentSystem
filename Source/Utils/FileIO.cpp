#include "stdafx.h"

#include "FileIO.h"

#include <fstream>

////////////////////////////////////////////////////////////////////////////////
static std::ios_base::openmode GetOpenMode(EWriteMode writeMode)
{
	switch (writeMode)
	{
	case EWriteMode::Out:
		return std::ios::out;

	case EWriteMode::App:
		return std::ios::app;

	default:
		Logger::LogError("Unhandled case in GetOpenMode, reverting to append mode.");
		return std::ios::app;
	}
}

////////////////////////////////////////////////////////////////////////////////
FileIO::FileIO(const std::string& fileName, EWriteMode writeMode)
	: m_FileName(fileName)
	, m_FileStream(new std::fstream)
	, m_WriteMode(writeMode)
{
	SetWriteMode(m_WriteMode);
}

////////////////////////////////////////////////////////////////////////////////
FileIO::~FileIO()
{
	SafeDelete(m_FileStream);
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::Open()
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);
	AssertReturnIf(m_FileStream->is_open() && "The file is already opened.", false);

	m_FileStream->open(m_FileName, GetOpenMode(m_WriteMode));

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::Close()
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);

	m_FileStream->close();

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::Read(Lines& outReadStrings)
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);
	AssertReturnIf(!m_FileStream->is_open() && "The file was not opened.", false);

	outReadStrings.clear();
	outReadStrings.reserve(1000);

	std::string readLine;
	readLine.reserve(512);
	while (std::getline(*m_FileStream, readLine))
	{
		//The '#' symbol will indicate a commented line in the input file
		ContinueIf(readLine[0] == '#' || readLine.size() <= 0);

		outReadStrings.emplace_back(TrimCarriageReturn(readLine));
	}

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::Write(const std::string& writeString)
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);
	AssertReturnIf(!m_FileStream->is_open() && "The file was not opened.", false);

	*m_FileStream << writeString;

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::SetWriteMode(EWriteMode writeMode)
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);

	if (m_FileStream->is_open())
	{
		m_FileStream->close();
	}

	m_WriteMode = writeMode;
	m_FileStream->open(m_FileName, std::ios::in | GetOpenMode(m_WriteMode));

	AssertReturnIf(!m_FileStream->is_open() && 
		"The file was not opened. Failed to change write mode.", false);

	return true;
}

////////////////////////////////////////////////////////////////////////////////
bool FileIO::ClearFileContents()
{
	AssertReturnIf(!m_FileStream && "The file stream was nullptr.", false);

	if (m_FileStream->is_open())
	{
		m_FileStream->close();
	}

	m_FileStream->open(m_FileName, std::ios::out | std::ios::trunc);

	return SetWriteMode(m_WriteMode);
}

////////////////////////////////////////////////////////////////////////////////
const std::string& FileIO::GetFileName() const
{
	return m_FileName;
}

////////////////////////////////////////////////////////////////////////////////
EWriteMode FileIO::GetWriteMode() const
{
	return m_WriteMode;
}

////////////////////////////////////////////////////////////////////////////////
//TODO Can be exported to StringUtils.h/.cpp or something
std::string FileIO::TrimCarriageReturn(const std::string& str)
{
	ReturnIf(!str.empty() && str.back() == '\r', str.substr(0, str.size() - 1));

	return str;
}