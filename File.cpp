#include "stdafx.h"
#include "File.h"

char File::write(BytesCnt count, char* buffer)
{
	return myImpl->write(count, buffer);
}

BytesCnt File::read(BytesCnt count, char* buffer)
{
	return myImpl->read(count, buffer);
}

char File::seek(BytesCnt count)
{
	return myImpl->seek(count);
}

BytesCnt File::filePos()
{
	return myImpl->filePos();
}

char File::eof()
{
	return myImpl->eof();
}

BytesCnt File::getFileSize()
{
	return myImpl->getFileSize();
}

char File::truncate()
{
	return myImpl->truncate();
}

char * File::getName()
{
	return myImpl->getName();
}

File::~File()
{
	myImpl->~KernelFile();
}

File::File(char* fname, char mode)
{
	myImpl = new KernelFile(fname, mode, this);
}