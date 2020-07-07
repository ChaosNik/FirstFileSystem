// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<windows.h>
#include<ctime>



// TODO: reference additional headers your program requires here
#include <vector>
#include <thread>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <bitset>
#include <map>

typedef unsigned long ClusterNo;
const unsigned long ClusterSize = 2048;

typedef unsigned long BytesCnt;
typedef unsigned long EntryNum;
const unsigned long ENTRYCNT = 64;
const unsigned int FNAMELEN = 8;
const unsigned int FEXTLEN = 3;

struct Entry
{
	char name[FNAMELEN];
	char ext[FEXTLEN];
	char reserved;
	unsigned long indexCluster;
	unsigned long size;
};

const unsigned long ENTRYLEN = (FNAMELEN + FEXTLEN + 1 + 4 + 4);

typedef Entry Directory[ENTRYCNT];

void splitFileName(char* fname, char& letter, char* name, char* ext);

class Partition;
class PartitoinImpl;
class FS;
char* getBitVector(Partition* partition);
void setBitVectorBit(char* bitVector, unsigned long position, char value);
char getBitVectorBit(char* bitVector, unsigned long position);

Entry getRootEntry(Partition* partition, EntryNum rootEntryNumber);
ClusterNo getFirstLevelEntry(char* indexCluster, EntryNum position);
void setFirstLevelEntry(char indexCluster[], EntryNum position, ClusterNo clusterNo);
void setRootEntry(EntryNum rootEntryNumber, Entry rootEntry, Partition* partition);