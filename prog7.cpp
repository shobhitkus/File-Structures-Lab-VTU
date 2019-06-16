#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
using namespace std;

class coseq{
	public:
		string list1[100],list2[100];
		int count1,count2;
		void read_list();
		void sort_list();
		void match_list();
};

int main(){
	coseq c;
	c.read_list();
	c.sort_list();
	cout << "\nCommon Names are: "<<endl;
	c.match_list();
	return 0;
}

void coseq::read_list(){
	fstream fp;
	string name;
	count1=0;
	fp.open("1.txt",ios::in);
	if(!fp){
		cout<<"File cannot opoen"<<endl;
		return;
	}
	while(fp){
		getline(fp,name);
		list1[count1++]=name;
	}
	fp.close();
	
	count2=0;
	fp.open("2.txt",ios::in);
	if(!fp){
		cout<<"File cannot opoen"<<endl;
		return;
	}
	while(fp){
		getline(fp,name);
		list2[count2++]=name;
	}
	fp.close();	
}

void coseq::sort_list(){
	int i,j;
	string temp;
	for(i=0;i<count1;i++){
		for(j=i+1;j<count1;j++){
			if(list1[i]>list1[j]){
				temp=list1[i];
				list1[i]=list1[j];
				list1[j]=temp;
			}
		}
	}
	
	for(i=0;i<count2;i++){
		for(j=i+1;j<count2;j++){
			if(list2[i]>list2[j]){
				temp=list2[i];
				list2[i]=list2[j];
				list2[j]=temp;
			}
		}
	}
	
}

void coseq::match_list(){
	int i=0,j=0;
	while(i<=count1 && j<=count2){
		if(list1[i] == list2[j]){
			cout << list1[i] <<endl;
			i++;
			j++;
		}
		if(list1[i]<list2[j])
			i++;
		if(list1[i]>list2[j])
			j++;	
	}
}
