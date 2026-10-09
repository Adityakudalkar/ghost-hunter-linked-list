# 👻 Ghost Hunter: Dual-Platform Game Engine

A hybrid Data Structures project showcasing a core **C++ Linked List Game Engine** paired with a modern, interactive **React + Vite Web GUI**. 

The game simulates a player navigating a haunted linear hallway, placing traps, scanning distance, and evading/capturing a wandering ghost driven by pointer traversal logic.

---

## 🛠️ Tech Stack & Architecture

- **Core Engine (C++17):** Implements room nodes (`Room`), explicit linked list traversal (`LinkedList`), game logic, trap detection, and ANSI terminal rendering.
- **Web Interface (React + Vite):** A modern graphical user interface built with React, Lucide Icons, and custom CSS styling for real-time visual tracking of node states.

---

## 📁 Project Structure

```text
ghost-hunter-cpp/
├── include/              # C++ Header Files
│   ├── Room.hpp          # Room struct (node definition)
│   ├── LinkedList.hpp    # Hallway dynamic linked list class
│   ├── Game.hpp          # Engine game loop & state handlers
│   └── UI.hpp            # Terminal UI and ANSI color rendering
├── src/                  # C++ Source Files
│   ├── main.cpp
│   ├── LinkedList.cpp
│   ├── Game.cpp
│   └── UI.cpp
├── ghost-hunter-gui/     # React + Vite Web Frontend
│   ├── src/
│   │   ├── App.jsx       # Interactive Web GUI & state management
│   │   └── main.jsx
│   ├── package.json
│   └── vite.config.js
└── README.md
