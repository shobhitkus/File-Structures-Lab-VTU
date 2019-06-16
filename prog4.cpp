#include<iostream>
#include<fstream>
#include<fstream>
#include<cstdlib>

using namespace std;

class student{
	string usn,name,sem;
	public:
		void input();
		void output();
		void pack();
		void unpack(int);
}s1;

int rrn[100],count=0;
fstream fp1;

void findrrn();
void search();

int main(){
	int choice;
	fp1.open("rrnrec.txt",ios::out|ios::app);
	fp1.close();
	findrrn();
	
	while(1){
		cout << "\n1.Insert a Record\n2.Search for Record using RRN\n3.Exit\nEnter Your Choice: "<<endl;
		cin >> choice;
		switch(choice){
			case 1:
				s1.input();
				fp1.open("rrnrec.txt",ios::out|ios::app);
				if(!fp1){
					cout << "File Could not open" << endl;
					return 0;
				}
				s1.pack();
				fp1.close();
				break;
			
			case 2:
				search();
				break;
			default:
				return 0;				
		}
	}
	return 0;
}

void findrrn(){
	int pos;
	string seg;
	fp1.open("rrnrec.txt",ios::in);
	if(!fp1){
		cout << "File Could not open" << endl;
		return;
	}
	while(fp1){
		pos=fp1.tellg();
		getline(fp1,seg);
		if(seg.length()==0)
			continue;
		rrn[++count]=pos;
	}
	fp1.close();
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
	int pos = fp1.tellg();
	string buff = usn+"|"+name+"|"+sem+"|";
	fp1 << buff << endl;
	rrn[++count]=pos;
}

void search(){
	int rrn_srch,pos;
	cout << "Enter the RRN of the Record to be Found:\n";
	cin >> rrn_srch;
	if(rrn_srch>count || rrn_srch<1){
		cout << "Record does not Exists." << endl;
		return;
	}
	cout << "Record Found!"<<endl;
	pos = rrn[rrn_srch];
	fp1.open("rrnrec.txt",ios::in);
	if(!fp1){
		cout << "File Could not open" << endl;
		return;
	}
	s1.unpack(pos);
	fp1.close();
	s1.output();
}

void student::unpack(int pos){
	fp1.seekg(pos, ios::beg);
	getline(fp1, usn,'|');
	getline(fp1, name,'|');
	getline(fp1, sem,'|');
}

void student::output(){
	cout << "\nName:"<<name<<"\nUSN:"<<usn<<"\nSemester:"<<sem<<endl;
}
