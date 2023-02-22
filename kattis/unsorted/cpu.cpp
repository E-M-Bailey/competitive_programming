#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool isPrime(int n){
    if(n == 1) return false;
    if(n >= 13000000) return false;
    for(int i = 2; i*i <= n; i++){
        if(n%i == 0) return false;
    }
    return true;
}

int f(int U){
    int res = 0;
    for(int A = 1; A <= 40; A++){
        for(int B = 2-A; B <= 2000; B++){
            if(A == 0 && B == 0) continue;
            int p = 1;
            long long prod = 1;
            int ind = 0;
            while(prod <= U && isPrime(A*p+B)){
                p = A*p+B;
                prod *= p;
                ind++;
                if(prod <= U && ind >= 3){
                    res++;
                    cout << prod << endl;
                }
            }
        }
    }
    return res;
}

int main() {
    /*int n;
    cin >> n;
    for(int i = 0; i < n; i++){
        int l, r;
        cin >> l >> r;
        int ans = f(r) - f(l-1);
        cout << ans << endl;
    }
    cout << f(2000000000) << endl;*/


    /*set<int> explosive;
    for (int a = -2000; a <= 2000; a++) {
        for (int b = -2000; b <= 2000; b++) {
            ll curr = 1, prod = 1, c = 0;
            set<int> seen;
            while (true) {
                if (curr * a + b == curr || seen.find(curr * a + b) != seen.end()) break;
                curr = curr * a + b;
                seen.insert(curr);
                if (curr < 0 || !isPrime(curr)) break;
                prod *= curr;
                if (prod > 2e9) break;
                if (++c >= 3) {
                    explosive.insert(prod);
                }
            }
        }
    }*/
    vector<int> ee{105, 1419, 1729, 1885, 4505, 5719, 15387, 24211, 25085, 27559, 31929, 54205, 59081, 114985, 207177, 208681, 233569, 287979, 294409, 336611, 353977, 448585, 507579, 982513, 1012121, 1073305, 1242709, 1485609, 2089257, 2263811, 2953711, 3077705, 3506371, 3655861, 3812599, 3973085, 4293793, 4648261, 4813879, 5069629, 6173179, 6253085, 6622609, 6985249, 7355239, 7355671, 7558219, 8011459, 8413179, 8444431, 8712985, 8835799, 9271805, 9773731, 10235499, 13534129, 14662681, 15411785, 16596371, 18175361, 18578113, 18651417, 19827641, 20138379, 20771801, 22549639, 23691481, 25711399, 26000605, 26758057, 31852931, 32812089, 32894743, 34179391, 34878529, 35347159, 37605385, 38596273, 41305159, 42501439, 43055057, 44544219, 46999705, 48476449, 49982899, 52691801, 53399449, 54177877, 55902529, 56052361, 59267089, 65237577, 68633979, 69207769, 71550913, 71657209, 72457085, 72730439, 76724569, 78225589, 79796761, 84280585, 87393129, 92458529, 92835667, 96916279, 96931639, 100085785, 104966471, 118901521, 126893905, 127090931, 130692329, 133800661, 134574729, 161164441, 162913085, 167195509, 170383081, 172947529, 176116299, 177055201, 185245273, 195850411, 197916193, 199708657, 210509529, 212122639, 213701405, 216821881, 221042353, 222931549, 228842209, 237646105, 240479779, 249925249, 257519143, 265265329, 265786107, 266032009, 268578181, 269545249, 272174369, 290770505, 291335089, 306333559, 320237979, 321767447, 323476777, 332898769, 342116741, 367224619, 372526121, 375615073, 378606709, 392605449, 418637557, 426689979, 428108921, 443880589, 458576371, 483824809, 513769209, 559874269, 572905085, 578178931, 599938361, 604611019, 607692079, 627977681, 644074039, 656960585, 662998921, 667235531, 668997041, 671405827, 732641959, 758056531, 763651289, 770382685, 781296905, 790296729, 820192231, 826048329, 856970353, 872159101, 873571459, 939947009, 953055097, 959646507, 970578289, 976228129, 994732211, 995762585, 1006956091, 1007749849, 1017436249, 1020225061, 1023780151, 1056066169, 1075122185, 1102226791, 1129119819, 1136972771, 1140806899, 1151271109, 1158590105, 1164151711, 1191610211, 1244556249, 1262588371, 1268239597, 1276450585, 1299963601, 1306276309, 1324715137, 1348964401, 1412889731, 1414608769, 1449600967, 1455928891, 1495619759, 1518477085, 1539866809, 1586031409, 1614365473, 1615067791, 1637505339, 1640582839, 1640591017, 1641183305, 1659996371, 1667082529, 1674819721, 1675383631, 1715605681, 1743564961, 1743855049, 1748351011, 1793680361, 1813376689, 1826139169, 1886676121};


    int t;
    cin >> t;
    while (t--) {
        ll l,r;
        cin >> l >> r;
        int lb = lower_bound(ee.begin(), ee.end(), l) - ee.begin();
        int rb = upper_bound(ee.begin(), ee.end(), r) - ee.begin()-1;
        cout << rb - lb + 1 << '\n';
    }


    return 0;
}