#include "Local_Queue.cpp"
#include "Local_IO.cpp"
#include "Local_hash.cpp"
#include <stdio.h>
#include <cstdlib>
using namespace std;
using std::cout;
using std::cin;

int main()
{
	// Starts with a queue
	Queue* test = new Queue();
	test->getio()->read_all("test1.csv", test);
	test->setl_queue(test->report(test->getl_queue()));
	return 0;
}
