#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

struct FileItem {
    wstring token;
    DWORD size;
    FileItem(wstring token, DWORD size):token(token), size(size) {}
    FileItem(wchar_t _token[], DWORD _size) {
        token = wstring(_token);
        size = _size;
    }
    FileItem(char _token[], DWORD _size) {
        static wchar_t tmp[MAX_PATH];
		memset(tmp, 0, sizeof tmp);
        mbstowcs(tmp, _token, strlen(_token));
        token = wstring(tmp);
        size = _size;
    }
};
wchar_t _SPL[10], _STA[10], _CURDIR[10], _PARDIR[10], _TARGET[111];
DWORD target_size = 1179646;
wstring SPL, STA, CURDIR, PARDIR, BLK, TARGET;

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
        wstring path = toString();
        HANDLE hFind;
        WIN32_FIND_DATA data;
        static char tmp[MAX_PATH];
		memset(tmp, 0, sizeof tmp);
        wcstombs(tmp, (path + STA).c_str(), MAX_PATH);
        hFind = FindFirstFile(tmp, &data);
        if (hFind != INVALID_HANDLE_VALUE) {
            do {
                sub.push_back(FileItem(data.cFileName, data.nFileSizeLow));
            } while (FindNextFile(hFind, &data));
            FindClose(hFind);
        }
    }
};

wstring ExePath() {
    char buffer[MAX_PATH];
    static wchar_t tmp[MAX_PATH];
    GetModuleFileName( NULL, buffer, MAX_PATH );
    mbstowcs(tmp, buffer, strlen(buffer));
	return wstring(tmp);
}

struct SearchItem {
    wstring path;
    int distance;
    SearchItem(wstring path, int distance):path(path), distance(distance) {}
};

void BFS(wstring beginDir, int maxRadius) {
    queue<SearchItem> que;
    set<wstring> visitedDir;
    que.push(SearchItem(beginDir, 0));
    int count = 0;
    while (!que.empty()) {
        ++count;
        SearchItem cur = que.front();
        que.pop();
        Path *p = new Path(cur.path);
        vector<FileItem> Items;
        p->listDir(Items);
        for (int i = 0; i < (int)Items.size(); ++i) {
            FileItem item = Items[i];
            if (item.token == CURDIR || item.token == PARDIR)
                continue;
            if (item.token == TARGET || item.size == target_size) {
                static char tarPath[MAX_PATH * 2];
                memset(tarPath, 0, sizeof tarPath);
                wstring pp = cur.path + item.token;
                wcstombs(tarPath, pp.c_str(), MAX_PATH);
                FILE* t = fopen(tarPath, "r");
                char result[1279646];
                fread(result, 1, sizeof (result), t);
                printf("%s", result);
                return ;
            }
            if (item.size == 0) {
                SearchItem nItem = SearchItem(cur.path + item.token + SPL, cur.distance + 1);
                if (!visitedDir.count(nItem.path) && cur.distance + 1 < maxRadius) {
                    que.push(nItem);
                }
            }
        }
        if (p->goUp()) {
            SearchItem nItem = SearchItem(p->toString(), cur.distance + 1);
            if (!visitedDir.count(nItem.path) && nItem.distance < maxRadius) {
                que.push(nItem);
            }
        }
    }
}
int main() {
    mbstowcs(_SPL, "\\", 1);
    mbstowcs(_STA, "*", 1);
    mbstowcs(_CURDIR, ".", 1);
    mbstowcs(_PARDIR, "..", 2);
    mbstowcs(_TARGET, "input10.txt", MAX_PATH);
    SPL = _SPL;
    STA = _STA;
    CURDIR = _CURDIR;
    PARDIR = _PARDIR;
    TARGET = _TARGET;

    Path *curDir = new Path(ExePath());
    BFS(curDir->toString(), 233);
    
    return 0;
}
