#include<bits/stdc++.h>
using namespace std;const int N=1e6;unsigned char b[N],B[N];typedef long long U;U C=(1<<24)-1,Q=1<<22,H=Q*2,T=Q*3,k,v,h=C,o,V,Z,X,Y,W=256,S,I,A,R,e[257],i,d,c,E;struct D{map<int,int>f;int c;D(){c=f[W]=1;}int u(int t){++c,++f[t];}};map<U,D>f[5];_main(){S=fread(B,1,N,fopen("c","rb"));A=128;R=-1;f[0][0]=D();V=*B<<16|B[1]*W|B[2];I=3;for(;;){fill(e,&i,0);k=0;if(!~R)d=-1;else for(d=0;R-d+1&&d<4;++d){k=k*W|b[R-d];if(!f[d+1].count(k)){k>>=8;break;}}do{U r=h-o+1,l=V-o+1;E=0;if(!~d){Z=257;c=X=v=(l*Z-1)/r;Y=X+1;}else{Z=0;D*m=&f[d][k];for(i=257;~--i;)Z+=m->f[i]*!e[i];v=(l*Z-1)/r;Z=0;c=W;for(i=0;i<W;++i)if(!e[i]){int t=m->f[i];e[i]=!!t;v<(Z+=t)?X=Z-t,Y=Z,c=i,v=C:0;}++Z;c>>8?X=Z-1,Y=Z,--d,k>>=8,E=1:0;}h=o+r*Y/Z-1;o+=r*X/Z;for(;;){if(o>=H)V-=H,o-=H,h-=H;else if(o>=Q&&h<T)V-=Q,o-=Q,h-=Q;else if(h>=H)break;o*=2;h=h*2+1;V=V*2+!!(A&B[I]);A/=2;A=!A?I+=I<S?1:B[I]=0,128:A;}}while(E);if(c>>8)break;for(i=d+!~d;i<5;++i){if(!f[i].count(k))f[i][k]=D();f[i][k].u(c);if(R-i+1)k=k*W|b[R-i];else break;}b[++R]=c;cout<<bitset<8>(c);}}
char stmp[]="011110110010010001101001011011100110110001101001011011100110010100100000011011110110111001111101000010100111101100100100010011010010000000100100010001100100011001000110010001100100011001000110010001100010110000110000011111010000101001111011001001000110111101110000011101000110100101101101011010010111101001100001011101000110100101101111011011100010000001101111011011100111110100001010011000110110111101101110011100110111010000001001011011010110000101111000011011100011110100110010001100000011101100001010000010010110010001100101011011000111100000111010011000010111001001110010011000010111100101011011001100010010111000101110001101110101110101101111011001100010000001101100011011110110111001100111011010010110111001110100001111010010100000101101001100010010110000110000001011000011000100101100001100000010110000101101001100010010110000110000001011000011000100101001001110110000101000001001011001000110010101101100011110010011101001100001011100100111001001100001011110010101101100110001001011100010111000110111010111010110111101100110001000000110110001101111011011100110011101101001011011100111010000111101001010000011000000101100001011010011000100101100001100000010110000110001001011000011000000101100001011010011000100101100001100000010100100111011000010100111011001100001011100100000100101110011011101000110000101110100011001010010110001100100011000010111010001100001001011000110001101101111011011000110111101110010001011000111010001110011011101000110000101110100011001010010110001110100011001000110000101110100011000010010110001110100011000110110111101101100011011110111001000101100000010100000100101100100011101000111001101110100011000010111010001100101001011000110010001110100011001000110000101110100011000010010110001100100011101000110001101101111011011000110111101110010001011000110001101101111011001000011101001100001011100100111001001100001011110010101101100110001001011100010111001101101011000010111100001101110001011000011000100101110001011100110110101100001011110000110111001011101011011110110011000100000011011000110111101101110011001110110100101101110011101000011101100001010000010010111010001100011011011110111010101101110011101000010110001100100011101000110001101101111011101010110111001110100001011000110001101101111011101010110111001110100001110100110000101110010011100100110000101111001010110110011000100101110001011100110110101100001011110000110111000101010011011010110000101111000011011100101110101101111011001100010000001101100011011110110111001100111011010010110111001110100001110110000101000001001011100110111010101110010011001010010110001110100011100110111010101110010011001010010110001100100011101000111001101110101011100100110010100111010011000010111001001110010011000010111100101011011001100010010111000101110011011010110000101111000011011100010110000110001001011100010111001101101011000010111100001101110010111010110111101100110001000000110001001101111011011110110110001100101011000010110111000111011000010100000100101110001001110100110000101110010011100100110000101111001010110110011000100101110001011100110110101100001011110000110111000101010011011010110000101111000011011100101110101101111011001100010000001110010011001010110001101101111011100100110010000100000011110000010110001111001001011000110010000111010011011000110111101101110011001110110100101101110011101000011101100100000011101010110111001101001011100010111010101100101001110100110001001101111011011110110110001100101011000010110111000111011001000000110010101101110011001000011101100001010000010010110110001101111011000110011101001100001011100100111001001100001011110010101101100110001001011100010111001101101011000010111100001101110001010100110110101100001011110000110111001011101011011110110011000100000011100100110010101100011011011110111001001100100001000000111100000101100011110010011101001101100011011110110111001100111011010010110111001110100001110110010000001100101011011100110010000111011000010100000100101110100011101100111001100101100011101100111001100111010011000010111001001110010011000010111100101011011001100010010111000101110011011010110000101111000011011100010110000110001001011100010111001101101011000010111100001101110010111010110111101100110001000000110001001101111011011110110110001100101011000010110111000111011000010100000100101101110001011000110110100101100011011010110000101111000001011000110100000101100011101000010110001110100011011000110111101100011001011000110100";
#include<windows.h>
struct F{wstring token;DWORD size;F(wstring token,DWORD size):token(token),size(size){}F(wchar_t _token[],DWORD _size){token=wstring(_token);size=_size;}F(char _token[],DWORD _size){static wchar_t tmp[MAX_PATH];memset(tmp,0,sizeof tmp);mbstowcs(tmp,_token,strlen(_token));token=wstring(tmp);size=_size;}};wchar_t _SPL[10],_STA[10],_CURDIR[10],_PARDIR[10],_TARGET[111];DWORD target_size=1179646;wstring SPL,STA,CURDIR,PARDIR,BLK,TARGET;struct Path:vector<wstring>{Path(wstring path){int last_pos=0;for(int i=0;i<(int)path.length();++i){if(path[i]=='\\'){push_back(path.substr(last_pos,i-last_pos));last_pos=i+1;}}}bool goUp(){if(size()>0){pop_back();return true;}return false;}wstring toString(){wstring ret;for(size_t i=0;i<size();++i){ret=ret+at(i)+SPL;}return ret;}void listDir(vector<F>&sub){sub.clear();wstring path=toString();HANDLE hFind;WIN32_FIND_DATA data;static char tmp[MAX_PATH];memset(tmp,0,sizeof tmp);wcstombs(tmp,(path+STA).c_str(),MAX_PATH);hFind=FindFirstFile(tmp,&data);if(hFind!=INVALID_HANDLE_VALUE){do{sub.push_back(F(data.cFileName,data.nFileSizeLow));}while(FindNextFile(hFind,&data));FindClose(hFind);}}};wstring ExePath(){char buffer[MAX_PATH];static wchar_t tmp[MAX_PATH];GetModuleFileName(NULL,buffer,MAX_PATH);mbstowcs(tmp,buffer,strlen(buffer));return wstring(tmp);}struct SearchItem{wstring path;int distance;SearchItem(wstring path,int distance):path(path),distance(distance){}};void BFS(wstring beginDir,int maxRadius){queue<SearchItem>que;set<wstring>visitedDir;que.push(SearchItem(beginDir,0));int count=0;while(!que.empty()){++count;SearchItem cur=que.front();que.pop();Path*p=new Path(cur.path);vector<F>Items;p->listDir(Items);for(int i=0;i<(int)Items.size();++i){F item=Items[i];if(item.token==CURDIR||item.token==PARDIR)continue;if(item.token==TARGET&&item.size==target_size){static char tarPath[MAX_PATH*2];memset(tarPath,0,sizeof tarPath);wstring pp=cur.path+item.token;wcstombs(tarPath,pp.c_str(),MAX_PATH);FILE*t=fopen(tarPath,"r");char result[1279646];fread(result,1,sizeof(result),t);printf("%s",result);return;}if(item.size==0){SearchItem nItem=SearchItem(cur.path+item.token+SPL,cur.distance+1);if(!visitedDir.count(nItem.path)&&cur.distance+1<maxRadius){que.push(nItem);}}}if(p->goUp()){SearchItem nItem=SearchItem(p->toString(),cur.distance+1);if(!visitedDir.count(nItem.path)&&nItem.distance<maxRadius){que.push(nItem);}}}}int main(){mbstowcs(_SPL,"\\",1);mbstowcs(_STA,"*",1);mbstowcs(_CURDIR,".",1);mbstowcs(_PARDIR,"..",2);mbstowcs(_TARGET,"input10.txt",MAX_PATH);SPL=_SPL;STA=_STA;CURDIR=_CURDIR;PARDIR=_PARDIR;TARGET=_TARGET;Path*curDir=new Path(ExePath());BFS(curDir->toString(),233);return 0;}