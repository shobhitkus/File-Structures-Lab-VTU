#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

int main(){
	char s1[25];
	fstream f1,f2;
	int i=0,j=0,x=0,c=0,ch=0;
	char fname1[25],fname2[25];
	cout << "1:For std i/o\n2.For file i/o\n";
	cout << "Enter your choice :\n";
	cin >> ch;
	switch(ch){
		case 1:
            cout << "Enter number of names :";
            cin >> c;
			for(j = 1;j <= c; j++){
				cout << "Enter name :" << j << ":";
				cin >> s1;
				x = strlen(s1);
				cout << "Reversed name :" << j << ":";
				for(i = x-1; i >= 0; i--)
					cout << s1[i];
				cout << endl;
			}
			break;
		case 2:
            cout << "Enter datafile name :";
			cin >> fname1;
			cout << "Enter reverse datafile name :";
			cin >> fname2;
			f1.open(fname1, ios::in);
			f2.open(fname2, ios::out);
            if(!f1){
                cerr << "File doesnot exist: " << fname1;
                return -1;
            }
            if(!f2){
                cerr << "File doesnot exist: " << fname2;
                return -1;
            }
			while(1){
				f1.getline(s1,25);
				if(f1.fail())
					break;
				x = strlen(s1);
				for(i = x-1; i >= 0; i--)
                    f2 << s1[i];
				f2 << endl;
			}
            f1.close();
            f2.close();
            break;
    }
    return 0;
}
