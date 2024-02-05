#include <bits/stdc++.h>

using namespace std;

int n, T, M, N = 1, i, j, v, w, d;
int main()
{
	cin >> n >> T;
	vector<int> S(++n, 1), D = S, P(M = ++T * 2), L(M, T), C = P, V = P, Q[T--];
	while (++j < n)
		cin >> S[j] >> D[j];
	for (Q[L[T] = 0] = {T}; N--; V[v] = 1)
	{
		for (j = -1; Q[i].empty();)
			++i;
		if (!V[v = Q[i].back()])
			while (++j < n)
				if (w = v + S[j], d = i + D[j], w < M & w >= 0 & d < L[w])
					P[w] = j + 1, C[w] = C[v] + 1, Q[L[w] = d].push_back(w), ++N;
		Q[i].pop_back();
	}
	for (cout << C[M -= 2] << '\n'; P[M]; M -= S[P[M] - 1])
		cout << P[M] << ' ';
}

// #include <bits/stdc++.h>
// using namespace std;int n,T,M,N=1,i,j,v,w,d;int
// main(){cin>>n>>T;vector<int>S(++n,1),D=S,P(M=++T*2),L(M,T),C=P,V=P,Q[T--];while(++j<n)cin>>S[j]>>D[j];for(Q[L[T]=0]={T};N--;V[v]=1){for(j=-1;Q[i].empty();)++i;if(!V[v=Q[i].back()])while(++j<n)if(w=v+S[j],d=i+D[j],w<M&w>=0&d<L[w])P[w]=j+1,C[w]=C[v]+1,Q[L[w]=d].push_back(w),++N;Q[i].pop_back();}for(cout<<C[M-=2]<<'\n';P[M];M-=S[P[M]-1])cout<<P[M]<<'
// ';}
