#include "stdafx.h"
#include "RWLock.h"

void RWLock::readLock()
{
	std::unique_lock<std::mutex> lck(shared);
	while (waitingWriters != 0)
		readerCondition.wait(lck);
	++activeReaders;
	lck.unlock();
}

void RWLock::readUnlock()
{
	std::unique_lock<std::mutex> lck(shared);
	--activeReaders;
	lck.unlock();
	writerCondition.notify_one();
}

void RWLock::writeLock()
{
	std::unique_lock<std::mutex> lck(shared);
	++waitingWriters;
	while (activeReaders != 0 || activeWriters != 0)
		writerCondition.wait(lck);
	++activeWriters;
	lck.unlock();
}

void RWLock::writeUnlock()
{
	std::unique_lock<std::mutex> lck(shared);
	--waitingWriters;
	--activeWriters;
	if (waitingWriters > 0)
		writerCondition.notify_one();
	else
		readerCondition.notify_all();
	lck.unlock();
}