#include <windows.h>
#include <bits/stdc++.h>
using namespace std;

#define token first
#define sizToken second
struct FileItem {
    wstring token;
    DWORD size;
    FileItem(wstring token, DWORD size):token(token), size(size) {}
};
wchar_t SPL = "\\";
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

#define path first
#define distance second
typedef pair<string, int> SearchItem;

void BFS(string beginDir, int maxRadius) {
    queue<pair<string, int> > que;
    set<string> visitedDir;
    que.push(make_pair(beginDir, 0));
    while (!que.empty()) {
        SearchItem cur = que.front();
        que.pop();
        Path *p = new Path(cur.path);
        vector<Item> Items;
        p->listDir(Items);
        for (int i = 0; i < (int)Items.size(); ++i) {
            Item item = Items[i];
            if (item.token == "." || item.token == "..")
                continue;
            cout << cur.path + item.token + (item.sizToken == 0 ? "\\" : "") << ' ' << item.sizToken << endl;
            if (item.sizToken == 0) {
                SearchItem nItem = make_pair(cur.path + item.token + "\\", cur.distance + 1);
                if (!visitedDir.count(nItem.path) && cur.distance + 1 < maxRadius) {
                    que.push(nItem);
                }
            }
        }
        if (p->goUp()) {
            SearchItem nItem = make_pair(p->toString(), cur.distance + 1);
            if (!visitedDir.count(nItem.path) && nItem.distance < maxRadius) {
                que.push(nItem);
            }
        }
    }
}
int main() {
    Path *curDir = new Path(ExePath());
    BFS(curDir->toString(), 3);
    return 0;
}