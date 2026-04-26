#include <SFML/Audio.hpp>
#include <SFML/System/Time.hpp>
#include <iostream>
#include<fstream>
#include<conio.h>
#include <Windows.h>
#include<cstdlib>

using namespace std;
using namespace sf;

//classes
class Song;
class HashNode;
class PNode;
class SNode;
class TNode;
class QNode;
class Hash;
class Playlist;
class Stack;
class Queue;
class Tree;

//functions
int stringToInt(string);
string duration(float);
void checkMusic(Music&, int);
void playMusic(Song&, Hash&);
void loadData();
void displayAllSongs(Hash&);
void mainMenu(Hash&);
void playlistMenu(Hash&);
bool createPlaylist(string*, int);
bool deletePlaylist(string*, int);
void displayPlaylists(string*, int);
void addToPlaylist(Song*, Hash&);
void selectPlaylist(string, Hash&);
void updateRecentlyPlayed(string);
void genreMenu(Hash&);
void selectGenre(string, Hash&, TNode*);
string getGenre(TNode*);
bool populateGenre(TNode*, Playlist&, Hash&, string, bool);
void logo();

//classes

class Song {
public:
    string name;
    string artist;
    string genre;
    string path;
    Song() {}
    void display() {
        cout << "Song name = " << name << " , Artist name = " << artist << " , Genre = " << genre << endl << endl;
    }
};

class HashNode {
public:
    Song data;
    HashNode* next;
    HashNode(Song s) {
        data = s;
        next = NULL;
    }
};

class PNode {
public:
    Song* data;
    PNode* next;
    PNode* prev;
    PNode(Song* d) {
        data = d;
        next = NULL;
        prev = NULL;
    }
};

class TNode {
public:
    string data;
    TNode* left;
    TNode* right;
    TNode(string d) {
        data = d;
        left = right = NULL;
    }
};

class SNode {
public:
    string data;
    SNode* next;
    SNode(string d) {
        data = d;
        next = NULL;
    }
};

class Qnode {
public:
    TNode* data;
    Qnode* next;
    Qnode(TNode* d) {
        data = d;
        next = NULL;
    }
};

class Hash {
public:
    HashNode** table;
    int size;
    Hash(int s) {
        table = new HashNode * [s];
        size = s;
        for (int i = 0; i < s; i++) {
            table[i] = NULL;
        }
    }
    void insert(HashNode* q) {
        HashNode* p = table[stringToInt(q->data.name) % size];
        if (p == NULL) {
            table[stringToInt(q->data.name) % size] = q;
            return;
        }
        while (p && p->next) {
            p = p->next;
        }
        p->next = q;
    }
    void insertGenre(HashNode* q) {
        HashNode* p = table[stringToInt(q->data.genre) % size];
        if (p == NULL) {
            table[stringToInt(q->data.genre) % size] = q;
            return;
        }
        while (p && p->next) {
            p = p->next;
        }
        p->next = q;
    }
    Song* search(string i) {
        HashNode* p = table[stringToInt(i) % size];
        if (p == NULL) {
            return NULL;
        }
        while (p != NULL) {
            if (p->data.name == i) {
                return &p->data;
            }
            p = p->next;
        }
        return NULL;
    }
    void dislay() {
        int i;
        HashNode* p;
        for (i = 0; i < size; i++) {
            cout << i << " : ";
            if (table[i] == NULL) {
                cout << "  " << endl;
                continue;
            }
            p = table[i];
            while (p) {
                cout << p->data.name << ":" << stringToInt(p->data.name) << " , " << p->data.genre << " | ";
                p = p->next;
            }
            cout << endl;
        }
    }
};

