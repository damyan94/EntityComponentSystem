#pragma once

////////////////////////////////////////////////////////////////////////////////
enum class EWriteMode
{
	Out,
	App,
};

////////////////////////////////////////////////////////////////////////////////
class FileIO
{
public:
	FileIO(const std::string& fileName, EWriteMode writeMode = EWriteMode::App);
	~FileIO();

	bool Open();
	bool Close();

	bool Read(Lines& outReadLines);
	bool Write(const std::string& writeString);

	bool SetWriteMode(EWriteMode writeMode);
	bool ClearFileContents();

	const std::string&	GetFileName() const;
	EWriteMode			GetWriteMode() const;

private:
	std::string			TrimCarriageReturn(const std::string& str);

private:
	const std::string	m_FileName;
	std::fstream*		m_FileStream;
	EWriteMode			m_WriteMode;
};