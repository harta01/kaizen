#include <bits/stdc++.h>
using namespace std;

const int MAXC = 20;

class Trie {
    public:
        bool is_word;
        char chr;
        vector<Trie*> children;

        Trie() {
            this->is_word = false;
        }
        Trie(char _chr) {
            this->is_word = false;
            this->chr = _chr;
        }
};

int n;
char* s, *longest;
Trie* root;
vector<char> ans;

bool cf(char* a, char* b) {
    return strlen(a) > strlen(b);
}

void insert_trie(int idx) {
    Trie *curr = root;
    int len = strlen(s);
    for (int idx = 0; idx < len; idx++) {
        bool found = false;
        for (int i = 0; i < curr->children.size(); i++) {
            if (curr->children[i]->chr == s[idx]) {
                curr = curr->children[i];
                found = true;
                break;
            }
        }
        if (!found) {
            curr->children.push_back(new Trie(s[idx]));
            curr = curr->children[curr->children.size() - 1];
        }
    }
    curr->is_word = true;
}

void input() {
    scanf("%d", &n);

    root = new Trie();
    for (int i = 0; i < n; i++) {
        s = (char*)malloc(sizeof(char) * MAXC);
        scanf("%s", s);
        insert_trie(0);
        if (i == 0) {
            longest = (char*)malloc(sizeof(char) * MAXC);
        }
        if (i == 0 || strlen(longest) < strlen(s)) {
            memcpy(longest, s, sizeof(char) * strlen(s));
        }
    }
}

void print_trie(Trie *curr) {
    ans.push_back(curr->chr);
    if (curr->is_word) ans.push_back('P');
    for (int i = 0; i < curr->children.size(); i++) {
        print_trie(curr->children[i]);
    }
    ans.push_back('-');
}

void traverse(Trie *curr, int idx) {
    if (idx >= strlen(longest)) {
        ans.push_back('P');
        return;
    }
    Trie *next = NULL;
    for (int i = 0; i < curr->children.size(); i++) {
        if (curr->children[i]->chr == longest[idx]) {
            next = curr->children[i];
            continue;
        }
        print_trie(curr->children[i]);
    }
    if (curr->is_word) ans.push_back('P');
    ans.push_back(longest[idx]);
    traverse(next, idx + 1);
}

int main() {
    input();

    traverse(root, 0);
    printf("%d\n", ans.size());
    for (int i = 0; i < ans.size(); i++) {
        printf("%c\n", ans[i]);
    }
    return 0;
}