class Playlist {
public:
    string name;
    PNode* head;
    PNode* tail;
    Playlist(string str) {
        name = str;
        head = NULL;
        tail = NULL;
    }
    void insertLast(Song* value = NULL) {
        PNode* p = new PNode(value);
        if (!head) {
            head = p;
            tail = p;
            return;
        }
        p->prev = tail;
        tail->next = p;
        tail = p;
    }
    void insertFirst(Song* value = NULL) {
        if (value == NULL) {
            return;
        }
        PNode* p = new PNode(value);
        if (!head) {
            head = p;
            tail = p;
            return;
        }
        head->prev = p;
        p->next = head;
        head = p;
    }
    void insertAfter(int key, Song* value = NULL) {
        if (value == NULL) {
            return;
        }
        if (key<0 || key>length()) {
            cout << "Invalid key" << endl;
            return;
        }
        if (key == 0) {
            insertFirst(value);
            return;
        }
        if (key == length()) {
            insertLast(value);
            return;
        }
        PNode* p, * q = head;
        p = new PNode(value);
        for (int i = 0; i < key - 1; i++) {
            q = q->next;
        }
        p->prev = q;
        p->next = q->next;
        q->next->prev = p;
        q->next = p;
    }
    void del(int key) {
        if (key<0 || key>length() - 1) {
            cout << "Invalid key" << endl;
            return;
        }
        PNode* p = head, * q = NULL;
        if (key == 0) {
            if (p && p->next == NULL) {
                delete p;
                head = tail = NULL;
                return;
            }
            p->next->prev = NULL;
            head = p->next;
            delete p;
            return;
        }
        if (key == length() - 1) {
            p = tail;
            p->prev->next = NULL;
            tail = p->prev;
            delete p;
            return;
        }
        for (int i = 0; i < key; i++) {
            q = p;
            p = p->next;
        }
        p->next->prev = q;
        q->next = p->next;
        delete p;
    }
    bool update() {
        string filename = "D:\\songs\\" + name + ".txt";
        fstream file;
        file.open(filename, ios::out);
        if (!file || head == NULL) {
            return 0;
        }
        PNode* p = head;
        while (p) {
            file << p->data->name << endl;
            p = p->next;
        }
        file.close();
        return 1;
    }
    bool read(Hash& h) {
        string line, filename = "D:\\songs\\" + name + ".txt";
        fstream file;
        Song* p = NULL;
        file.open(filename, ios::in);
        if (!file) {
            return 0;
        }
        while (getline(file, line)) {
            p = h.search(line);
            insertLast(p);
        }
        file.close();
        if (head == NULL) {
            return 0;
        }
        return 1;
    }
    void display() {
        PNode* p = head;
        int i = 0;
        while (p) {
            cout << i << " : " << p->data->name << endl;
            p = p->next;
            i++;
        }
    }
    int length() {
        PNode* p = head;
        int cnt = 0;
        while (p) {
            cnt++;
            p = p->next;
        }
        return cnt;
    }
    PNode* get(int key) {
        if (key < 0 || key >= length()) {
            return NULL;
        }
        PNode* p = head;
        for (int i = 0; i < key; i++) {
            p = p->next;
        }
        return p;
    }
    void playMusic(PNode* p) {
        Song* song = p->data;
        system("cls");
        logo();
        updateRecentlyPlayed(p->data->name);
        Music music;
        music.openFromFile(song->path);
        song->display();
        cout << "Song duration = " << duration(music.getDuration().asSeconds()) << endl << endl;
        cout << "Press the following keys during playback:\n";
        cout << "0 : Replay / Resume\n";
        cout << "1 : Pause\n";
        cout << "2 : Set / Reset loop\n";
        cout << "3 : Forward (next song)\n";
        cout << "4 : Backward (previous song)\n";
        cout << "5 : Exit\n\n";

        char temp;
        int check = 0;
        int choice = -1;
        music.play();
        while (choice != 5) {
            while (!_kbhit()) {
                Sleep(1000);
                if (music.getStatus() == 0) {
                    if (p->next) {
                        check = 1;
                        playMusic(p->next);
                        break;
                    }
                    else if (p->prev) {
                        check = 1;
                        playMusic(p->prev);
                        break;
                    }
                    else {
                        check = 1;
                        break;
                    }
                }
                cout << "\rLoop = " << (music.getLoop() ? "Y , Current duration = " : "N , Current duration = ")
                    << duration(music.getPlayingOffset().asSeconds()) << "       ";

            }
            if (check == 1) {
                break;
            }
            temp = _getch();
            choice = temp - '0';
            if (choice == 0) {
                music.play();
            }
            else if (choice == 1) {
                music.pause();
            }
            else if (choice == 2) {
                music.setLoop(!music.getLoop());
            }
            else if (choice == 5) {
                break;
            }
            else if (choice == 3) {
                if (p->next != NULL) {
                    music.stop();
                    playMusic(p->next);
                    break;
                }
                else {
                    cout << " <<No song available.>>";
                    Sleep(2000);
                    cout << "\r" << "Loop = " << (music.getLoop() ? "Y , Current duration = " : "N , Current duration = ") << duration(music.getPlayingOffset().asSeconds()) << "                       ";
                }
            }
            else if (choice == 4) {
                if (p->prev != NULL) {
                    music.stop();
                    playMusic(p->prev);
                    break;
                }
                else {
                    cout << " <<No song available.>>";
                    Sleep(2000);
                    cout << "\r" << "Loop = " << (music.getLoop() ? "Y , Current duration = " : "N , Current duration = ") << duration(music.getPlayingOffset().asSeconds()) << "                       ";
                }
            }
            else {
                continue;
            }
            cout << "                                   \r";
        }
        music.stop();
        system("cls");
    }
};

