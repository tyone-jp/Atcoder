#include <bits/stdc++.h>
#define rep(i,n) for (int i = 0; i < (int)(n); i++)
using namespace std;

int main() {
   int k;
   cin >> k;
   int n = 8;
   char data[n][n];
   rep(i,n)rep(j,n) data[i][j] = '.';
   vector<int> perm(n);
   rep(i,n) perm[i] = i;
   vector<int> x(k), y(k);
   rep(i,k) {
      int X, Y;
      cin >> X >> Y;
      x[i] = X;
      y[i] = Y;
   }
   do {
      bool ok = true;
      rep(i,k) {
         if (perm[y[i]] != x[i]) ok = false;
      }
      if (ok) {
         bool ans = true;
         rep(i,7) {
            for (int j = 1; i+j < n; j++) {
               if (perm[i] + j == perm[i+j]) ans = false;
               if (perm[i] - j == perm[i+j]) ans = false;
            }
         }
         if (ans) {
            rep(i,n) {
               data[perm[i]][i] = 'Q';
            }
            rep(i,n) {
               rep(j,n) {
                  cout << data[i][j];
               }
               cout << endl;
            }
            return 0;
         }
      }
   } while(next_permutation(perm.begin(),perm.end()));
}