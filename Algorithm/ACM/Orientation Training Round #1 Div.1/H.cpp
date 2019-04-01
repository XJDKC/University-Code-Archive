#include<iostream>
#include<cstdio>
using namespace std;
struct tree
{
	int data;
	tree *left;
	tree *right;
};
tree *root;
void dealinput(tree **T)
{
	bool fu=false;
	char c;
	int temp,l=0,r=0;
	while (cin>>c)
	{
		if (isdigit(c))
		{
			temp=c-'0';
			while (cin>>c&&isdigit(c))
			{
				temp=temp*10+c-'0';
			}
			(*T)=new(tree);
			(*T)->data=fu?-temp:temp;
			(*T)->left = NULL;
			(*T)->right = NULL;
			if (c == '(') ungetc(c, stdin);
			else if (c == ')') r++;
			dealinput(&(*T)->left);
			dealinput(&(*T)->right);
		}
		else if (c=='(')
		{
			l++;
		}
		else if (c==')')
		{
			r++;
		}
		else if (c=='-')
		{
			fu = true;
		}
		if (l==r&&l)
		{
			break;
		}
	}
}

bool find(int n,int len,tree *T)
{
	if (T&&!T->left&&!T->right)
	{
		return (len+T->data==n);
	}
	else if (T)
	{
		return (find(n, len + T->data, T->left)||find(n, len + T->data, T->right));
	}
	else
	{
		return false;
	}
}

int main()
{
	int n;
	bool mark = false;
	while (scanf("%d",&n)!=EOF)
	{
		mark = false;
		root = NULL;
		dealinput(&root);
		if (root!=NULL)
			mark = find(n,0,root);
		if (mark == true) cout << "yes" << endl;
		else cout << "no" << endl;
	}
	return 0;
}