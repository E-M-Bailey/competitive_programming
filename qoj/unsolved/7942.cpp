#include <bits/stdc++.h>

using namespace std;

#define rep(i, a, b) for (int i = a; i < b; i++)
#define sz(C)		 int(size(C))

int arr[200000];
int res[200000];
int run[200000];
vector<int> z, f, m;

int N, K;

bool work(int M){
	f.clear();
	z.clear();
	m.clear();
	for(int i = 0; i < K; i++){
		z.push_back(i);
		run[i] = 0;
	}
	for(int i = 0; i < N; i++){
		//cerr << f.size() << " " << z.size() << " " << m.size() << endl;
		if(arr[i] == 1){
			int x;
			if(z.size() != 0){
				x = z.back();
				z.pop_back();
			}
			else if(m.size() != 0){
				x = m.back();
				m.pop_back();
			}
			else{
				return false;
			}
			res[i] = x;
			run[x]++;
			//cout << x << " " << run[x] << endl;
			if(run[x] == M){
				f.push_back(x);
			}
			else{
				m.push_back(x);
			}
		}
		else{
			int x;
			if(f.size() != 0){
				x = f.back();
				f.pop_back();
			}
			else if(m.size() != 0){
				x = m.back();
				m.pop_back();
			}
			else{
				x = z.back();
				z.pop_back();
			}
			run[x] = max(0, run[x]-1);
			res[i] = x;
			if(run[x] == 0){
				z.push_back(x);
			}
			else{
				m.push_back(x);
			}
		}
		
	}
	return true;
}

void process(){
	cin >> N >> K;
	for(int i = 0; i < N; i++){
		cin >> arr[i];
	}
	int b = 0;
	int e = 300000;
	while(e-b > 1){
		int m = (b+e)/2;
		if(work(m)){
			e = m;
		}
		else{
			b = m;
		}
	}
	//cout << e << endl;
	work(e);
	for(int i = 0; i < N; i++){
		cout << (res[i]+1) << " ";
	}
	cout << endl;


}

int main(int argc, char const *argv[])
{
	int t;
	cin >> t;
	for(int i = 0; i < t; i++) process();
}
