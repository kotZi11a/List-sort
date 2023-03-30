#include <fstream>

using namespace std;

struct list
{
	double value;
	list* next;
};

list* go_back(list* num)
{
	list* a = num;
	while (a->next != num)
		a = a->next;
	return a;
}

void push(list* pred, unsigned long int val)
{
	list *number = new list;
	list* p;

	p = pred->next; 
	pred->next = number; 
	number->value = val; 
	number->next = p;

}

void print(ofstream& out, list* number, int num)
{
	list* p;
	p = number;

	do {
		out << p->value << ' '; 
		p = p->next; 
	} while (p != number);
}

void sort_Insertion(list* &number, int num)
{
	list* no_sort = number;

	for (int i = 0; i < num ; i++)
	{
		list* sort = number;

		for (int j = 0; j < i; j++)
		{
			if (no_sort->value < sort->value)
			{
					list* a = go_back(no_sort);
					list* b = go_back(sort);

					a->next = no_sort->next;
					no_sort->next = sort;
					b->next = no_sort;

					if (go_back(sort)->next == number)
						number = no_sort;
					j = i;
					no_sort = a;

			}
			else
			{
				sort = sort->next;
			}
		}
		no_sort = no_sort->next;
	}
}


void pop(list * p)
	{
		if (p->next)
		{
			list* l = p->next;
			p->next = l->next;
			delete l;
		}

	}


int main()
{
	ifstream file_inp("input.txt");
	ofstream file_out("output.txt");
	list* first = new list;
	bool sort;
	file_inp >> sort;

	file_inp >> first->value;
	first->next = first;
	unsigned long int num = 1;
	unsigned long int val;

	while (!file_inp.eof())
	{
		val = 0;
		file_inp >> val;
		push(first, val);
		num++;
	}

	sort_Insertion(first, num);

	file_out << num << ' ';
	print(file_out, first, num);

	do
	{
		pop(first);
	} while (first->next != first);

	file_inp.close();
	file_out.close();
	delete first;
}
