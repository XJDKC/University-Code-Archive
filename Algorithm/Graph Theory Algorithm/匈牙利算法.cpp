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
        cin>>a1>>b1;  //a1:a组编号    b1:b组编号 
        adj1[a1][++adj1[a1][0]]=b1;
    }
}
bool cross(int k){  //k：a组编号 
    if(!k) return false;
    for(int i=1;i<=adj1[k][0];i++){    
        int j=adj1[k][i];  //j为b编号 
        if (!used[j]){  //邻接顶点j未使用         
            used[j]=true;
            if(!match[j]||cross(match[j])){  //未匹配或增广成功             
                match[j]=k;   //j和k匹配, 注意j是右边集合顶点编号，k是左边集合顶点 
                return true;
            }
        }
    }
    return false;
}
void solve(){
    ans=0;
    for(int i=1;i<=n;i++){    //i:a编号 
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
