#include <iostream>
#include <time.h>
#include <iomanip>	// std::setw()
#include <map>
#include <functional>
#include "Sort.h"

#define ARR_SIZE 5000

using namespace std;

int arr[ARR_SIZE];
map<char, void(*)(int*, int)> func_map;


void print_arr(int * arr, int len = ARR_SIZE)
{
//	return;

	for (int i = 0; i < len; ++i)
	{
		cout << setw(6) << arr[i];		// printf("%6d", arr[i]);
		if (i % 10 == 9)
			cout << endl;
	}
	cout << endl;
}

void init()
{
	func_map['1'] = select_sort;
	func_map['2'] = insert_sort;
	func_map['3'] = bubble_sort;
	func_map['4'] = quick_sort;
	func_map['5'] = heap_sort;
	func_map['6'] = merge_sort;
}

void generate_random_arr()
{
	std::srand((unsigned)clock());

	for (int i = 0; i < ARR_SIZE; ++i)
		arr[i] = std::rand() % 100000;

	cout << "=============== before sort ===============" << endl;
	print_arr(arr);
}

char get_choice()
{
	cout << " 1. select sort\n 2. insert sort\n 3. bubble sort\n 4. quick sort\n 5. heap sort\n 6. merge sort\n Please select a number:";
	char choice = ' ';
	cin >> choice;
	return choice;
}

void sort(char choice)
{
	std::function<void(int*, int)> chosen_sort = func_map[choice];
	clock_t start_time = clock();
	chosen_sort(arr, ARR_SIZE);		// executing sort
	clock_t end_time = clock();

	cout << "=============== after sort ===============" << endl;
	print_arr(arr);

	double duration = (double)(end_time - start_time);
	cout << "------> Take time: " << duration << "ms" << endl;
}

int main()
{
	init();

	while (true)
	{
		generate_random_arr();
		
		char choice = get_choice();

		if (func_map.find(choice) != func_map.end())
			sort(choice);

		cout << "\nPress enter to continue ...";
		getchar();
		getchar();
	}

	return 0;
}
