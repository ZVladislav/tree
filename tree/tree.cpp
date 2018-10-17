// tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct tnode
{
	int value = 0;
	int weight = 0;
	tnode * left = NULL;
	tnode * right = NULL;
};

void deletetree(tnode **tree)
{
	if ((*tree) != NULL)
	{
		deletetree(&(*tree)->left);
		deletetree(&(*tree)->right);
		delete *tree;
		*tree = NULL;
	}
}
// функция для добавления элемента в дерево
void set_node(tnode **tree, int value, int *weight = NULL, int level = 0)
{
	if (*tree == NULL)
	{
		(*tree) = new tnode;
		(*tree)->value = value;
		if (weight == NULL)
		{
			(*tree)->weight = value;
		}
		else
		{
			(*tree)->weight = *weight + value;
		}
	}
}
void pass(tnode **tree, string key, int value)
{
	tnode ** temptree = tree;
	set_node(&(*temptree), value);

	for (int i = 1; i < (int)key.size(); i++)
	{
		if (key[i] == '1')
		{
			if ((*temptree)->right == NULL)
			{
				set_node(&(*temptree)->right, value, &(*temptree)->weight, i);
			}
			else
			{
				temptree = &(*temptree)->right;
				continue;
			}
		}
		if (key[i] == '0')
		{
			if ((*temptree)->left == NULL)
			{
				set_node(&(*temptree)->left, value, &(*temptree)->weight, i);
			}
			else
			{
				temptree = &(*temptree)->left;
				continue;
			}
		}
	}
}
void print_tree(tnode **tree, int level, char znak = 196)
{
	if ((*tree)!=NULL)
	{	
		
	
		print_tree(&(*tree)->right, level + 1, 218);
		if ((*tree)->right == NULL)
		{
			for (int i = 0; i < level; i++)
			{
				std::cout << "    ";
			}
			std::cout << (char)218 << (char)196 << (char)196 << (char)196;
			std::cout << ":" << std::endl;
		}
		for (int i = 0; i < level - 1; i++)
		{
			std::cout << "    ";
		}
		if(level > 0)
		std::cout  << znak << (char)196 << (char)196 << (char)196;
		std::cout << (*tree)->value <<"(" << (*tree)->weight << ")" << std::endl;
		if ((*tree)->left == NULL)
		{
			for (int i = 0; i < level; i++)
			{
				std::cout << "    ";
			}
			std::cout << (char)192 << (char)196 << (char)196 << (char)196 ;
			std::cout << "*" << std::endl;
		}
		print_tree(&(*tree)->left, level + 1, 192);
	
	}
}
void rec_avg(tnode **tree, int *avgweight, int *count)
{
	if (*tree != NULL)
	{
		if (((*tree)->left == NULL) && ((*tree)->right == NULL))
		{
			*avgweight += (*tree)->weight;
			*count += 1;
		}
		rec_avg(&(*tree)->left, avgweight, count);
		
		rec_avg(&(*tree)->right, avgweight, count);
	}
}

void notrec_avg(tnode *tree, int *avgweight, int *count, int value)
{
	int quantity = value;
	tnode *stack = new tnode[quantity];
	int top; // вершина стека
	top = 0;
	stack[0] = *tree;
	while (top > -1)
	{
		*tree = stack[top];		
		top--;
		if (tree->left == NULL && tree->right == NULL)
		{
			*avgweight += tree->weight;
		}
		if (tree == NULL)
			return;
		else
		{
			stack[top + 1] = *tree->left;
			stack[top + 2] = *tree->right;
			top++;
			top++;
		}
	}


}






int main()
{
	tnode *tree = NULL;
	int * wes = NULL;
	int value = 0;
	int level = 0;
	int count;

	ifstream in("C:\\1\\tree.txt");
	in >> count;
	string str;

	for (int i = 0; i < count; i++)
	{
		in >> str >> value;
		if (level < (int)str.size())
		{
			level = (int)str.size() - 1;
		}
		pass(&tree, str, value);
	}
	
	in.close();

	print_tree(&tree, 0);
	int avgvalue = 0;
	count = 0;
	avg(&tree, &avgvalue, &count);
	cout << avgvalue<< " " << count<< " "<< (float)avgvalue/(float)count<<" HELLO! MY FRIEND"<< endl;
	deletetree(&tree);
}

