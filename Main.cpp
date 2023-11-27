#include <iostream>
#include <fstream>
#include <chrono>
#include <string>
#include <iomanip>

using namespace std;

#define READ_BORDER 50
#define DATA_SIZE 200

string dataUnsorted = "data.txt";
string dataSorted = "sortedData.txt";
string file1 = "_part1";
string file2 = "_part2";
string file3 = "_part3";
string file4 = "_part4";
string file5 = "_part5";
string file6 = "_part6";
string file7 = "_part7";
string file8 = "_part8";
string file9 = "_part9";
string file10 = "_part10";

////////////////////////////////////////////
////////// Механизм сортировки /////////////
////////////////////////////////////////////

static void swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

static int partition(int* arr, int low, int high)
{
	int pivot = arr[high];
	int i = (low - 1);
	for (int j = low; j <= high - 1; j++)
	{
		if (arr[j] <= pivot)
		{
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[high]);
	return (i + 1);
}

static void quickSort(int* arr, int low, int high)
{
	if (low < high)
	{
		int pi = partition(arr, low, high);
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

//////////////////////////////////////////

static void write_file(const string& filename, const int* arr, const int n) //Запись массива в файл
{
	fstream fs;
	fs.open(filename, fstream::out);
	if (fs.is_open())
	{
		cout << "File " << filename << " open to wrote array" << endl;
		for (int i = 0; i < n; i++)
		{
			fs << arr[i] << ' ';
			cout << "Writing file " << filename << " completed: " << setw(3) << round(((static_cast<float>(i) / static_cast<float>(n)) * 10000) / 100) << setw(2) << "%" << endl;
		}
		fs.close();
		cout << "File " << filename << " filled by data. File closed." << endl;
	}
}

static void write_parts(const string& filename, int n) //Запись значения в файл
{
	fstream tempfs;
	tempfs.open(filename, fstream::out | fstream::app);
	tempfs << n << ' ';
	tempfs.close();
}

static void readAndSplit(const string& filename) //Распределение значений между пределами, вызов записи в соответствующий файл
{
	fstream fs;
	fs.open(filename, fstream::in);

	if (fs.is_open())
	{
		int z = 0;
		while (!fs.eof())
		{
			if (fs.eof())
				break;

			cout << "Parsing and writing block " << z << " from " << DATA_SIZE/READ_BORDER << endl;
			for (int i = 0; i < READ_BORDER && !fs.eof(); i++)
			{	
				int temp = 0;
				fs >> temp;
				if (temp > 0 && temp <= 100)
				{
					write_parts(file1, temp);
				}
				if (temp >100  && temp <= 200)
				{
					write_parts(file2, temp);
				}
				if (temp > 200 && temp <= 300)
				{
					write_parts(file3, temp);
				}
				if (temp > 300 && temp <= 400)
				{
					write_parts(file4, temp);
				}
				if (temp > 400 && temp <= 500)
				{
					write_parts(file5, temp);
				}
				if (temp > 500 && temp <= 600)
				{
					write_parts(file6, temp);
				}
				if (temp > 600 && temp <= 700)
				{
					write_parts(file7, temp);
				}
				if (temp > 700 && temp <= 800)
				{
					write_parts(file8, temp);
				}
				if (temp > 800 && temp <= 900)
				{
					write_parts(file9, temp);
				}
				if (temp > 900 && temp <= 1000)
				{
					write_parts(file10, temp);
				}
			}
			z++;
		}
		fs.close();
	}
}

static int genInteger() //генератор случайных чисел
{
	int left_border = 5;
	int range_len = 995;
	return left_border + rand() % range_len;
}

int countData(const string& filename) //Функция вычисляющая количество значений в файле
{
	cout << "Count data for " << filename << "..." << endl;
	fstream tempfs;
	tempfs.open(filename, fstream::in);
	int counter = 0;
	if (tempfs.is_open())
	{
		int temp;
		while (!tempfs.eof())
		{
			tempfs >> temp;
			counter++;
		}
		counter -= 1;
	}
	tempfs.close();
	return counter;
}

void sortAndCombine() //Функция выполняющая сортировку и запись отсортированных данных в файл
{
	cout << "Sort and combine..." << endl;
	for (int i = 1; i <= 10; i++)
	{
		fstream fs;
		string filename = "_part";
		filename = filename.append(std::to_string(i));
		fs.open(filename, fstream::in);
		if (fs.is_open())
		{	
			cout << "Reading data from " << filename << "..." << endl;
			int n = countData(filename);
			int* array = new int[n];
			for (int j = 0; j < n; j++)
			{
				fs >> array[j];
			}
			cout << "Sorting data from " << filename << "..." << endl;
			quickSort(array, 0, n-1);
			cout << "Writing data from " << filename << "..." << endl;
			for (int k = 0; k < n; k++)
			{
				cout << "Writing sorted data from " << filename << " completed: " << setw(3) << round(((static_cast<float>(k) / static_cast<float>(n)) * 10000) / 100) << setw(2) << "%" << endl;
				write_parts(dataSorted, array[k]);
			}
			delete[] array;
		}
		fs.close();
		cout << "Writing sorted data completed. File " << dataSorted << " closed." << endl;
	}
}

void printData(const string& filename) //Функция выводящая содерэимое файла на экран
{
	fstream fs;
	fs.open(filename, fstream::in);
	if (fs.is_open())
	{
		while (!fs.eof())
		{
			int temp;
			fs >> temp;
			cout << temp << " ";
		}
		cout << endl;
	}
}

int main()
{
	//Build data
	
	int* rand_arr = new int[DATA_SIZE];
	srand(time(nullptr));
	cout << "Generating array..." << endl;
	
	for (int i = 0; i < DATA_SIZE; i++)
	{
		rand_arr[i] = genInteger();
	}

	cout << "Array generated." << endl;

	write_file(dataUnsorted, rand_arr, DATA_SIZE);
	cout << "Deleting temporary array..." << endl;
	delete[] rand_arr;

	//Show unsorted:
//	cout << "Data unsorted: " << endl;
//	printData(dataUnsorted);

	//Read and split data

	readAndSplit(dataUnsorted);

	//Sort and join data

	sortAndCombine();

	//Show sorted:
//	cout << "Data sorted: " << endl;
//	printData(dataSorted);

	return 0;
}
