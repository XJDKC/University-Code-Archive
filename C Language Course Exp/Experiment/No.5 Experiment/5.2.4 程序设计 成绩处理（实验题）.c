#include<stdio.h>
struct student
{
    char name[36];
	int grade;	
}f[106];
int comp(struct student x,struct student y);
void isort(struct student f[],int n);
int binary(struct student f[],int x,int left,int right);
int main()
{
	int n,m,i,no,ans;
	scanf("%d",&n);
	for (i=0;i<n;i++)
	    scanf("%s%d",f[i].name,&f[i].grade);
	isort(f,n);
	for (i=0;i<n;i++)
	    printf("%-20s %d\n",f[i].name,f[i].grade);
	printf("\n");
	scanf("%d",&m);
	for (i=0;i<m;i++)
	{
		scanf("%d",&no);
		ans=binary(f,no,0,n-1);
		if (ans==-1) printf("Not found!\n");
		else printf("%-20s %d\n",f[ans].name,f[ans].grade);
	}
	return 0;
}
int comp(struct student x,struct student y)
{
	return x.grade>y.grade;
}
void isort(struct student f[],int n)
{
	struct student temp;
	int i,j;
	for (i=0;i<n;i++)
	    for (j=n-1;j>i;j--)
	    {
	    	if (comp(f[j],f[j-1])) temp=f[j],f[j]=f[j-1],f[j-1]=temp;
		}
}
int binary(struct student f[],int x,int left,int right)
{
	int mid;
	while (left<=right)
	{
		mid=left+(right-left)/2;
		if (f[mid].grade>x) return binary(f,x,mid+1,right);
		else return binary(f,x,left,mid-1);
	}
	if (f[left].grade==x) return left;
	else return -1;
}