class Stack {
public:
    SNode* top;
    int size;
    Stack() {
        size = 0;
        top = NULL;
    }
    void push(string d) {
        if (top == NULL) {
            size++;
            top = new SNode(d);
            return;
        }
        size++;
        SNode* p = new SNode(d);
        p->next = top;
        top = p;
    }
    string pop() {
        if (top == NULL) {
            return " ";
        }
        size--;
        SNode* p = top;
        top = top->next;
        return p->data;
    }
    bool isEmpty() {
        if (top == NULL) {
            return true;
        }
        return false;
    }
    string peek() {
        if (top == NULL) {
            return " ";
        }
        return top->data;
    }
    bool isPresent(string d) {
        SNode* p = top;
        while (p) {
            if (p->data == d) {
                return 1;
            }
            p = p->next;
        }
        return 0;
    }
    void display() {
        SNode* p = top;
        while (p) {
            cout << p->data << " | ";
            p = p->next;
        }
        cout << endl;
    }
};

class Queue {
public:
    Qnode* front;
    Qnode* rear;
    Queue() {
        front = rear = NULL;
    }
    bool isEmpty() {
        if (front == NULL) {
            return 1;
        }
        return 0;
    }
    void enqueue(TNode* d) {
        if (front == NULL) {
            front = new Qnode(d);
            rear = front;
            return;
        }
        Qnode* p = new Qnode(d);
        rear->next = p;
        rear = rear->next;
    }
    TNode* dequeue() {
        if (isEmpty()) {
            return NULL;
        }
        Qnode* q = front;
        front = front->next;
        TNode* p = q->data;
        delete q;
        return p;
    }
};

class Tree {
private:
    void preorder(TNode* t) {
        if (t != NULL) {
            cout << t->data << endl;
            preorder(t->left);
            preorder(t->right);
        }
    }
public:
    TNode* root;
    Tree() {
        root = NULL;
    }
    void insert(string str) {
        if (root == NULL) {
            root = new TNode(str);
            return;
        }
        Queue q;
        TNode* p = root;
        TNode* newNode = new TNode(str);
        q.enqueue(p);
        while (!q.isEmpty()) {
            p = q.dequeue();
            if (p->left == NULL) {
                p->left = newNode;
                return;
            }
            else {
                q.enqueue(p->left);
            }
            if (p->right == NULL) {
                p->right = newNode;
                return;
            }
            else {
                q.enqueue(p->right);
            }
        }
    }
    void preOrder() {
        preorder(root);
        cout << endl;
    }

};

//functions

string duration(float total) {
    string str = "";
    str += to_string((int)(total / 60));
    str += ":";
    str += to_string((int)total % 60);
    return str;
}

int stringToInt(string str) {
    int num = 0;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z')) {
            num += str[i] - '0';
        }
    }
    return num;
}

void checkMusic(Music& music, int a) {
    if (a == 0) music.play();
    else if (a == 1) music.pause();
    else if (a == 2) {
        music.stop();
    }
}

void playMusic(Song& song, Hash& h) {
    system("cls");
    logo();
    updateRecentlyPlayed(song.name);
    Music music;
    music.openFromFile(song.path);
    song.display();
    cout << "Song duration = " << duration(music.getDuration().asSeconds()) << endl << endl;
    cout << "Press the following keys during playback:\n";
    cout << "0 : Play / Replay / Resume\n";
    cout << "1 : Pause\n";
    cout << "2 : Stop\n";
    cout << "3 : Add to a playlist\n";
    cout << "4 : Exit\n\n";

    char temp;
    int choice = -1;
    while (choice != 4) {
        while (!_kbhit()) {
            Sleep(1000);
            cout << "\r" << duration(music.getPlayingOffset().asSeconds());
        }
        temp = _getch();
        choice = temp - '0';
        if (choice < 0 || choice>4) {
            music.stop();
            break;
        }
        if (choice == 3) {
            music.stop();
            addToPlaylist(&song, h);
            break;
        }
        checkMusic(music, choice);
        cout << "     \r";
    }
    music.stop();
    system("cls");
}

