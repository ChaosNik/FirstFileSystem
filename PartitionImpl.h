#pragma once
#include "stdafx.h"
#include "RWLock.h"

class PartitionImpl
{
public:
	PartitionImpl(char* confiurationFileName);
	ClusterNo getNumOfClusters() const; //vraca broj(popunjenih) klastera koji pripadaju particiji

	int readCluster(ClusterNo clusterNo, char* buffer) const; //cita zadati klaster i u slucaju uspeha vraca 1; u suprotnom 0
	int writeCluster(ClusterNo clusterNo, const char* buffer) const; //upisuje zadati klaster i u slucaju uspeha vraca 1; u suprotnom 0

	void show();
	ClusterNo getSize();
	~PartitionImpl();
	friend class KernelFile;
	friend class File;
	friend class Partition;
private:
	ClusterNo size;
	FILE* file;
};
