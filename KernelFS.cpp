#include "stdafx.h"
#include "KernelFS.h"

std::map<char, Partition*> KernelFS::mountedPartitions;
std::map<char, File*> KernelFS::openedFiles;

KernelFS::KernelFS()
{
}

char KernelFS::mount(Partition* partition)
{
	char letter;
	for (char i = 0; i < 26; ++i) //provjeravamo za svako slovo pojedinacno
	{
		if ((mountedPartitions.find(i)) == mountedPartitions.end()) //ako ne
		{//postoji particija sa datim slovom
			letter = 'A' + i; //pamtimo prvo slobodno slovo
			i = 26; //forsiramo izlazak iz petlje
		}
	}
	mountedPartitions.insert(std::pair<char, Partition*>(letter, partition));
	//ubacujemo par (slovo,particija) u listu montiranih particija
	return letter;
}

char KernelFS::unmount(char part)
{
	if ((mountedPartitions.find(part)) == mountedPartitions.end()) return 0;
	mountedPartitions.erase(part); //uklanjamo trazenu particiju iz liste
	openedFiles.erase(part); //brisemo sve fajlove koji su na trazenoj particiji
	return 1;
}

char KernelFS::format(char part)
{ 
	if ((mountedPartitions.find(part)) == mountedPartitions.end()) return 0;
	Partition* myPart = mountedPartitions.find(part)->second;
	char* buffer = new char[ClusterSize]; //napravimo buffer za upis pojedinacnog cluster-a
	for (unsigned long i = 1; i < ClusterSize; ++i) buffer[i] = 0; //u sve bajtove upisemo 0
	buffer[0] = 3; //upisemo mu jedinicu na prvu i drugu poziciju, posto je prvi bitVector, a drugi je root
	myPart->writeCluster(0, buffer);
	buffer[0] = 0; //sada su sve nule u buffer-u
	for (ClusterNo i = 1;i<myPart->getSize(); ++i)myPart->writeCluster(i, buffer);
		//u sve ostale cluster-e upisujemo nule
	delete[] buffer;
	return 1;
}

char KernelFS::readRootDir(char part, EntryNum n, Directory &d)
{
	if ((mountedPartitions.find(part)) == mountedPartitions.end()) return 0;
	Partition* myPart = mountedPartitions.find(part)->second; //biramo particiju
	char* buffer = new char[ClusterSize];
	myPart->readCluster(1, buffer); //ucitavamo root cluster
	//if (((n + ENTRYCNT)*ENTRYLEN) >= ClusterSize) return 0; //za svaki slucaj
	EntryNum position = 0;
	EntryNum i;
	int k = 1;
	for (i = 0; (i < ClusterSize/ENTRYLEN) && k; ++i)
	{
		Entry temp = *(Entry*)&buffer[i*ENTRYLEN];
		if (temp.name[0] != 0)
		{
			d[position] = temp; //upisivanje u Directory
			position++;
		}
		if (position == 64)k = 0; //ako je procitan pun direktorijum
	}

	k = 1;
	for (; (i < ClusterSize / ENTRYLEN) && k; ++i) //provjeravamo ima li preostalih ulaza
	{
		Entry temp = *(Entry*)&buffer[i*ENTRYLEN];
		if (temp.name[0] != 0)
		{
			i = ClusterSize / ENTRYLEN;
			k = 0;
		}
	}
	if(k)return position; //ako nije bilo preostalih ulaza
	return 65; //ako jest bilo preostalih ulaza
}

char KernelFS::doesExist(char* fname)
{
	char letter, name[FNAMELEN], ext[FEXTLEN];
	splitFileName(fname, letter, name, ext); //razbijamo naziv na dijelove
	
	int k = 0;
	Partition* partition = KernelFS::mountedPartitions.find(letter)->second;
	for (EntryNum i = 0; i < ClusterSize / ENTRYLEN; ++i) //prolazimo kroz sve korjenske ulaze
	{			//da vidimo da li vec postoji fajl sa ovim nazivom
		Entry temp = getRootEntry(partition, i);
		int test = 1;
		for (unsigned long i = 0; i < FNAMELEN; ++i)if (name[i] != temp.name[i])test = 0;
		for (unsigned long i = 0; i < FEXTLEN; ++i)if (ext[i] != temp.ext[i])test = 0;
		if (test)//ako postoji zapamtimo to
		{
			k = 1;
			i = ClusterSize / ENTRYLEN;
		}
	}

	return k;
}

File* KernelFS::open(char* fname, char mode)
{
	File* file = new File(fname, mode);
	if (mode == 'w')
	{
		file->seek(0);
		if (file->getFileSize())file->truncate();
	}
	return file;
}

char KernelFS::deleteFile(char* fname)
{
	if (!doesExist(fname))return 0;

	char letter, name[FNAMELEN], ext[FEXTLEN];
	splitFileName(fname, letter, name, ext); //razbijamo naziv na dijelove

	//brisanje svih fajlova koji imaju isti naziv kao ovaj
	std::for_each(openedFiles.begin(), openedFiles.end(), 
		[&fname](std::pair<char, File*> file)
		{
		if (strcmp(file.second->getName(), fname) == 0)
		{
			file.second->seek(0);
			file.second->truncate();
			openedFiles.erase(file.first);
		}
		});
	return 1;
}

KernelFS::~KernelFS()
{
}
