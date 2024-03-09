#include <bits/stdc++.h>

using namespace std;

int par[400000];
int fre[400000];
int N, L;

int find(int a){
	if(a == par[a]) return a;
	return (par[a] = find(par[a]));
}

void merge(int a, int b){
	b = find(b);
	a = find(a);
	if(a == b){
		fre[a] = fre[b] = -1;
		return;
	}
	par[b] = a;
	
}

int main()
{
	cin >> N >> L;
	for(int i = 0; i < L; i++) par[i] = fre[i] = i;

	for(int i = 0; i < N; i++){
		int a, b;
		cin >> a >> b;
		a--; b--;
		if(par[a] == a && fre[a] != -1){
			cout << "LADICA\n";
			merge(b, a);
			continue;
		}
		if(par[b] == b && fre[b] != -1){
			cout << "LADICA\n";
			merge(a, b);
			continue;
		}
		if(fre[find(a)] != -1){
			cout << "LADICA\n";
			a = find(a);
			merge(b, a);
			continue;
		}
		if(fre[find(b)] != -1){
			cout << "LADICA\n";
			b = find(b);
			merge(a, b);
			continue;
		}
		cout << "SMECE\n";
	}

}