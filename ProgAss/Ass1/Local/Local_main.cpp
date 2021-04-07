#include "Local_Queue.cpp"
#include "Local_IO.cpp"
#include "Local_hash.cpp"
#include <stdio.h>
#include <cstdlib>
using namespace std;
using std::cout;
using std::cin;
using std::to_string;

int main()
{
	// Starts with a queue:
	Queue* test = new Queue();
	// Test for adding new patients:
	test->getio()->read_all("test1.csv", test);
	// Test for update function:
	test->update(1, 0, 3);
	test->update(1, 1, 7);
	test->update(1, 2, 6);
	test->update(1, 5, 1);
	test->update(1, 6, 59);
	test->update_info(2, 0, "xxx");
	test->update_info(2, 1, "xxx");
	test->update_info(2, 2, "xxx");
	test->update_info(2, 3, "xxx");
	// Test for report:
	test->setl_queue(test->report(test->getl_queue()));
	return 0;
}
