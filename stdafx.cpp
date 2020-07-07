// stdafx.cpp : source file that includes just the standard includes
// FileSystem.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "part.h"
#include "FS.h"

// TODO: reference any additional headers you need in STDAFX.H
// and not in this file

void splitFileName(char* fname, char& letter, char* name, char* ext)
{
	for (int j = 0; j < 8; j++)name[j] = 0;
	letter = fname[0];
	int i = 3;
	while (fname[i] != '.')
	{
		name[i - 3] = fname[i];
		++i;
	}
	++i;
	for (int j = 0; j < FEXTLEN; ++j)ext[j] = fname[i + j];
}

char* getBitVector(Partition* partition)
{
	char* bitVector = new char[ClusterSize];
	partition->readCluster(0, bitVector);
	return bitVector;
}

void setBitVectorBit(char* bitVector, unsigned long position, char value)
{
	if (value)bitVector[(position / 8) % ClusterSize] |= (1 << (position % 8));
	else bitVector[(position / 8) % ClusterSize] &= (~(1 << (position % 8)));
}

char getBitVectorBit(char * bitVector, unsigned long position)
{
	return (bitVector[position / 8] & (1 << (position % 8))) == (1 << (position % 8));
}

Entry getRootEntry(Partition* partition, EntryNum rootEntryNumber)
{
	char* rootCluster = new char[ClusterSize];
	partition->readCluster(1, rootCluster);

	Entry* directory = (Entry*)(rootCluster);
	return directory[rootEntryNumber];
}

ClusterNo getFirstLevelEntry(char* indexCluster, EntryNum position)
{
	unsigned* buffer = (unsigned*)(indexCluster); //prolazi ako uzmem adresu indexCluster-a
	unsigned result = buffer[position];
	return result;
}

void setFirstLevelEntry(char indexCluster[], EntryNum position, ClusterNo clusterNo)
{
	char* buffer = (char*)(&clusterNo);
	indexCluster[4 * position] = buffer[0];
	indexCluster[4 * position + 1] = buffer[1];
	indexCluster[4 * position + 2]= buffer[2];
	indexCluster[4 * position + 3]= buffer[3];
}

void setRootEntry(EntryNum rootEntryNumber, Entry rootEntry, Partition* partition)
{
	char rootCluster[ClusterSize];
	partition->readCluster(1, rootCluster);

	Entry* directory = (Entry*)(rootCluster);
	directory[rootEntryNumber] = rootEntry;
	partition->writeCluster(1, rootCluster);
}
