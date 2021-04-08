#include "Local_Queue.cpp"
#include "Local_IO.cpp"
#include "Local_hash.cpp"
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <ctime>
using namespace std;
using std::cout;
using std::cin;
using std::to_string;

int main()
{
cout<<"Welcome to the local hospital registry."<<endl;
cout<<"Please store the new patients in folder Local/new"<<endl;
cout<<"Please store the patients that whose information need to update in folder Local/update"<<endl;
Queue* test = new Queue();
int Order=-1;
string Filename1="new/ExportCSV (  ).csv";
string Filename2="update/ExportCSV (  ).csv";
int Daycounter=0;
string Filecounter =to_string(Daycounter);
while (Order!=0)
{
	cout<<"Today is day "<<Daycounter/2+1;cout<<" ";
	if (Daycounter%2==0)
	{
		cout<<"morning"<<endl<<endl;
	}
	if (Daycounter%2!=0)
	{
		cout<<"afternoon"<<endl<<endl;
	}
	cout<<"Processing new patients:"<<endl;
	Filecounter=to_string(Daycounter++);
	Filename1=Filename1.replace(15,Filecounter.length(),Filecounter);
	test->getio()->read_all(Filename1, test);
	Filename2=Filename2.replace(18,Filecounter.length(),Filecounter);
	test->getio()->read_update(Filename2, test);
	test->setl_queue(test->report(test->getl_queue()));
	cout<<"The file sent to the center has been packed into file named Submit.csv"<<endl<<endl;
	cout<<"If you want to finish the Local registry program, enter 0,else enter other number"<<endl<<endl<<endl;
	cin>>Order;
}
cout<<"Down for the local registry system"<<endl;
return 0;
}