void displayAllSongs(Hash& h) {
    Song** allSongs;
    allSongs = new Song * [h.size];
    int i, j = 0;
    for (i = 0; i < h.size; i++) {
        HashNode* p = h.table[i];
        while (p) {
            allSongs[j++] = &p->data;
            p = p->next;
        }
    }
    int num = j, choice = 0;
again:
    system("cls");
    logo();
    for (i = 0; i < num; i++) {
        cout << i << " : ";
        allSongs[i]->display();
    }
    cout << "Enter song number to play or -1 to exit = ";
    cin >> choice;
    if (choice < -1 || choice >= num) {
        goto again;
    }
    else if (choice == -1) {
        return;
    }
    playMusic(*allSongs[choice], h);
    goto again;
}

void searchAnySong(Hash& h) {
    string input;
    int key;
again:
    system("cls");
    logo();
    cout << "Enter song name to search or enter exit to exit the search = ";
    getline(cin, input);
    if (input == "exit") {
        return;
    }
    key = stringToInt(input);
    HashNode* p = NULL;
    p = h.table[key % h.size];
    if (p == NULL) {
        cout << "Song not found.Enter any key to continue.";
        _getch();
        cin.ignore(1, '\n');
        goto again;
    }
    Song* song = NULL;
    while (p) {
        if (input == p->data.name) {
            song = &p->data;
            break;
        }
        p = p->next;
    }
    if (song == NULL) {
        cout << "Song not found.Press any key to continue.";
        _getch();
        goto again;
    }
    playMusic(*song, h);
    goto again;
}

void playlistMenu(Hash& h) {
    string line;
    int num, choice;
    fstream file;
    file.open("D:\\songs\\Playlists.txt", ios::in);
    if (!file) {
        mainMenu(h);
    }
    getline(file, line);
    num = stoi(line);
    string* arr = new string[num];
    for (int i = 0; i < num && getline(file, line); i++) {
        arr[i] = line;
    }
again:
    system("cls");
    logo();
    cout << "Total playlists = " << num << endl;
    displayPlaylists(arr, num);
    cout << endl << "Enter playlist number to select that playlist, -1 to create a new playlist, -2 to delete a playlist and -3 to exit." << endl;
    cin >> choice;
    cin.ignore();
    if (choice == -3) {
        mainMenu(h);
    }
    if (choice<-3 || choice>num) {
        goto again;
    }
    if (choice == -1) {
        if (createPlaylist(arr, num)) {
            cout << "Playlist created.Press any key to continue." << endl;
            _getch();
            playlistMenu(h);
        }
        else {
            cout << "Error creating playlist.Press any key to continue." << endl;
            _getch();
            goto again;
        }
    }
    if (choice == -2) {
        if (deletePlaylist(arr, num)) {
            cout << "Playlist deleted.Press any key to continue." << endl;
            _getch();
            playlistMenu(h);
        }
        else {
            cout << "Error deleting playlist.Press any key to continue." << endl;
            _getch();
            goto again;
        }
    }
    else {
        selectPlaylist(arr[choice], h);
        goto again;
    }
}

bool createPlaylist(string* arr, int size) {
    string str;
    int i;
    system("cls");
    logo();
    cout << "Enter playlist name = ";
    getline(cin, str);
    for (i = 0; i < size; i++) {
        if (arr[i] == str) {
            return 0;
        }
    }
    fstream file;
    file.open("D:\\songs\\" + str + ".txt", ios::out);
    if (!file) {
        return 0;
    }
    file.close();
    file.open("D:\\songs\\Playlists.txt", ios::out);
    if (!file) {
        return 0;
    }
    file << size + 1 << endl;
    for (i = 0; i < size; i++) {
        file << arr[i] << endl;
    }
    file << str << endl;
    file.close();
    return 1;
}

