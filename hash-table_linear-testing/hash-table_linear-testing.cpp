#include <iostream>
#include <fstream>
using namespace std;
typedef char T; // тип элементов
typedef int hashTableIndex;// индекс в хеш-таблице
int hashTableSize;
T* hashTable;
bool* used;
hashTableIndex myhash(T data);
void insertData(T data);
void deleteData(T data);
bool findData(T data);
int dist(hashTableIndex a, hashTableIndex b);

//E A S Y Q U T I O N
int alf(char n)
{
	char a[] = { "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	for (int i = 0; i < 26; i++)
	{
		if (a[i] == n)
			return i + 1;
	}
}
int main()
{
	setlocale(LC_ALL, "ru");
	int i, maxnum;
	char* a;
	cout << "Введите количество элементов maxnum : ";
	cin >> maxnum;
	cout << "Введите размер хеш-таблицы hashTableSize : ";
	cin >> hashTableSize;
	a = new char[maxnum];
	hashTable = new T[hashTableSize];
	used = new bool[hashTableSize];
	for (i = 0; i < hashTableSize; i++) {
		hashTable[i] = 0;
		used[i] = false;
	}
	// генерация массива
	for (i = 0; i < maxnum; i++)
		cin >> a[i];
	// заполнение хеш-таблицы элементами массива
	for (i = 0; i < maxnum; i++)
		insertData(a[i]);
	// поиск элементов массива по хеш-таблице
	for (i = maxnum - 1; i >= 0; i--)
		findData(a[i]);
	// вывод элементов массива в файл List.txt
	ofstream out("List.txt");
	for (i = 0; i < maxnum; i++) {
		out << a[i];
		if (i < maxnum - 1) out << "\t";
	}
	out.close();
	// сохранение хеш-таблицы в файл HashTable.txt
	out.open("HashTable.txt");
	out << "Индекс : Состояние  : Значение" << endl;
	for (i = 0; i < hashTableSize; i++)
	{
		out << i << " : " << used[i] << " : " <<
			hashTable[i] << endl;
	}
	for (i = 0; i < hashTableSize; i++)
		cout << hashTable[i] << endl;
	out.close();
	cout << endl << "===" << endl;
	// очистка хеш-таблицы
	for (i = maxnum - 1; i >= 0; i--) {
		deleteData(a[i]);
	}
	for (i = 0; i < hashTableSize; i++)
		cout << hashTable[i] << endl;

	return 0;
}
// хеш-функция размещения величины
hashTableIndex myhash(T data) {
	return (15 * alf(data) % hashTableSize);
}
//функция поиска местоположения и вставки величины в таблицу
void insertData(T data)
{
	hashTableIndex bucket;
	bucket = myhash(data);
	while (used[bucket] && hashTable[bucket] != data)
		bucket = (bucket + 1) % hashTableSize;
	if (!used[bucket]) {
		used[bucket] = true;
		hashTable[bucket] = data;
	}
}
// функция поиска величины, равной data
bool findData(T data) {
	hashTableIndex bucket;
	bucket = myhash(data);
	while (used[bucket] && hashTable[bucket] != data)
		bucket = (bucket + 1) % hashTableSize;
	return used[bucket] && hashTable[bucket] == data;
}
// функция удаления величины из таблицы
void deleteData(T data) {
	int bucket, gap;
	bucket = myhash(data);
	while (used[bucket] && hashTable[bucket] != data)
		bucket = (bucket + 1) % hashTableSize;
	if (used[bucket] && hashTable[bucket] == data) {
		used[bucket] = false;
		gap = bucket;
		bucket = (bucket + 1) % hashTableSize;
		while (used[bucket]) {
			if (bucket == myhash(hashTable[bucket]))
				bucket = (bucket + 1) % hashTableSize;
			else if (dist(myhash(hashTable[bucket]), bucket) <
				dist(gap, bucket))
				bucket = (bucket + 1) % hashTableSize;
			else {
				used[gap] = true;
				hashTable[gap] = hashTable[bucket];
				used[bucket] = false;
				gap = bucket;
				bucket++;
			}
		}
	}
}
// функция вычисления расстояние от a до b
//(по часовой стрелке, слева направо)
int dist(hashTableIndex a, hashTableIndex b) {
	return (b - a + hashTableSize) % hashTableSize;
}