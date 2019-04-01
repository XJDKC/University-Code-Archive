#include<iostream>
#include<algorithm>
#include<cstring>
using namespace std;
const int N=505;
int adj1[N][N]={0},match[N],k=1,m,n,ans;
bool used[N];
void init(){
    ans=0;
    memset(adj1,0,sizeof(adj1));	
    for(int i=1;i<N;i++) { used[i]=false; match[i]=0; }    
    cin>>n>>m;
    for(int i=1,a1,b1;i<=k;i++){    
        cin>>a1>>b1;  //a1:a����    b1:b���� 
        adj1[a1][++adj1[a1][0]]=b1;
    }
}
bool cross(int k){  //k��a���� 
    if(!k) return false;
    for(int i=1;i<=adj1[k][0];i++){    
        int j=adj1[k][i];  //jΪb��� 
        if (!used[j]){  //�ڽӶ���jδʹ��         
            used[j]=true;
            if(!match[j]||cross(match[j])){  //δƥ�������ɹ�             
                match[j]=k;   //j��kƥ��, ע��j���ұ߼��϶����ţ�k����߼��϶��� 
                return true;
            }
        }
    }
    return false;
}
void solve(){
    ans=0;
    for(int i=1;i<=n;i++){    //i:a��� 
        if (cross(i)) ans++;                  
        fill(used,used+N,false);
    }
}
void print(){
    cout<<ans<<endl;
}
int main()
{
    while(cin>>k&&k){
        init();
        solve();
        print();      
    }
    return 0;
}