bool deletePlaylist(string* arr, int size) {
    string str;
    fstream file;
    system("cls");
    logo();
    for (int j = 1; j < size; j++) {
        cout << "*) " << arr[j] << endl;
    }
    cout << "Enter playlist name to be deleted = ";
    getline(cin, str);
    if (str == "Recently Played") {
        return 0;
    }
    int i, check = 0;
    for (i = 1; i < size; i++) {
        if (arr[i] == str) {
            check = 1;
        }
    }
    if (check == 0) {
        return 0;
    }
    file.open("D:\\songs\\Playlists.txt", ios::out);
    if (!file) {
        return 0;
    }
    file << size - 1 << endl;
    for (i = 0; i < size; i++) {
        if (arr[i] == str) {
            continue;
        }
        file << arr[i] << endl;
    }
    remove(("D:\\songs\\" + str + ".txt").c_str());

    file.close();
    return 1;
}

void displayPlaylists(string* arr, int size) {
    for (int i = 0; i < size; i++) {
        cout << i << " : " << arr[i] << endl;
    }
}

void addToPlaylist(Song* song, Hash& h) {
    int i, num, choice;
    string line;
    fstream file;
    file.open("D:\\songs\\Playlists.txt", ios::in);
    if (!file) {
        return;
    }
    getline(file, line);
    num = stoi(line);
    string* arr = new string[num];
    for (int i = 0; i < num && getline(file, line); i++) {
        arr[i] = line;
    }
again:
    system("cls");
    logo();
    for (int i = 1; i < num; i++) {
        cout << i << " : " << arr[i] << endl;
    }
    cout << "Enter playlist number to add song or -1 to exit = ";
    cin >> choice;
    cin.ignore();
    if (choice == -1) {
        return;
    }
    else if (choice <= 0 || choice >= num) {
        goto again;
    }
    else {
        Playlist p(arr[choice]);
        p.read(h);
        p.insertLast(song);
        p.update();
        cout << "Song added to playlist.Press any key to continue.";
        _getch();
    }
}

void selectPlaylist(string str, Hash& h) {
    Playlist playlist(str);
    int choice;
    if (!playlist.read(h)) {
        cout << "Error accessing playlist.Press any key to continue.";
        _getch();
        return;
    }
again:
    system("cls");
    logo();
    cout << "Total songs = " << playlist.length() << endl;
    playlist.display();
    cout << "Enter song number to play,-1 to delete a song and -2 to exit = ";
    cin >> choice;
    cin.ignore();
    if (choice < -2 || choice >= playlist.length()) {
        goto again;
    }
    else if (choice == -1) {
        if (str == "Recently Played") {
            cout << "Cannot delete song from this playlist.Press any key to continue.";
            _getch();
            goto again;
        }
        cout << "Enter song number to delete = ";
        cin >> choice;
        if (choice < 0 || choice >= playlist.length()) {
            goto again;
        }
        else {
            //playlist.display();
            playlist.del(choice);
            playlist.update();
            selectPlaylist(str, h);
        }
    }
    else if (choice == -2) {
        return;
    }
    else {
        playlist.playMusic(playlist.get(choice));
        if (str == "Recently Played") {
            selectPlaylist(str, h);
            return;
        }
        goto again;
    }
}

void updateRecentlyPlayed(string name) {
    string line;
    fstream file;
    file.open("D:\\songs\\Recently Played.txt", ios::in);
    if (!file) {
        return;
    }
    Stack s1, s2;
    while (getline(file, line)) {
        s1.push(line);
    }
    file.close();
    if (s1.isEmpty()) {
        return;
    }
    if (s1.size >= 5) {
        s1.pop();
        while (!s1.isEmpty()) {
            if (s1.peek() == name) {
                s1.pop();
                continue;
            }
            s2.push(s1.pop());
        }
        s2.push(name);
    }
    else {
        while (!s1.isEmpty()) {
            if (s1.peek() == name) {
                s1.pop();
                continue;
            }
            s2.push(s1.pop());
        }
        s2.push(name);
    }
    file.open("D:\\songs\\Recently Played.txt", ios::out);
    while (!s2.isEmpty()) {
        file << s2.pop() << endl;
    }
    file.close();
}

