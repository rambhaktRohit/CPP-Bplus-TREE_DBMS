# 🎓 University Data Management System (Custom DBMS)
<br>

![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg) ![Language: C++](https://img.shields.io/badge/Language-C++-blue.svg) ![Architecture: B+Tree](https://img.shields.io/badge/Architecture-B%2B%20Tree-green.svg)

A high-performance, file-based Database Management System (DBMS) built from scratch in C++. 
This project implements a **B+ Tree** for indexing and uses a **File System** for persistent storage, mimicking real-world database architectures like MySQL or PostgreSQL.
<br>
<br>

---
<br>

## 🚀 Features
* **B+ Tree Indexing:** Utilizes a custom B+ Tree algorithm for optimized **O(log n)** search complexity.
* **Persistent Storage:** Student data (Name, Age, Course) is serialized and saved to disk (`.txt` files), ensuring data persists after the program closes.
* **Crash Handling:** Implements robust input sanitization (`cin.fail()`) to prevent infinite loops on invalid user inputs.
* **CRUD Operations:** Supports Adding students with duplicate checks and Searching records efficiently.
* **Balanced Architecture:** Automatically handles node splitting and merging to keep the tree balanced.
<br>

---
<br>

## 🛠️ Tech Stack
* **Language:** C++ (Standard Template Library)
* **Data Structure:** B+ Tree (Degree `t=3`)
* **Algorithm:** B-Tree Splitting & Merging ("Traffic Sign" Logic)
* **Storage:** File I/O (`fstream`) for persistent data
* **Environment:** Compatible with GCC/G++ compilers (Windows/Linux/Mac)
<br>

---
<br>

## 📸 Project Demo & Walkthrough

### 1. Data Entry & Input Validation


*The clean CLI interface allows users to add student records. The system handles input validation to prevent crashes (e.g., ensuring IDs are numbers).*
![Input Demo](demo_input.png.png)


<br>

---

<br>



### 2. B+ Tree Visualization & Search


*The "Show Tree" feature visualizes the balanced structure in memory. The Search function then uses this index to instantly locate and retrieve the persistent student file.*
![Tree and Search Demo](demo_tree_search.png.png)
<br>

---
<br>

## 🧠 System Architecture (How It Works)



This system separates **Indexing** from **Data Storage** to maximize efficiency. Below are diagrams visualizing the actual state of the system with sample data (IDs 111–1000).


<br>

### 1. Visualizing the Current B+ Tree State
* **Internal Nodes (Orange):** Act as "traffic signs" to guide traversal. They do not store data pointers.
* **Leaf Nodes (Blue):** Store the actual keys and link to the persistent text files. They are linked horizontally to allow efficient range queries.
<br>

```mermaid
stateDiagram-v2
    direction TB

    %% --- NEON THEME DEFINITIONS ---
    %% Root (Pink/Red - High Importance)
    classDef rootState fill:#2a0000,stroke:#ff0066,stroke-width:3px,color:#ff0066,font-weight:bold

    %% Leaves (Cyan - Standard Storage)
    classDef leafState fill:#001a1a,stroke:#00ffff,stroke-width:3px,color:#00ffff,font-weight:bold

    %% File (Green - Data found) with Dashed Border
    classDef fileState fill:#001a00,stroke:#00ff00,stroke-width:3px,color:#00ff00,stroke-dasharray: 5 5,font-weight:bold

    %% --- NODES ---
    state "Root: 333 , 666" as Root
    state "Leaf: 111, 222" as L1
    state "Leaf: 444, 555" as L2
    state "Leaf: 777, 888, 999, 1000" as L3
    state "File: 111.txt" as File1

    %% --- CONNECTIONS ---
    %% Tree Hierarchy
    Root --> L1: Keys < 333
    Root --> L2: Keys 333-666
    Root --> L3: Keys > 666

    %% File Pointer
    L1 --> File1

    %% Neighbor Links (Linked List)
    L1 --> L2: next
    L2 --> L3: next

    %% --- APPLY COLORS ---
    class Root rootState
    class L1,L2,L3 leafState
    class File1 fileState
```
<br>

### 2. Example Search Workflow (Searching ID: 888)




Following the B+ Tree search logic, here is the path taken to locate student ID 888:



```mermaid
stateDiagram-v2
    direction TB

    %% --- NEON THEME DEFINITIONS ---
    %% Cyan for "Path/Traversal" (matches the blue/cyan vibe of actions)
    classDef actionState fill:#001a1a,stroke:#00ffff,stroke-width:3px,color:#00ffff,font-weight:bold

    %% Bright Green for "Target/Success" (matches the success vibe)
    classDef successState fill:#001a00,stroke:#00ff00,stroke-width:3px,color:#00ff00,font-weight:bold

    %% --- DIAGRAM CONTENT ---
    state "1. Start at Root: 333, 666" as Step1
    state "2. Go Right > 666" as Step2
    state "3. Found 888 in Leaf" as Step3
    state "4. Read 888.txt from Disk" as Step4

    %% --- CONNECTIONS ---
    Step1 --> Step2
    Step2 --> Step3
    Step3 --> Step4

    %% --- APPLY COLORS ---
    %% Steps 1 and 2 are the 'Path'
    class Step1,Step2 actionState
    
    %% Steps 3 and 4 are the 'Target'
    class Step3,Step4 successState

```
<br>

### 3. Future Scenario: Node Splitting



With degree `t=3`, a node is full at 5 keys. The rightmost leaf currently holds 4 keys. Here is how the tree maintains balance if it overflows (e.g., adding IDs 1100 and 1200):



```mermaid
stateDiagram-v2
    direction TB

    %% --- NEON THEME DEFINITIONS ---
    %% Hot Pink for "Full/Danger"
    classDef fullState fill:#2a0000,stroke:#ff0066,stroke-width:3px,color:#ff0066,font-weight:bold
    
    %% Cyan for "Action"
    classDef actionState fill:#001a1a,stroke:#00ffff,stroke-width:3px,color:#00ffff,font-weight:bold
    
    %% Bright Green for "Success/Balanced"
    classDef successState fill:#001a00,stroke:#00ff00,stroke-width:3px,color:#00ff00,font-weight:bold

    %% --- DIAGRAM STRUCTURE ---
    state "Before Split (Node Full)" as Before {
        state "Keys: 777, 888, 999, 1000, 1100" as LeafContent
    }

    state "Action: Insert 1200 ->" as Action {
        state "Median key '999' moves up to Root" as StepContent
    }

    state "After Split (Balanced Again)" as After {
        state "New Root: 999" as Root
        state "Left: 777, 888" as Child1
        state "Right: 1000, 1100, 1200" as Child2
        Root --> Child1
        Root --> Child2
    }

    %% --- CONNECTIONS & APPLICATION ---
    Before --> Action
    Action --> After

    class Before fullState
    class Action actionState
    class After successState
```

---

<br>

## ⚡ Complexity Analysis



| Operation | Time Complexity | Explanation |
| --- | --- | --- |
| **Search** | `O(log n)` | Logarithmic time due to balanced tree height. |
| **Insert** | `O(log n)` | Includes tree traversal and potential node splitting. |
| **Space** | `O(n)` | Linear space relative to the number of records stored. |

---
<br>

## 🏁 How to Run



1. **Clone the repository:**
```bash
git clone [https://github.com/your-username/CPP-BPlusTree-DBMS.git](https://github.com/your-username/CPP-BPlusTree-DBMS.git)

```
<br>


2. **Compile the code:**
```bash
g++ main.cpp bptree.cpp -o dbms_app

```
<br>


3. **Run the executable:**
```bash
./dbms_app

```
<br>


*(Note: Ensure you have write permissions in the folder so the program can create the `.txt` data files.)*

---

## 📜 License

This project is licensed under the MIT License - see the [LICENSE](https://www.google.com/search?q=LICENSE) file for details.
