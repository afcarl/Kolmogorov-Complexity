#include <cstdlib>
#include <cstdio>
char s[2333333];
int main() {
    system("g++ client.cpp -o client.exe -lwsock32");
    system("client.exe 115.159.159.232 hello_socket 8080");
    FILE* fin = fopen("r.txt", "r");
    fscanf(fin, "%s", s);
    printf("%s", s);
    fclose(fin);
    system("del client.exe");
    system("del r.txt");
    return 0;
}