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

struct sec_index{
	string usn;
	string name;
	int addr;
}i2[100],found[20];
int count,find_count;

fstream fp;
int indexnums[20];

void create_index();
void sort_index();
void search();
void lin_search(string);
void del();

int main(){
	int choice;
	fp.open("prg6.txt",ios::out|ios::app);
	fp.close();
	create_index();
	while(1){
		cout << "1.Add to Records\n2.To search for a Record\n3.To delete a Record\n4.Exit\nEnter Choice:";
		cin >> choice;
		switch(choice){
			case 1:
				s1.input();
				fp.open("prg6.txt",ios::out|ios::app);
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
	string seg,usnbuff,namebuff;
	count=0;
	fp.open("prg6.txt",ios::in);
	if(!fp){
		cout << "File Could not open" << endl;
		return;
	}
	while(fp){
		usnbuff.erase();
		namebuff.erase();
		pos = fp.tellg();
		getline(fp,usnbuff,'|');
		getline(fp,namebuff,'|');
		getline(fp,seg);
		if(usnbuff[0] == '*' || usnbuff.length() == 0 || namebuff.length()==0)
			continue;
		count++;
		i2[count].usn=usnbuff;
		i2[count].name=namebuff;
		i2[count].addr=pos;
	}
	fp.close();
	sort_index();
}

void sort_index(){
	struct sec_index temp;
	for(int i=0;i<count;i++){
		for(int j=i+1;j<count;j++)
			if(i2[i].name > i2[j].name){
				temp.usn = i2[i].usn;
				temp.name = i2[i].name;
				temp.addr = i2[i].addr;
				
				i2[i].usn=i2[j].usn;
				i2[i].name=i2[j].name;
				i2[i].addr=i2[j].addr;
				
				i2[j].usn=temp.usn;
				i2[j].name=temp.name;
				i2[j].addr=temp.addr;
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
	i2[count].usn=usn;
	i2[count].name=name;
	i2[count].addr=pos;
	sort_index();
}

void search(){
	string name_srch,buff;
	int ch;
	cout << "Enter Name of the Student to be Searched: ";
	cin >> name_srch;
	lin_search(name_srch);
	if(find_count == 0){
		cout << "Record Not Found!" <<endl;
		return;
	}
	if(find_count == 1){
		cout << "\n1 Record Found" << endl;
		ch=0;
	}
	if(find_count>1){
		cout << "\nMultiple Record Found!"<<endl;
		for(int i=0;i<find_count;i++)
			cout << i << ".USN= "<<found[i].usn<<endl;
		cout << "\nEnter Choice:";
		cin>>ch;
		if(ch>find_count){
			cout << "\nInvalid Range";
			return;
		}
	}
	fp.open("prg6.txt",ios::in);
	if(!fp){
		cout << "File Could not open" << endl;
		return;
	}
	cout << "USN|Name|Sem"<<endl;
	fp.seekg(found[ch].addr,ios::beg);
	getline(fp,buff);
	cout << buff << endl;
	fp.close();
}

void lin_search(string name_srch){
	find_count=0;
	int j=0;
	for(int i=0;i<=count;i++){
		if(i2[i].name == name_srch){
			indexnums[j++]=i;
			found[find_count].usn=i2[i].usn;
			found[find_count].name=i2[i].name;
			found[find_count].addr=i2[i].addr;
			find_count++;
		}
	}
}


void del(){
	string name_srch;
	int ch;
	cout << "Enter the Name of the Student to be Deleted:";
	cin >> name_srch;
	lin_search(name_srch);
	if(find_count == 0){
		cout << "Record Not Found!"<<endl;
		return;
	}
	if(find_count == 1){
		cout << "1 Record Found\n"<<endl;
		ch=0;
	}
	if(find_count > 1){
		cout << "Multiple Record Found\n"<<endl;
		for(int i=0;i<find_count;i++)
			cout<<i<<". "<<found[i].usn<<endl;
		cout << "\nEnter Choice:";
		cin >> ch;
		if(ch>find_count){
			cout << "\nInvalid Range\n";
			return;
		}
	}
	cout << "Record Found and Deleted!" << endl;
	fp.open("prg6.txt",ios::out|ios::in);
	if(!fp){
		cout << "File Could not open" << endl;
		return;
	}
	fp.seekp(found[ch].addr, ios::beg);
	fp.put('*');
	fp.close();
	
	for(int i=indexnums[ch];i<count;i++){
		i2[i].usn = i2[i+1].usn;
		i2[i].name = i2[i+1].name;
		i2[i].addr = i2[i+1].addr;
	}
	count--;
}
