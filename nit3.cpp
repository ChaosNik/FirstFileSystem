#include "stdafx.h"
#include"testprimer.h"

DWORD WINAPI nit3run(){
	wait(sem23);	//ceka nit2
	{
		char filepath1[]="1:\\fajl1.dat";
		filepath1[0]=p1;
		File *f1=FS::open(filepath1,'r');
		wait(mutexx); cout<<"Nit3: Otvoren fajl fajl1.dat"<<endl;
		cout<<"Nit3: signal 2"<<endl; signal(mutexx);
		signal(sem32);//6.signal
		char filepath2[]="1:\\fajl3.dat";
		filepath2[0]=p1;
		File *f2=FS::open(filepath2,'w');
		wait(mutexx); cout<<"Nit3: Kreiran fajl fajl3.dat"<<endl; signal(mutexx);
		wait(mutexx); cout<<"Nit3: signal 1"<<endl; signal(mutexx);
		signal(sem31);//7.signal
		char c;
		while(!f1->eof()){
			f1->read(1,&c);
			f2->write(1,&c);
		}
		delete f1;
		wait(mutexx); cout<<"Nit3: Zatvoren fajl fajl1.dat"<<endl; signal(mutexx);
		delete f2;
		wait(mutexx); cout<<"Nit3: Zatvoren fajl fajl3.dat"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit3: wait 1"<<endl; signal(mutexx);
	wait(sem13);//ceka nit 1

	//4.blok
	{
		char filepath[]="2:\\fajl2.dat";
		filepath[0]=p2;
		File *f=FS::open(filepath,'r');
		wait(mutexx); cout<<"Nit3: Otvoren fajl fajl2.dat"<<endl; signal(mutexx);
		delete f;
		wait(mutexx); cout<<"Nit3: Zatvoren fajl fajl2.dat"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit3: wait 1"<<endl; signal(mutexx);
	wait(sem13);
	wait(mutexx); cout<<"Nit3: wait 2"<<endl; signal(mutexx);
	wait(sem23);

	//5.blok
	{
		char filepath[]="2:\\fajl2.dat";
		filepath[0]=p2;
		File *f=FS::open(filepath,'r');
		wait(mutexx); cout<<"Nit3: Otvoren fajl fajl2.dat"<<endl; signal(mutexx);
		ofstream fout("izlaz1.dat", ios::out|ios::binary);
		char *buff=new char[f->getFileSize()];
		f->read(f->getFileSize(),buff);
		fout.write(buff,f->getFileSize());
		wait(mutexx); cout<<"Nit3: Upisan 'fajl2.dat' u fajl os domacina 'izlaz1.dat'"<<endl; signal(mutexx);
		delete [] buff;
		fout.close();
		delete f;
		wait(mutexx); cout<<"Nit3: Zatvoren fajl fajl2.dat"<<endl; signal(mutexx);
		FS::unmount(p2);
		wait(mutexx); cout<<"Nit3: Demontirana particija p2"<<endl; signal(mutexx);
	}

	wait(mutexx); cout<<"Nit3: Zavrsena!"<<endl; signal(mutexx);
	signal(semMain);
	return 0;
}