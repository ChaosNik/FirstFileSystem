#include "stdafx.h"
#include "PartitionImpl.h"

PartitionImpl::PartitionImpl(char* confiurationFileName)
{
	std::ifstream in(confiurationFileName);
	std::string name;
	in >> name;
	in >> size;
	in.close();

	file = fopen(name.c_str(), "rb+");

}

ClusterNo PartitionImpl::getNumOfClusters() const
{
	ClusterNo clusterNo = 0;
	
	char* bitVector = new char[ClusterSize];
	this->readCluster(0, bitVector);
	for (unsigned long i = 0; i < ClusterSize*8; ++i)
		clusterNo += getBitVectorBit(bitVector,i);
	delete[] bitVector;
	return clusterNo;
}

int PartitionImpl::readCluster(ClusterNo clusterNo, char* buffer) const
{
	int err = fseek(file, clusterNo*ClusterSize, SEEK_SET);
	err += fread(buffer, ClusterSize, 1, file);
	return err != ClusterSize;
}

int PartitionImpl::writeCluster(ClusterNo clusterNo, const char* buffer) const
{
	int err = fseek(file, clusterNo*ClusterSize, SEEK_SET);
	err += fwrite(buffer, ClusterSize, 1, file);
	fseek(file, clusterNo*ClusterSize, SEEK_SET);
	return err != ClusterSize;
}

void PartitionImpl::show()
{
	char* buffer = new char[ClusterSize+1];
	buffer[ClusterSize] = 0;
	int err = fseek(file, 0, SEEK_SET);
	for (unsigned long i = 0; i < size; ++i)
	{
		err += fread(buffer, ClusterSize, 1, file);
		std::cout << buffer;
		std::cout << std::endl << std::endl;
	}
	delete[] buffer;
}

ClusterNo PartitionImpl::getSize()
{
	return size;
}

PartitionImpl::~PartitionImpl()
{
	fclose(file);
}