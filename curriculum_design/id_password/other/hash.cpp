#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>

using namespace std;
#define ull unsigned long long
#define ll long long
const int base = 2333;
const int Mod1 = 998244353;
const int Mod2 = 1000000007;
int n, tot;
char ch[2000];
int CalcHash(char *s, int len, int Mod) {
  int hash = 0;
  for (int i = 0; i < len; ++i)
    hash = (1ll * hash * base + s[i]) % Mod;
  return hash;
}
pair<int, int> ele[10010];
int main() {
  scanf("%d", &n);
  for (int i = 1, l; i <= n; ++i) {
    scanf("%s", ch);
    l = strlen(ch);
    ele[i] = make_pair(CalcHash(ch, l, Mod1), CalcHash(ch, l, Mod2));
    cout << ele[i].first << "\t" << ele[i].second << endl;
  }

  sort(&ele[1], &ele[n + 1]);
  tot = unique(&ele[1], &ele[n + 1]) - ele - 1;
  printf("%d\n", tot);
  return 0;
}