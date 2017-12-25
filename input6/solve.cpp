#include <cstdio>
#include <cstring>
char s[5000][13] = {"000000000000"};
int main() {
	for (int i = 0; i < 12;) {
		for (int j = 0; j < (1<<i); ++j)
			memcpy(s[(1<<(i+1)) - j - 1], s[j], 12);
		for (int j = 1<<i++; j < (1<<i); ++j)
			s[j][i-1] = '1';
	}
	for (int i = 0; i < 4096; ++i)
		printf("%s", s[i]);
	return 0;
}