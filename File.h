#pragma once
#include "stdafx.h"
#include "KernelFile.h"

class KernelFile;
class KernelFS;
class FS;

class File {
public:
	char write(BytesCnt count, char* buffer);
	BytesCnt read(BytesCnt count, char* buffer);
	char seek(BytesCnt count);
	BytesCnt filePos();
	char eof();
	BytesCnt getFileSize();
	char truncate();
	char* getName();
	~File();
private:
	friend class FS;
	friend class KernelFS;
	File(char* fname, char mode); //objekat fajla se može kreirati samo otvaranjem
	KernelFile *myImpl;
};