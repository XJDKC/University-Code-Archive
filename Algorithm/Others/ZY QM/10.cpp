#include<stdio.h>

int a[15],b[15];

int pow(int num,int p)
{
	int i=1,m=1;
	for (;i<=p;i++)
	{
		m*=num;
	}
	return m;
}

void sort(int x,int y)
{
	int temp,i,j;
	for (i=x;i<y;i++)
    	for (j=y;j>i;j--)
    	{
    		if (a[j]<a[i]) 
    		{
    			temp=a[i];
    			a[i]=a[j];
    			a[j]=temp;
    		}
    	}
}
int main()
{
	int t,n,i,j,k,temp,ans=0x7fffffff,minn=10,cal=0;
	scanf("%d",&t);
	while (t--)
    {
    	ans=0x7fffffff,minn=10;
    	scanf("%d",&n);
    	for (i=1;i<=n;i++)
    	scanf("%d",&a[i]);
    	sort(1,n);
    	i=1;
    	while (!a[i]) i++;
    	if (n%2==1)
    	{
    		n=n/2+1;
    		ans=a[i]*pow(10,n-1);
    	    temp=a[i];
    	    a[i]=a[2*n-1];
    	    a[2*n-1]=temp;
    	    sort(1,2*n-2);
    	    a[0]=n;
    	    for (i=1;i<n;i++)
    	    ans-=(a[2*n-1-i]-a[i])*pow(10,--a[0]-1);
    	    printf("%d\n",ans);
    	}
    	else 
    	{
    		for (j=i;j<n;j++)
			if (minn>a[j+1]-a[j]) minn=a[j+1]-a[j];
			n/=2; 
			for (;i<2*n;i++)
			{
				if (a[i+1]-a[i]==minn) 
				{
					cal=(a[i+1]-a[i])*pow(10,n-1);
					for (j=1,k=1;j<=2*n&&k<=2*n;j++,k++)
					if (k!=i) b[j]=a[k];
					else k+=1,j--;
					b[0]=n;
					for (j=1;j<n;j++)
    	            cal-=(b[2*n-1-j]-b[j])*pow(10,--b[0]-1);
    	            if (cal<ans) ans=cal;
				}
			} 
			printf("%d\n",ans);
    	}
    } 
} 
