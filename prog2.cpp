#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>

using namespace std;

class student{
	public:
		string usn,name,sem;
		void input();
		void output();
		void pack();
		void unpack();
		void modify();
}s[10],temp;

fstream fp;

void search();

int main(){
	int choice;
	while(1){
		cout << "\n1.Insert Record\n2.Search and Modify\n3.Exit" << endl;
		cin >> choice;
		switch(choice){
			case 1:
				temp.input();
				fp.open("prg2.txt",ios::out|ios::app);
				if(!fp){
					cout << "Error: File Couldn't Open" <<endl;
					return 0;
				}
				temp.pack();
				fp.close();
				break;
				
			case 2:
				search();
				break;
			default:
				exit(0);
				
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
	string buff = usn+"|"+name+"|"+sem+"|";
	if(buff.length() > 45){
		cout << "Data Exceed Record Length" <<endl;
		return;
	}
	while(buff.length() <46)
		buff += '*';
		
	fp << buff << endl;
}

void search(){
	string usn_srch;
	int i=0,srch_flag=-1,modify_flag=-1,count;
	cout << "\nEnter the USN of the Student to be Searched: ";
	cin >> usn_srch;
	fp.open("prg2.txt",ios::in);
	if(!fp){
		cout << "Error: File Couldn't Open" <<endl;
		return;
	}
	while(fp){
		s[i].unpack();
		i++;
	}
	fp.close();
	count=i;
	for(i=0;i<count;i++){
		if(s[i].usn == usn_srch){
			srch_flag=i;
			break;
		}
	}
	if(srch_flag == -1){
		cout << "Record Not Found!" <<endl;
		return;
	}
	cout <<"\nRecord Found!"<<endl;
	s[srch_flag].output();
	cout << "\nDo you wish to modify the Record?\nPress 1. to modify 0. to Exit"<<endl;
	cin >> modify_flag;
	
	if(modify_flag){
		s[srch_flag].modify();
		fp.open("prg2.txt",ios::out);
		if(!fp){
			cout << "Error: File Couldn't Open" <<endl;
			return;
		}
		for(i=0;i<count;i++)
			s[i].pack();
		fp.close();
	}
}

void student::unpack(){
	string seg;
	getline(fp,usn,'|');
	getline(fp,name,'|');
	getline(fp,sem,'|');
	getline(fp,seg);
}

void student::output(){
	cout << "\nName:"<<name<<"\nUSN:"<<usn<<"\nSemester:"<<sem<<endl;
}

void student::modify(){
	int choice;
	while(1){
		cout << "\nEnter the field to modify:\n1.Name\n2.USN\n3.Sem" <<endl;
		cin >> choice;
		switch(choice){
			case 1:
				cout << "Enter New Name:";
				cin>>name;
				break;
			case 2:
				cout << "Enter New USN:";
				cin>>usn;
				break;
			case 3:
				cout << "Enter New Semester:";
				cin>>sem;
				break;
			default:
				return;		
		}
	}
}
