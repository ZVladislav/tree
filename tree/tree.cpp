// tree.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// это изменение)

#include "pch.h"
//структура, описывающая узел дерева
struct tnode
{
	int value = 0;			
	int weight = 0;			//вес ветви
	tnode * left = NULL;	//левый потомок
	tnode * right = NULL;	//правый потомок
};
//удаление дерева
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
//вспомогательная функция для добавления элемента в дерево
//вызывается из функции pass
void set_node(tnode **tree, int value, int *weight = NULL)
{
	if (*tree == NULL)
	{
		(*tree) = new tnode;
		(*tree)->value = value;
		//добовление веса всей ветви в узел 
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
//функция прохода по дереву
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
				set_node(&(*temptree)->right, value, &(*temptree)->weight);
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
				set_node(&(*temptree)->left, value, &(*temptree)->weight);
			}
			else
			{
				temptree = &(*temptree)->left;
				continue;
			}
		}
	}
}
//печать дерева
void print_tree(tnode **tree, int level, char znak = 196)
{
	if ((*tree)!=NULL)
	{	
		
	
		print_tree(&(*tree)->right, level + 1, 218);
		if ((*tree)->right == NULL)
		{
			for (int i = 0; i < level; i++)
			{
				cout << "    ";
			}
			cout << (char)218 << (char)196 << (char)196 << (char)196;
			cout << ":" << endl;
		}
		for (int i = 0; i < level - 1; i++)
		{
			cout << "    ";
		}
		if(level > 0)
		cout  << znak << (char)196 << (char)196 << (char)196;
		cout << (*tree)->value  << endl;
		if ((*tree)->left == NULL)
		{
			for (int i = 0; i < level; i++)
			{
				cout << "    ";
			}
			cout << (char)192 << (char)196 << (char)196 << (char)196 ;
			cout << "*" << endl;
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

void notrec_avg(tnode **tree, int *avgweight, int *count, int value)
{
	int quantity = value;
	stack<tnode**> st;
	st.push(tree);
	tnode **temp;
	while (!st.empty())
	{
		temp = st.top();
		st.pop();
		if (((*temp)->right == NULL && (*temp)->left == NULL))
		{
			*avgweight += (*temp)->weight;
			*count += 1;
			
		}
		if ((*temp)->right != NULL)
		{
			st.push(&(*temp)->right);
		}
		if ((*temp)->left != NULL)
		{
			st.push(&(*temp)->left);
		}
	}
}
int main()
{
	tnode *tree = NULL;
	int * wes = NULL;
	int value = 0;
	int level = 0;
	int quantity= 0;

	ifstream in("C:\\1\\tree.txt");
	string str;

	while (!in.eof())
	{
		in >> str >> value;
		if (level < (int)str.size())
		{
			level = (int)str.size() - 1;
		}
		pass(&tree, str, value);
		quantity++;
	}
	
	in.close();

	print_tree(&tree, 0);
	int avgvalue = 0;
	int count = 0;
	//rec_avg(&tree, &avgvalue, &count);
	notrec_avg(&tree, &avgvalue, &count, quantity);
	cout << avgvalue<< " " << count<< " "<< (float)avgvalue/(float)count<< endl;
	deletetree(&tree);
}

