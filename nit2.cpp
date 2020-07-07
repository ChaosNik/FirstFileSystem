#include "stdafx.h"
#include"testprimer.h"

DWORD WINAPI nit2run(){
	//1.blok
	wait(mutexx); partition2=new Partition("p2.ini"); signal(mutexx);
	wait(mutexx); cout<<"Nit2: Kreirana particija"<<endl; signal(mutexx);
	p2=FS::mount(partition2);
	wait(mutexx); cout<<"Nit2: Montirana particija"<<endl; signal(mutexx);
	FS::format(p2);
	wait(mutexx); cout<<"Nit2: Formatirana particija"<<endl; signal(mutexx);
	{
		char filepath[]="2:\\fajl2.dat";
		filepath[0]=p2;
		File *f=FS::open(filepath,'w');
		wait(mutexx); cout<<"Nit2: Kreiran fajl 'fajl2.dat'"<<endl; signal(mutexx);
		f->write(ulazSize,ulazBuffer);
		wait(mutexx); cout<<"Nit2: Prepisan sadrzaj 'ulaz.dat' u 'fajl2.dat'"<<endl; signal(mutexx);
		delete f;
		wait(mutexx); cout<<"Nit2: zatvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
	}	
	wait(mutexx); cout<<"Nit2: wait 1"<<endl; signal(mutexx);
	wait(sem12);//ceka nit 1
	wait(mutexx); cout<<"Nit2: signal 3"<<endl; signal(mutexx);
	signal(sem23);//signalizira nit 3 - 5.signal
	wait(mutexx); cout<<"Nit2: wait 3"<<endl; signal(mutexx);
	wait(sem32);//ceka nit 3

	//2.blok
	{
		File *src,*dst;
		char filepath1[]="1:\\fajl1.dat";
		filepath1[0]=p1;
		src=FS::open(filepath1,'r');
		src->seek(src->getFileSize()/2);//pozicionira se na pola fajla
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl1.dat' i pozicionirani smo na polovini"<<endl; signal(mutexx);
		char filepath2[]="1:\\fajl5.dat";
		filepath2[0]=p1;
		dst=FS::open(filepath2,'w');
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl5.dat'"<<endl; signal(mutexx);
		char c;
		while(!src->eof()){
			src->read(1,&c);
			dst->write(1,&c);
		}
		wait(mutexx); cout<<"Nit2: Prepisana druga polovina 'fajl1.dat' u 'fajl5.dat'"<<endl; signal(mutexx);
		delete dst;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl5.dat'"<<endl; signal(mutexx);
		delete src;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl1.dat'"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit2: wait 1"<<endl; signal(mutexx);
	wait(sem12);//ceka nit1

	//3.blok
	{
		File *f2,*f4,*f5;
		char filepath1[]="2:\\fajl2.dat";
		filepath1[0]=p2;
		f2=FS::open(filepath1,'w');
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
		char filepath2[]="2:\\fajl4.dat";
		filepath2[0]=p2;
		f4=FS::open(filepath2,'r');
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl4.dat'"<<endl; signal(mutexx);
		char c;
		while(!f4->eof()){
			f4->read(1,&c);
			f2->write(1,&c);
		}
		wait(mutexx); cout<<"Nit2: 'fajl4.dat' iskopiran u 'fajl2.dat'"<<endl; signal(mutexx);
		delete f4;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl4.dat'"<<endl; signal(mutexx);
		delete f2;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
		f2=FS::open(filepath1,'a');
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
		char filepath3[]="1:\\fajl5.dat";
		filepath3[0]=p1;
		f5=FS::open(filepath3,'r');
		wait(mutexx); cout<<"Nit2: Otvoren fajl 'fajl5.dat'"<<endl; signal(mutexx);
		while(!f5->eof()){
			f5->read(1,&c);
			f2->write(1,&c);
		}
		wait(mutexx); cout<<"Nit2: 'fajl5.dat' dopisan na kraj 'fajl2.dat'"<<endl; signal(mutexx);
		delete f5;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl5.dat'"<<endl; signal(mutexx);
		delete f2;
		wait(mutexx); cout<<"Nit2: Zatvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
	}
	signal(sem23);//11. signal

	//4.blok
	{
		char filepath[]="1:\\fajl5.dat";
		filepath[0]=p1;
		FS::deleteFile(filepath);
		wait(mutexx); cout<<"Nit2: Obrisan fajl 'fajl5.dat'"<<endl; signal(mutexx);
		FS::unmount(p1);
		wait(mutexx); cout<<"Nit2: Demontirana p1 particija"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit2: signal 1"<<endl; signal(mutexx);
	signal(sem21);//12. signal

	wait(mutexx); cout<<"Nit2: Zavrsena!"<<endl; signal(mutexx);
	signal(semMain);
	return 0;
}