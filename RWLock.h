#pragma once
#include <mutex>

class RWLock {
public:
	RWLock()
		: shared()
		, readerCondition(), writerCondition()
		, activeReaders(0), waitingWriters(0), activeWriters(0)
	{}

	void readLock();
	void readUnlock();
	void writeLock();
	void writeUnlock();

private:
	std::mutex shared;
	std::condition_variable readerCondition;
	std::condition_variable writerCondition;
	int activeReaders;
	int waitingWriters;
	int activeWriters;
};
