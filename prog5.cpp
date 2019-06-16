#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>

using namespace std;

class student{
	public:
		string usn,name,sem;
		void input();
		void pack();
}s1;

struct index{
	string usn;
	int addr;
}i1[10],temp;

int count;
fstream fp;

void create_index();
void sort_index();
void search();
int bin_search(string);
void del();

int main(){
	int choice;
	fp.open("prg5.txt",ios::out|ios::app);
	fp.close();
	create_index();
	while(1){
		cout << "1.Add to Records\n2.To search for a Record\n3.To delete a Record\n4.Exit\nEnter Choice:";
		cin >> choice;
		switch(choice){
			case 1:
				s1.input();
				fp.open("prg5.txt",ios::out|ios::app);
				if(!fp){
					cout << "File Could not open" << endl;
					return 0;
				}
				s1.pack();
				fp.close();
				break;
			case 2:
				search();
				break;
			case 3:
				del();
				break;
			default:
				exit(0);
			
		}
	}
	return 0;
}

void create_index(){
	int pos,i;
	string seg,usnbuff;
	count=0;
	fp.open("prg5.txt",ios::in);
	if(!fp){
		cout << "File Could not open" << endl;
		return;
	}
	while(fp){
		usnbuff.erase();
		pos = fp.tellg();
		getline(fp,usnbuff,'|');
		getline(fp,seg);
		if(usnbuff[0] == '*' || usnbuff.length() == 0)
			continue;
		count++;
		i1[count].usn=usnbuff;
		i1[count].addr=pos;
	}
	fp.close();
	sort_index();
}

void sort_index(){
	for(int i=0;i<=count;i++){
		for(int j=i+1;j<=count;j++)
			if(i1[i].usn > i1[j].usn){
				temp.usn = i1[i].usn;
				temp.addr = i1[i].addr;
				
				i1[i].usn=i1[j].usn;
				i1[i].addr=i1[j].addr;
				
				i1[j].usn=temp.usn;
				i1[j].addr=temp.addr;
			}
	}
}

void student::input(){
	cout << "Enter USN: ";
	cin >> usn;
	cout << "Enter Name: ";
	cin >> name;
	cout << "Enter Semester: ";
	cin >> sem;	
}

void student::pack(){
	int pos = fp.tellg();
	string buff = usn+"|"+name+"|"+sem+"|";
	fp << buff << endl;
	count++;
	i1[count].usn=usn;
	i1[count].addr=pos;
	sort_index();
}

void search(){
	string usn_srch,buff;
	cout << "Enter the USN of the Student to be Found:";
	cin >> usn_srch;
	int pos = bin_search(usn_srch);
	if(pos == -1){
		cout << "Record not found"<<endl;
		return;
	}
	cout << "Record Found!\n";
	cout << "USN|Name|Sem"<<endl;
	fp.open("prg5.txt",ios::in);
	if(!fp){
		cout << "File Could not open" << endl;
		return;
	}
	fp.seekg(i1[pos].addr,ios::beg);
	getline(fp,buff);
	cout << buff << endl;
	fp.close();
}

int bin_search(string usn_srch){
	int l=0,h=count;
	int mid=(l+h)/2;
	while(l<=h){
		if(i1[mid].usn == usn_srch)
			return mid;
		if(i1[mid].usn < usn_srch)
			l=mid+1;
		if(i1[mid].usn > usn_srch)
			h=mid-1;
		mid=(l+h)/2;
	}
	return -1;
}

void del(){
	string usn_srch;
	cout << "Enter the USN of the Student to be Deleted:";
	cin >> usn_srch;
	int pos = bin_search(usn_srch);
	if(pos == -1){
		cout << "Record Not Found!"<<endl;
		return;
	}
	cout << "Record Found and Deleted!" << endl;
	fp.open("prg5.txt",ios::out|ios::in);
	fp.seekp(i1[pos].addr,ios::beg);
	fp.put('*');
	fp.close();
	
	for(int i=pos;i<count;i++){
		i1[i].usn = i1[i+1].usn;
		i1[i].addr = i1[i+1].addr;
	}
	count--;
}
