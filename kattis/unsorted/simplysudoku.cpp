#include <bits/stdc++.h>

using namespace std;

int grid[9][9];

bool canDo(int r, int c, int d){
	if(grid[r][c] != 0) return false;
	int br = 3*(r/3);
	int bc = 3*(c/3);
	for(int i = 0; i < 9; i++){
		if(grid[i][c] == d) return false;
		if(grid[r][i] == d) return false;
		//if(r == 2 && c == 0) cout << r << " " << c << " " << d << " " << grid[0][0] << endl;
		if(grid[br+i/3][bc+i%3] == d) return false;
	}
	//(r == 2 && c == 0) cout << r << " " << c << " " << d << endl;
	return true;
}

int only(int r, int c){
	int f = 0;
	int res = -1;
	for(int d = 1; d <= 9; d++){
		if(canDo(r, c, d)){
			f++;
			res = d;
		}
	}
	if(f == 1) return res;
	return -1;
}

int singleRow(int r, int d){
	int f = 0;
	int res = -1;
	for(int c = 0; c < 9; c++){
		if(canDo(r, c, d)){
			f++;
			res = c;
		}
	}
	if(f == 1) return res;
	return -1;
}

int singleBox(int b, int d){
	int f = 0;
	int res = -1;
	//3*(e/3)+3*(bb/3)][3*(e%3)+3*(bb%3)
	for(int bb = 0; bb < 9; bb++){
		if(canDo(3*(b/3)+(bb/3), 3*(b%3)+(bb%3), d)){
			f++;
			res = bb;
		}
	}
	if(f == 1) return res;
	return -1;
}

int singleCol(int c, int d){
	int f = 0;
	int res = -1;
	for(int r = 0; r < 9; r++){
		if(canDo(r, c, d)){
			f++;
			res = r;
		}
	}
	if(f == 1) return res;
	return -1;
}

int main(int argc, const char* argv[])
{
	if (argc > 1)
	{
		ignore = freopen(argv[1], "r", stdin);
		ignore = freopen(argv[2], "w", stdout);
	}
	//int grid[9][9];

	for(int i = 0; i < 9; i++) for(int e = 0; e < 9; e++) cin >> grid[i][e];

	for(int i = 0; i < 81; i++){
		//cout << i << endl;
		for(int r = 0; r < 9; r++){
			for(int c = 0; c < 9; c++){
				if(grid[r][c] != 0) continue;
				int o = only(r, c);
				if(o != -1){
					grid[r][c] = o;
					goto here;
				}
			}
		}
		//return 0;
		for(int e = 0; e < 9; e++){
			for(int d = 1; d <= 9; d++){
				int c = singleRow(e, d);
				if(c != -1){
					grid[e][c] = d;
					goto here;
				}
				int r = singleCol(e, d);
				if(r != -1){
					grid[r][e] = d;
					goto here;
				}
				int bb = singleBox(e, d);
				if(bb != -1){
					grid[3*(e/3)+(bb/3)][3*(e%3)+(bb%3)] = d;
					goto here;
				}
			}
		}

		here:;
	}
	bool finish = true;
	for(int i = 0; i < 9; i++){
		for(int e = 0; e < 9; e++){
			if(grid[i][e] == 0){
				finish = false;
			}
		}
	}
	if(finish) cout << "Easy\n";
	else cout << "Not easy\n";
	for(int i = 0; i < 9; i++){
		for(int e = 0; e < 9; e++){
			if(grid[i][e] != 0) cout << grid[i][e] << " ";
			else cout << ". ";
		}
		cout << endl;
	}
}
