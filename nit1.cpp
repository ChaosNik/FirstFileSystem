#include "stdafx.h"
#include"testprimer.h"

DWORD WINAPI nit1run(){
	//prvi blok
	wait(mutexx); partition1=new Partition("p1.ini"); signal(mutexx);
	wait(mutexx); cout<<"Nit1: Kreirana particija"<<endl; signal(mutexx);
	p1=FS::mount(partition1);
	wait(mutexx); cout<<"Nit1: Montirana particija"<<endl; signal(mutexx);
	FS::format(p1);
	wait(mutexx); cout<<"Nit1: Formatirana particija"<<endl; signal(mutexx);
	{
		char filepath[]="1:\\fajl1.dat";
		filepath[0]=p1;
		File *f=FS::open(filepath,'w');
		wait(mutexx); cout<<"Nit1: Kreiran fajl 'fajl1.dat'"<<endl; signal(mutexx);
		f->write(ulazSize,ulazBuffer);
		wait(mutexx); cout<<"Nit1: Prepisan sadrzaj 'ulaz.dat' u 'fajl1.dat'"<<endl; signal(mutexx);
		f->seek(0);
		char *toWr=new char[ulazSize+1];
		f->read(0x7FFFFFFF,toWr);//namerno veci broj od velicine fajla
		toWr[ulazSize]=0;//zatvaramo string pre ispisa
		wait(mutexx); 
			cout<<"Nit1: Sadrzaj fajla 'fajl1.dat'"<<endl;
			cout<<toWr<<endl;
		signal(mutexx);
		delete [] toWr;
		delete f;
		wait(mutexx); cout<<"Nit1: zatvoren fajl 'fajl1.dat'"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit1: signal 2"<<endl; signal(mutexx);
	signal(sem12);
	wait(mutexx); cout<<"Nit1: wait 3"<<endl; signal(mutexx);
	wait(sem31);//ceka nit 3

	//2.blok
	{
		File *src,*dst;
		char filepath1[]="1:\\fajl3.dat";
		filepath1[0]=p1;
		src=FS::open(filepath1,'r');
		wait(mutexx); cout<<"Nit1: Otvoren fajl fajl3.dat za citanje!"<<endl; signal(mutexx);
		char filepath2[]="2:\\fajl4.dat";
		filepath2[0]=p2;
		dst=FS::open(filepath2,'w');
		wait(mutexx); cout<<"Nit1: Otvoren fajl fajl4.dat za upis!"<<endl; signal(mutexx);
		int srcLen=src->getFileSize();
		char c;
		for(int i=0;i<srcLen/2;i++){
			src->read(1,&c);
			dst->write(1,&c);
		}
		wait(mutexx); cout<<"Nit1: Fajl 'fajl3.dat' prepisan do pola u fajl 'fajl4.dat'"<<endl; signal(mutexx);
		delete dst;
		wait(mutexx); cout<<"Nit1: Zatvoren fajl 'fajl4.dat'"<<endl; signal(mutexx);
		delete src;
		wait(mutexx); cout<<"Nit1: Zatvoren fajl 'fajl3.dat'"<<endl; signal(mutexx);
	}
	
	char filepath[]="2:\\fajl2.dat";
	filepath[0]=p2;
	File *f=FS::open(filepath,'w');
	
	wait(mutexx); cout<<"Nit1: Otvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
	wait(mutexx); cout<<"Nit1: signal 2"<<endl; signal(mutexx);
	signal(sem12);//8.signal
	wait(mutexx); cout<<"Nit1: signal 3"<<endl; signal(mutexx);
	signal(sem13);//9.signal
	
	//3.blok
	{
		char *zeroBuff=new char[4000];
		memset(zeroBuff,0,4000);
		for(int i=0;i<5;i++){
			f->seek(0);
			f->write(2049,zeroBuff);
			f->write(2048,zeroBuff);
			f->write(2047,zeroBuff);
			wait(mutexx); cout<<"Nit1: 'fajl2.dat' "<<(i+1)<<". put popunjen nulama"<<endl; signal(mutexx);
		}
		delete [] zeroBuff;
		delete f;
		wait(mutexx); cout<<"Nit1: Zatvoren fajl 'fajl2.dat'"<<endl; signal(mutexx);
		signal(sem13);
	}
	wait(mutexx); cout<<"Nit1: wait 2"<<endl; signal(mutexx);
	wait(sem21);//ceka nit 2

	//4.blok
	{
		Entry D[64];
		p1=FS::mount(partition1);
		int lim=FS::readRootDir(p1,0,D);
		wait(mutexx);
			cout<<"Nit1: Namontirana particija p1"<<endl;
			cout<<"Nit1: p1 root dir:"<<endl;
			cout<<'\t'<<p1<<':'<<endl;
			for(int i=0;i<lim;i++) cout<<"\t"<<((i!=lim-1)?char(195):char(192))<<' '<<D[i]<<endl;
		signal(mutexx);

		char filepath[]="1:\\fajl1.dat";
		filepath[0]=p1;
		File *f=FS::open(filepath,'r');
		wait(mutexx); cout<<"Nit1: Otvoren fajl 'fajl1.dat'"<<endl; signal(mutexx);
		ofstream fout("izlaz2.dat", ios::out|ios::binary);
		char *buff=new char[f->getFileSize()];
		f->read(f->getFileSize(),buff);
		fout.write(buff,f->getFileSize());
		wait(mutexx); cout<<"Nit1: Upisan 'fajl1.dat' u fajl os domacina 'izlaz2.dat'"<<endl; signal(mutexx);
		delete [] buff;
		fout.close();
		delete f;
		wait(mutexx); cout<<"Nit1: Zatvoren fajl 'fajl1.dat'"<<endl; signal(mutexx);
		FS::unmount(p1);
		wait(mutexx); cout<<"Nit1: Demontirana particija p1"<<endl; signal(mutexx);
	}
	wait(mutexx); cout<<"Nit1: Zavrsena!"<<endl; signal(mutexx);
	signal(semMain);
	return 0;
}
