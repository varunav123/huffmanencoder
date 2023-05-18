#include<iostream>
#include<fstream>
#include<sstream>
#include<map>
#include<string>
#include<unordered_set>
#include<vector>
using namespace std;

struct node 
{
	char name;
	string code;
	node* parent=NULL;
	node* left=NULL;
	node* right=NULL;
	string dir;
	int fre;
};

node add(node& a, node& b,node& c)
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

void huffmandecoder(string& s, multimap<int, char> h)
{
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
	
		
			for (int i1 = 0; i1 < s.size();i1++)
			{
				for (int i = n-1; i >-1; i--)
				{
					
						if (s.substr(i1, t[i].code.length()) == t[i].code)
						{
							string decode;
							decode.assign(1, t[i].name);
							s.replace(i1, t[i].code.length(), decode);
							break;
						}
					
				}
			}
		
	
	ofstream fileout;
	fileout.open("fileout.txt");
	fileout << s;

}


int main()
{
	string s1="";
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
	for (int i = 0; i < s.size() ; i++)
	{
		c.insert(s[i]);
	}
	int n = c.size();
	/*cout << n << '\n';*/
	int* f=new int[n];
	int k = 0;
	unordered_set<char>::iterator itr;

	for (itr = c.begin(); itr != c.end(); itr++)
	{	
		int j = 0;
		for (int i = 0; i < s.size() ; i++)
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
	for (int i=0; i<n; i++)
	{
		bt.insert(btree_pair(t[i].fre,&t[i]));
	}
	
	for (int i = 0; i < n - 1; i++)
	{
		multimap<int,node*>::iterator bst;
		bst = bt.begin();
		if (bst != bt.end())
		{
			
				
				node* x = (bst->second);
				bt.erase(bst);
				advance(bst, 1);
				node* y = (bst->second);
				bt.erase(bst);
				t[i+n] = add(*x,*y,t[i+n]);
				bt.insert(btree_pair(t[i+n].fre, &t[i + n]));
			
			
		}

	}



	for (int i = 2*n-2; i >-1; i--)
	{
		encode(t[i]);
	}
	for (int i = 0; i < s.size(); i++)
	{
		for (int p = 0; p < 2 * n - 1; p++)
		{
			if (s[i] == t[p].name)
			{
				fileout1 << t[p].code;
				s1 = s1 + t[p].code;
			}
		}
	}
	/*for (int i = 0; i <n; i++)
	{
		cout << t[i].code << '\n';
	}
	fileout1.close();*/

	
	huffmandecoder(s1, h);




}