string getGenre(TNode* p) {
    system("cls");
    logo();
    if (p == NULL) {
        return " ";
    }
    if (p->left == NULL && p->right == NULL) {
        return p->data;
    }
    int choice;
    cout << "Current genre = " << p->data << endl;
    cout << "0 : " << (p->left->data) << endl << "1 : " << (p->right->data) << endl;
    cout << "Enter genre number or enter -1 to select current genre or -2 to exit = ";
    cin >> choice;
    cin.ignore();
    if (choice == 0) {
        return getGenre(p->left);
    }
    else if (choice == 1) {
        return getGenre(p->right);
    }
    else if (choice == -1) {
        return p->data;
    }
    else if (choice == -2) {
        return "exit";
    }
    else {
        return getGenre(p);
    }
}

void genreMenu(Hash& h1) {
    string line;
    fstream file;
    file.open("D:\\songs\\genre.txt", ios::in);
    if (!file) {
        return;
    }
    Tree tree;
    while (getline(file, line)) {
        tree.insert(line);
    }
    int i;
    HashNode* p;
    Hash h2(h1.size);
    for (i = 0; i < h1.size; i++) {
        p = h1.table[i];
        while (p) {
            h2.insertGenre(new HashNode(p->data));
            p = p->next;
        }
    }
    selectGenre(getGenre(tree.root), h2, tree.root);
}

bool populateGenre(TNode* p, Playlist& playlist, Hash& h, string str, bool check) {
    if (p == NULL && check) {
        return true;
    }
    if (p == NULL && !check) {
        return false;
    }
    if (check || str == p->data) {
        HashNode* q = h.table[stringToInt(p->data) % h.size];
        while (q) {
            if (q->data.genre == p->data) {
                playlist.insertFirst(&q->data);
            }
            q = q->next;
        }
    }
    if ((str == p->data || check) && populateGenre(p->left, playlist, h, str, true) && populateGenre(p->right, playlist, h, str, true)) return true;
    else return (populateGenre(p->left, playlist, h, str, false) || populateGenre(p->right, playlist, h, str, false));
}

void selectGenre(string str, Hash& h, TNode* p) {
    int choice;
    if (str == "exit") {
        return;
    }
    Playlist playlist(str);
    if (!populateGenre(p, playlist, h, str, false)) {
        return;
    }
again:
    system("cls");
    logo();
    cout << "Current genre = " << str << ". Enter Song number to play or -1 to exit." << endl;
    playlist.display();
    cin >> choice;
    cin.ignore();
    if (choice == -1) {
        return;
    }
    else if (choice < -1 || choice >= playlist.length()) {
        goto again;
    }
    else {
        playlist.playMusic(playlist.get(choice));
        goto again;
    }
}

void centerText(const string& text) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int consoleWidth;

    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    int textLength = text.length();
    int spaces = (consoleWidth - textLength) / 2;

    for (int i = 0; i < spaces; ++i) {
        cout << " ";
    }

    cout << text << endl;
}

void logo() {
    string logo[5] = { {"------------------------------------------------------------------"},
                      {"|||                                                            |||"},
                      {"|||                       SOUNDIFY                              |||"},
                      {"|||                                                            |||"},
                      {"------------------------------------------------------------------"}
    };
    cout << "\n";
    for (int i = 0; i < 5; i++) {
        centerText(logo[i]);
    }
    cout << "\n";
}

void loadData() {
    string line;
    ifstream in("D:\\songs\\songs.txt");
    if (!in) {
        return;
    }
    getline(in, line);
    int n = stoi(line);
    Song song;
    Hash allSongs(n);
    int i;
    for (i = 0; i < n && getline(in, line); i++) {
        song.name = line;
        getline(in, line);
        song.artist = line;
        getline(in, line);
        song.genre = line;
        getline(in, line);
        song.path = line;
        allSongs.insert(new HashNode(song));
    }
    in.close();
    mainMenu(allSongs);
}

void mainMenu(Hash& h) {
    int choice;
again:
    system("cls");
    logo();
    cout << "1.Search any song.\n2.Display all songs.\n3.Playlists.\n4.Select songs by Genre\n5.Exit\nEnter any choice = ";
    cin >> choice;
    if (choice == 5) {
        exit(0);
    }
    if (choice == 1) {
        cin.ignore(1, '\n');
        searchAnySong(h);
        goto again;
    }
    else if (choice == 2) {
        displayAllSongs(h);
        goto again;
    }
    else if (choice == 3) {
        playlistMenu(h);
        goto again;
    }
    else if (choice == 4) {
        genreMenu(h);
        goto again;
    }
    else {
        goto again;
    }
}

int main()
{
    system("Color 17");
    loadData();
}
