#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
wstring SPL;
struct Path:vector<wstring> {
    Path(wstring path) {
        int last_pos = 0;
        for (int i = 0; i < (int)path.length(); ++i) {
            if (path[i] == '\\') {
                push_back(path.substr(last_pos, i - last_pos));
                last_pos = i + 1;
            }
        }
    }
    bool goUp() {
        if (size() > 0) {
            pop_back();
            return true;
        }
        return false;
    }
    wstring toString() {
        wstring ret;
        for (size_t i = 0;  i < size(); ++i) {
            ret = ret + at(i) + SPL;
        }
        return ret;
    }
    void listDir(vector<FileItem>&sub) {
        sub.clear();
        string path = toString();
        HANDLE hFind;
        WIN32_FIND_DATA data;
        hFind = FindFirstFile((path + "*").c_str(), &data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                sub.push_back(FileItem((wstring)data.cFileName, data.nFileSizeLow));
            } while (FindNextFile(hFind, &data));
            FindClose(hFind);
        }
    }
};

string ExePath() {
    char buffer[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
	return string(buffer);
}

int main() {
    return 0;
}