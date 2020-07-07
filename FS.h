#pragma once

#include "stdafx.h"
#include "KernelFS.h"

class KernelFile;
class File;
class KernelFS;

class FS {
public:
	static char mount(Partition* partition);// montiranje particije, vraca dodjeljeno slovo
	static char unmount(char part);// demontira particiju oznacenu datim slovom. Vraca 0 u slucaju neuspjeha ili 1 u slucaju uspjeha
	static char format(char part);// particija zadata slovom se formatira. Vraca 0 u slucaju neuspjeha ili 1 u slucaju uspjeha
	static char readRootDir(char part, EntryNum n, Directory& d);// prvim argumentom se zadaje particija,
																 // drugim redni broj validnog ulaza od kog se počinje čitanje
																 // treci argument je naziv fajla sa apsolutnom putanjom
	static char doesExist(char* fname);
	static File* open(char* fname, char mode);
	static char deleteFile(char* fname);

	~FS();
protected:
	FS();
	static KernelFS *myImpl;
};