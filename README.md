# 🎵 Soundify

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML-2.5+-8CC445?style=for-the-badge&logo=sfml&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-Only-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![License](https://img.shields.io/badge/License-MIT-yellow?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Complete-brightgreen?style=for-the-badge)
![Data Structures](https://img.shields.io/badge/Data%20Structures-Custom%20Built-blueviolet?style=for-the-badge)

> A fully-featured **console-based music player** built in **C++**, powered by the **SFML Audio** library.  
> Play songs, manage playlists, browse genres, search tracks, and maintain a recently played history — all through an interactive terminal UI.

---

## 📸 Preview

```
  ██████  ██████  ██    ██ ███    ██ ██████  ██ ███████ ██    ██
 ██      ██    ██ ██    ██ ████   ██ ██   ██ ██ ██       ██  ██
 ███████ ██    ██ ██    ██ ██ ██  ██ ██   ██ ██ █████     ████
      ██ ██    ██ ██    ██ ██  ██ ██ ██   ██ ██ ██         ██
 ██████   ██████   ██████  ██   ████ ██████  ██ ██         ██
```

---

## 🚀 Features

### 🎶 Music Playback
- ▶️ Play, pause, resume, and stop songs
- ⏱️ Real-time playback duration display
- 🔁 Loop toggle (on/off)
- ⏭️ Skip forward / ⏮️ skip backward between songs
- 🎵 Smooth audio playback via **SFML Audio**

### 📚 Song Management
- 📂 Load and store songs from external files
- 🔍 Search songs by name
- 📋 Display all songs with metadata (name, artist, genre)

### 📂 Playlist System
- ➕ Create and ❌ delete playlists
- 🎵 Add / remove songs from any playlist
- 💾 Playlist data saved persistently to files
- ▶️ Play songs directly from any playlist
- 🕓 **Recently Played** playlist — auto-updated on every play

### 🌲 Genre Browsing
- 🌳 Genre hierarchy stored in a **complete binary tree**
- 🔽 Navigate genre nodes to explore sub-genres
- ⚡ Auto-generates a playlist of all songs matching a selected genre

---

## 🗃️ Data Structures Used

| Structure | Purpose |
|---|---|
| `Hash Table` | Fast O(1) average song lookup |
| `Doubly Linked List` | Playlist management |
| `Stack` | Recently played history |
| `Queue` | Binary tree node insertion |
| `Binary Tree` | Genre category navigation |
| `Linked List (chaining)` | Hash collision resolution |

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| Language | C++17 (OOP + Data Structures) |
| Audio Engine | SFML 2.5+ (Audio Module) |
| Console UI | Windows Console API (`windows.h`) |
| Memory | Dynamic memory management (raw pointers) |
| Storage | File I/O — `.txt` based persistent storage |

---

## 📁 Project Structure

```
Soundify/
│
├── main.cpp                  → Entry point, menu navigation
│
├── Song.h / Song.cpp         → Song metadata container
├── Hash.h / Hash.cpp         → Hash table for fast song lookup
├── Playlist.h / Playlist.cpp → Doubly linked list playlist manager
├── Tree.h / Tree.cpp         → Binary tree for genre browsing
├── Stack.h / Stack.cpp       → Recently played history stack
├── Queue.h / Queue.cpp       → Queue for tree insertion
│
├── playMusic.cpp             → Playback controller (SFML)
├── loadData.cpp              → Loads all songs on startup
│
└── D:/songs/
    ├── songs.txt             → Master song metadata file
    ├── Playlists.txt         → Saved playlists
    ├── Recently Played.txt   → Auto-updated history
    ├── <playlist>.txt        → Individual playlist files
    └── *.wav / *.ogg         → Audio files
```

---

## ⚙️ How It Works

```
1. songs.txt loads on startup
        ↓
2. Each song is hashed and stored in the Hash Table
        ↓
3. User navigates the terminal menu:
   ├── 🔍 Search songs
   ├── ▶️  Play songs
   ├── 📂 Manage playlists
   └── 🌲 Explore genres via binary tree
        ↓
4. Live playback controlled via keyboard input (SFML)
        ↓
5. Recently Played stack auto-updates after each play
```

---

## 🖥️ Requirements

- ✅ Windows OS (`conio.h` + `windows.h` dependencies)
- ✅ **SFML 2.5+** installed and linked
- ✅ **C++17** or higher
- ✅ Audio files and metadata placed in the correct folder:

```
D:\songs\
  ├── songs.txt
  ├── Playlists.txt
  ├── Recently Played.txt
  ├── <playlist>.txt
  └── audio files (.wav / .ogg / .mp3)
```

---

## 🔧 Build & Run

### 1. Clone the Repository
```bash
git clone https://github.com/shah-zaib-ali/SOUNDIFY.git
cd soundify
```

### 2. Install SFML
Download SFML 2.5+ from [sfml-dev.org](https://www.sfml-dev.org/download.php) and link it to your project.

### 3. Compile (g++ example)
```bash
g++ -std=c++17 main.cpp -o soundify -lsfml-audio -lsfml-system
```

### 4. Or open in Visual Studio
- Set up SFML include/lib paths in project properties
- Build and run with `F5`

### 5. Place your audio files
```
D:\songs\
```
Populate `songs.txt` with your song metadata in the expected format.

---

## 🎮 Controls

| Key | Action |
|---|---|
| `P` | Play / Pause |
| `S` | Stop |
| `N` | Next Song |
| `B` | Previous Song |
| `L` | Toggle Loop |
| `Q` | Quit Playback |

---

## 📌 Future Improvements

- [ ] 🖥️ GUI version using SFML Graphics module
- [ ] 🌍 Cross-platform support (remove `windows.h` dependency)
- [ ] 🔑 Improved hashing algorithm for song names
- [ ] 🧠 Replace raw pointers with smart pointers (`unique_ptr`, `shared_ptr`)
- [ ] 🗂️ JSON-based storage system (replace `.txt` files)
- [ ] 🎚️ Volume control & equalizer
- [ ] 🔎 Fuzzy search support

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).

---

<p align="center">
  Made with ❤️ and C++ — <strong>Soundify</strong>
</p>
