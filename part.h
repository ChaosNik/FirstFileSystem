#pragma once
#include "stdafx.h"
#include "PartitionImpl.h"

class PartitionImpl;

class Partition {
public:
	Partition(char* letter);
	virtual ClusterNo getNumOfClusters() const; //vraca broj klastera koji pripadaju particiji

	virtual int readCluster(ClusterNo clusterNo, char* buffer); //cita zadati klaster i u slucaju uspeha vraca 1; u suprotnom 0
	virtual int writeCluster(ClusterNo, const char* buffer); //upisuje zadati klaster i u slucaju uspeha vraca 1; u suprotnom 0

	ClusterNo getSize(); //koristena za testiranje
	virtual void show();
	virtual ~Partition();
	friend class KernelFile;
	friend class File;
private:
	PartitionImpl *myImpl;
};
