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

int main()
{
cout<<"Welcome to the local hospital registry."<<endl;
cout<<"Please store the new patients in folder Local/new"<<endl;
cout<<"Please store the patients that whose information need to update in folder Local/update"<<endl;
Queue* test = new Queue();
int Order=-1;
string Filename="new/ExportCSV (0).csv";
int Daycounter=0;
string Filecounter1 =to_string(Daycounter);
string Filecounter2 =to_string(Daycounter);
while (Order!=0)
{
	cout<<"Today is day "<<Daycounter/2+1;cout<<" ";
	if (Daycounter%2==0)
	{
		cout<<"morning"<<endl;
	}
	if (Daycounter%2!=0)
	{
		cout<<"afternoon"<<endl;
	}
	cout<<"Processing new patients:"<<endl;
	Filecounter1=to_string(Daycounter++);
	Filecounter2=Filecounter1;
	Filename=Filename.replace(15,1,Filecounter1);
	cout<<Filename<<endl;
	test->getio()->read_all(Filename, test);
	test->setl_queue(test->report(test->getl_queue()));
	cout<<"The file sent to the center has been packed into file named submit.csv";
	cout<<"If you want to finish the Local registry program, enter 1,else enter other number"<<endl;
	cin>>Order;
}
return 0;
}
