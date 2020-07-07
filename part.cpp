#include "stdafx.h"
#include "part.h"

Partition::Partition(char* confiurationFileName)
{
	myImpl = new PartitionImpl(confiurationFileName);
}

ClusterNo Partition::getNumOfClusters() const
{
	return myImpl->getNumOfClusters();
}

int Partition::readCluster(ClusterNo clusterNo, char* buffer)
{
	return myImpl->readCluster(clusterNo, buffer);
}

int Partition::writeCluster(ClusterNo clusterNo, const char * buffer)
{
	return myImpl->writeCluster(clusterNo, buffer);
}

ClusterNo Partition::getSize()
{
	return myImpl->getSize();
}

void Partition::show()
{
	myImpl->show();
}

Partition::~Partition()
{
	delete myImpl;
}
