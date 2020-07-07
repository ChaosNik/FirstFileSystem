/*Moj kod*/
//#include "stdafx.h"
//#include <fstream>
//#include "part.h"
//#include "FS.h"
//#include "File.h"
//
//void TestClust();
//void TestTemp();
//void TestFS1();
//void TestBitVector();
//void TestFileWriting();
//void TestFileReading();
//void TestFileTruncating();
//void TestFileGetters();
//void TestTimePermanence();
//void TestReadingDisk3();
//void TestFileWritingForReadRootDir();
//void TestReadRootDir();
//void TestLongFileWriting();
//void TestLongFileReading();
//
//int main()
//{
//	//TestClust();
//	//TestTemp();
//	//TestFS1();
//	//TestBitVector();
//	//TestFileWriting();
//	//TestFileReading();
//	//TestFileTruncating();
//	//TestFileGetters();
//	//TestTimePermanence();
//	//TestReadingDisk3();
//	//TestFileWritingForReadRootDir()
//	//TestReadRootDir();
//	//TestLongFileWriting();
//	TestLongFileReading();
//	system("pause");
//	return 0;
//}
//
//void TestLongFileReading()
//{
//	TestLongFileWriting();
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	File* in = FS::open("A/:lopta.exe", 'a');
//	in->seek(0);
//	char* buffer = new char[ClusterSize * 11];
//	BytesCnt size=in->read(ClusterSize * 10, buffer);
//	for (BytesCnt i = 0; i < size; ++i)
//	{
//		std::cout << (int)buffer[i] << "|";
//	}
//	FS::unmount(a);
//}
//
//void TestLongFileWriting()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out = FS::open("A/:lopta.exe", 'w');
//	//File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char* buffer = new char[ClusterSize * 2000];
//	for (unsigned long i = 0; i < ClusterSize * 1024; ++i)buffer[i] = i;
//	char* buffer1 = new char[ClusterSize * 1024];
//	for (unsigned long i = 0; i < ClusterSize * 1024; ++i)buffer1[i] = 2 * i;
//
//	out->write(3, buffer);
//	out->write(ClusterSize * 20, buffer);
//	//out1->write(ClusterSize * 1, buffer1);
//	//out->write(ClusterSize * 1000 - 3, buffer);
//
//	FS::unmount(a);
//	TestFS1();
//}
//
//void TestReadRootDir()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	//FS::format('A');
//	std::cout << part->getSize() << std::endl;
//	Directory d;
//	int length = FS::readRootDir(a, 0, d);
//	std::cout << length << std::endl;
//	if (length == 65)length = 64;
//	for (int i = 0; i < length; ++i)
//		std::cout << d[i].name << "." << d[i].ext << "|";
//}
//
//void TestFileWritingForReadRootDir()
//{
//	TestFileWriting();
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out;
//	char path[14] = "A/:lopta0.exe";
//	for (int i = 0; i < 62; ++i)
//	{
//		path[8] = i + 'a';
//		out = FS::open(path, 'w');
//	}
//	File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char buffer[ClusterSize * 4];
//	for (unsigned long i = 0; i < ClusterSize * 4; ++i)buffer[i] = 1;
//	char buffer1[ClusterSize * 2];
//	for (unsigned long i = 0; i < ClusterSize * 2; ++i)buffer1[i] = 2;
//
//	out->write(ClusterSize * 4, buffer);
//	out1->write(ClusterSize * 2 / 15, buffer1);
//	FS::unmount(a);
//	//TestFS1();
//}
//
//void TestReadingDisk3()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	//FS::format('A');
//	std::cout<<part->getSize();
//	/*File* out = FS::open("A/:slika.jpg", 'a');
//	char stream[ClusterSize * 2];
//
//	out->seek(0);
//	unsigned long length = out->read(ClusterSize * 2, stream);
//	std::cout << out->filePos() << std::endl;
//	for (int i = 0; i < length; ++i)std::cout << (int)stream[i] << "|";
//	*/
//	/*for (int i = 0; i < 20; ++i)
//	{
//		char stream[ClusterSize];
//		part->readCluster(i, stream);
//		for (int j = 0; j < ClusterSize; ++j) std::cout << (int)stream[j] << "|";
//		std::cout << "\n---------------------------\n";
//	}*/
//}
//
//void TestTimePermanence()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	File* out = FS::open("A/:lopta.exe", 'a');
//	char stream[ClusterSize * 2];
//
//	out->seek(0);
//	unsigned long length = out->read(ClusterSize * 2, stream);
//	std::cout << out->filePos() << std::endl;
//	for (int i = 0; i < length; ++i)std::cout << (int)stream[i] << "|";
//}
//
//void TestFileGetters()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out = FS::open("A/:lopta.exe", 'w');
//	/**/File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char buffer[ClusterSize * 4];
//	for (unsigned long i = 0; i < ClusterSize * 4; ++i)buffer[i] = i;
//	/**/char buffer1[ClusterSize * 2];
//	/**/for (unsigned long i = 0; i < ClusterSize * 2; ++i)buffer1[i] = 2;
//
//	out->write(ClusterSize * 4, buffer);
//	/**/out1->write(ClusterSize * 2 / 15, buffer1);
//	FS::unmount(a);
//
//	a = FS::mount(part);
//	char stream[ClusterSize * 5];
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'a');
//	out->seek(20);
//	out->truncate();
//	out->seek(19);
//	//std::cout << (int)out->seek(100) << std::endl;
//	//std::cout << (int)out->eof() << std::endl;
//	//std::cout << out->filePos() << std::endl;
//	//std::cout << out->getFileSize() << std::endl;
//	//std::cout << out->getName() << std::endl;
//}
//
//void TestFileTruncating()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out = FS::open("A/:lopta.exe", 'w');
//	/**/File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char buffer[ClusterSize * 4];
//	for (unsigned long i = 0; i < ClusterSize * 4; ++i)buffer[i] = i;
//	/**/char buffer1[ClusterSize * 2];
//	/**/for (unsigned long i = 0; i < ClusterSize * 2; ++i)buffer1[i] = 2;
//
//	out->write(ClusterSize * 4, buffer);
//	/**/out1->write(ClusterSize * 2 / 15, buffer1);
//	FS::unmount(a);
//
//	a = FS::mount(part);
//	char stream[ClusterSize * 5];
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'a');
//	out->seek(20);
//	out->truncate();
//	out->seek(0);
//	unsigned long length = out->read(ClusterSize * 4, stream);
//	//std::cout << out->filePos();
//	for (unsigned long i = 0; i < length; ++i)std::cout << (int)stream[i] << "|";
//	//TestFS1();
//}
//
//void TestFileReading()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out = FS::open("A/:lopta.exe", 'w');
//	/**/File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char buffer[ClusterSize * 4];
//	for (unsigned long i = 0; i < ClusterSize * 4; ++i)buffer[i] = i;
//	/**/char buffer1[ClusterSize * 2];
//	/**/for (unsigned long i = 0; i < ClusterSize * 2; ++i)buffer1[i] = 2;
//
//	out->write(ClusterSize * 4, buffer);
//	/**/out1->write(ClusterSize * 2 / 15, buffer1);
//	FS::unmount(a);
//
//	a = FS::mount(part);
//	char stream[ClusterSize * 5];
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	out = FS::open("A/:lopta.exe", 'r');
//	//out = FS::open("A/:ciglica.exe", 'r');
//	out->read(ClusterSize * 4, stream);
//	for(int i = 0; i < ClusterSize * 4; ++i)std::cout << (int)stream[i] << "|";
//	//TestFS1();
//}
//
//void TestFileWriting()
//{
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	FS::format(a);
//	File* out = FS::open("A/:lopta.exe", 'w');
//	File* out1 = FS::open("A/:ciglica.exe", 'w');
//	char buffer[ClusterSize * 4];
//	for (unsigned long i = 0; i < ClusterSize * 4; ++i)buffer[i] = 1;
//	char buffer1[ClusterSize * 2];
//	for (unsigned long i = 0; i < ClusterSize * 2; ++i)buffer1[i] = 2;
//	
//	out->write(ClusterSize * 4, buffer);
//	out1->write(ClusterSize * 2/15 , buffer1);
//	FS::unmount(a);
//	//TestFS1();
//}
//
//void TestBitVector()
//{
//	char* bitVector = new char[ClusterSize];
//	for (int i = 0; i < ClusterSize; ++i)bitVector[i] = 0;
//	setBitVectorBit(bitVector, 16003, 1);
//	std::cout << (int)getBitVectorBit(bitVector, 16003) << std::endl;
//	for (int i = 0; i < ClusterSize; ++i)std::cout << (int)bitVector[i] << "|";
//}
//
//void TestFS1()
//{
//	
//	Partition* part = new Partition("p3.ini");
//	char a = FS::mount(part);
//	std::cout << std::endl << "Number of clusters=" << part->getNumOfClusters();
//	std::cout << std::endl << "--------------------";
//	std::cout << std::endl << std::noskipws;
//	char buffer[ClusterSize];
//	for (int j = 0; j < /*part->getSize()*/25; ++j)
//	{
//		part->readCluster(j, buffer);
//		if(j == 1)for (int i = 0; i < ClusterSize; ++i)std::cout << buffer[i];
//		else for (int i = 0; i < ClusterSize; ++i)std::cout << (int)buffer[i] << "|";
//		std::cout << std::endl << "--------------------" << std::endl;
//	}
//	//part->readCluster(j, buffer);
//
//	FS::unmount(a);
//}
//
//void TestTemp()
//{
//	PartitionImpl a("p3.ini");
//	std::cout << a.getNumOfClusters();
//
//	char* buff;
//	buff = new char[ClusterSize];
//
//	for (int i = 0; i < ClusterSize; ++i)
//		buff[i] = 0;
//
//	/*Ciscenje particije*/
//	/*for (ClusterNo i = 0; i < 100; ++i)
//		a.writeCluster(i, buff);*/
//
//	system("pause");
//}
//
//void TestClust()
//{
//	Partition a("p1.ini");
//	std::cout << a.getNumOfClusters();
//	char* buff;
//	buff = new char[ClusterSize];
//
//	/*Kopiranje kompletne particije*/
//	/*std::ofstream out("out.txt");
//	for (unsigned i = 0; i < a.getSize(); ++i)
//	{
//		int k = a.readCluster(i, buff);
//		if (k)
//			for (int j = 0; j < ClusterSize; ++j) out << buff[j];
//	}
//	out.close();*/
//
//	system("pause");
//}

