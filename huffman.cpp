#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<unordered_set>

using namespace std;
struct node
{
	char name;
	string code;
	node* parent = NULL;
	node* left = NULL;
	node* right = NULL;
	string dir;
	int fre;
};


node add(node& a, node& b, node& c)
{
	c.left = &a;
	a.dir = "0";
	c.right = &b;
	b.dir = "1";
	a.parent = &c;
	b.parent = &c;
	c.fre = a.fre + b.fre;
	c.name = a.name + b.name;
	return c;
}
void encode(node& a)
{
	if (a.parent == NULL)
	{
		a.code = "";
		a.dir = "";
		return;
	}
	else if ((a.parent)->parent == NULL)
	{
		a.code = a.dir;
		return;
	}
	else
	{
		a.code = a.parent->code + a.dir;
	}
}
node* traversal(char x, node* y)
{

	if (x == '0')
	{
		return y->left;
	}
	else if (x == '1')
	{
		return y->right;
	}
	return NULL;
}

void huffmandecoder(string& s, multimap<int, char> h)
{
	ofstream fileout;
	fileout.open("fileout.txt");
	int n = h.size();
	node* t = new node[2 * n - 1];
	auto mnp = h.begin();
	for (int i = 0; i < n; i++)
	{

		if (mnp != h.end())
		{
			t[i].fre = mnp->first;
			t[i].name = mnp->second;
			mnp++;
		}

	}

	multimap<int, node*> bt;
	typedef pair <int, node*> btree_pair;
	for (int i = 0; i < n; i++)
	{
		bt.insert(btree_pair(t[i].fre, &t[i]));
	}

	for (int i = 0; i < n - 1; i++)
	{
		multimap<int, node*>::iterator bst;
		bst = bt.begin();
		if (bst != bt.end())
		{


			node* x = (bst->second);
			bt.erase(bst);
			advance(bst, 1);
			node* y = (bst->second);
			bt.erase(bst);
			t[i + n] = add(*x, *y, t[i + n]);
			bt.insert(btree_pair(t[i + n].fre, &t[i + n]));


		}

	}



	for (int i = 2 * n - 2; i > -1; i--)
	{
		encode(t[i]);
	}
	for (int i = 0; i < s.size()+1; )
	{
		node* x = traversal(s[i], &t[2 * n - 2]);
		int j = 1;
		for (; i + j < s.size()+1; j++)
		{	
			if (x->left == NULL && x->right == NULL)
			{
				string decode;
				decode.assign(1, x->name);
				fileout << decode;
				break;
			}
			
			x = traversal(s[i + j], x);
		}
		i = i + j ;
	}



	fileout.close();
}


int main()
{
	string s1 = "";
	ifstream file;
	file.open("file.txt");
	string s;
	stringstream ss;
	ss << file.rdbuf();
	s = ss.str();
	file.close();
	ofstream fileout1;
	fileout1.open("fileout1.txt");
	ofstream fileout2;
	fileout2.open("fileout2.txt");
	unordered_set<char> c;
	for (int i = 0; i < s.size(); i++)
	{
		c.insert(s[i]);
	}
	int n = c.size();
	/*cout << n << '\n';*/
	int* f = new int[n];
	int k = 0;
	unordered_set<char>::iterator itr;

	for (itr = c.begin(); itr != c.end(); itr++)
	{
		int j = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (*itr == s[i])
			{
				j++;
			}
		}
		f[k] = j;
		k++;
	}


	multimap<int, char> h;
	unordered_set<char>::iterator itr2;
	typedef pair <int, char> diff_pair;
	int l = 0;
	for (itr2 = c.begin(); itr2 != c.end(); itr2++)
	{

		h.insert(diff_pair(f[l], *itr2));
		l++;
	}


	for (auto i = h.begin(); i != h.end(); i++)
	{
		fileout2 << i->first << ' ';

	}
	fileout2 << '\n';
	for (auto i = h.begin(); i != h.end(); i++)
	{
		fileout2 << i->second << ' ';

	}
	fileout2.close();

	node* t = new node[2 * n - 1];
	auto mnp = h.begin();
	for (int i = 0; i < n; i++)
	{

		if (mnp != h.end())
		{
			t[i].fre = mnp->first;
			t[i].name = mnp->second;
			mnp++;
		}

	}

	multimap<int, node*> bt;
	typedef pair <int, node*> btree_pair;
	for (int i = 0; i < n; i++)
	{
		bt.insert(btree_pair(t[i].fre, &t[i]));
	}

	for (int i = 0; i < n - 1; i++)
	{
		multimap<int, node*>::iterator bst;
		bst = bt.begin();
		if (bst != bt.end())
		{


			node* x = (bst->second);
			bt.erase(bst);
			advance(bst, 1);
			node* y = (bst->second);
			bt.erase(bst);
			t[i + n] = add(*x, *y, t[i + n]);
			bt.insert(btree_pair(t[i + n].fre, &t[i + n]));


		}

	}



	for (int i = 2 * n - 2; i > -1; i--)
	{
		encode(t[i]);
	}
	for (int i = 0; i < s.size(); i++)
	{
		for (int p = 0; p < 2 * n - 1; p++)
		{
			if (s[i] == t[p].name)
			{
				s1 = s1 + t[p].code;
				break;
			}
		}
	}
	for (int i = 0; i <n; i++)
	{
		cout << t[i].code << '\n';
	}
	
	fileout1 << s1;
	fileout1.close();
	huffmandecoder(s1, h);
}