#include "stdafx.h"
#include"testprimer.h"

using namespace std;

HANDLE nit1,nit2,nit3;
DWORD ThreadID;

HANDLE semMain = CreateSemaphore(NULL, 0, 32, NULL);
HANDLE sem12=CreateSemaphore(NULL,0,32,NULL);
HANDLE sem13=CreateSemaphore(NULL,0,32,NULL);
HANDLE sem21=CreateSemaphore(NULL,0,32,NULL);
HANDLE sem23=CreateSemaphore(NULL,0,32,NULL);
HANDLE sem31=CreateSemaphore(NULL,0,32,NULL);
HANDLE sem32=CreateSemaphore(NULL,0,32,NULL);
HANDLE mutexx = CreateSemaphore(NULL, 1, 32, NULL);

Partition *partition1, *partition2;
char p1, p2;

char *ulazBuffer;
int ulazSize;

ostream& operator<<(ostream &os, const Entry &E) {
	char name[13];
	memcpy(name, E.name, 8);
	name[8] = '.';
	memcpy(name + 9, E.ext, 3);
	name[12] = 0;
	return os << name << " [" << E.size << ']';
}

int main() {
	clock_t startTime, endTime;
	cout << "Pocetak testa!" << endl;
	startTime = clock();//pocni merenje vremena

	{//ucitavamo ulazni fajl u bafer, da bi nit 1 i 2 mogle paralelno da citaju
		FILE *f = fopen("ulaz.dat", "rb");
		if (f == 0) {
			cout << "GRESKA: Nije nadjen ulazni fajl 'ulaz.dat' u os domacinu!" << endl;
			system("PAUSE");
			return 0;//exit program
		}
		ulazBuffer = new char[32 * 1024 * 1024];//32MB
		ulazSize = fread(ulazBuffer, 1, 32 * 1024 * 1024, f);
		fclose(f);
	}

	nit1=CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)nit1run, NULL, 0, &ThreadID); //kreira i startuje niti
	nit2=CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) nit2run,NULL,0,&ThreadID);
	nit3=CreateThread(NULL, 0,(LPTHREAD_START_ROUTINE) nit3run,NULL,0,&ThreadID);

	for(int i=0; i<3; i++) wait(semMain);//cekamo da se niti zavrse
	delete[] ulazBuffer;
	endTime = clock();
	cout << "Kraj test primera!" << endl;
	cout << "Vreme izvrsavanja: " << ((double)(endTime - startTime) / ((double)CLOCKS_PER_SEC / 1000.0)) << "ms!" << endl;
	CloseHandle(mutexx);
	CloseHandle(semMain);
	CloseHandle(sem12);
	CloseHandle(sem13);
	CloseHandle(sem21);
	CloseHandle(sem23);
	CloseHandle(sem31);
	CloseHandle(sem32);
	CloseHandle(nit1);
	CloseHandle(nit2);
	CloseHandle(nit3);
	return 0;
}