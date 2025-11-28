# Ransomware Simulator (Academic Project) :

This project is a **safe, controlled ransomware simulator** developed for academic and cybersecurity learning purposes.  
It demonstrates how real ransomware behaves at a conceptual level — specifically in terms of:

- File discovery  
- Simple encryption logic  
- File renaming  
- User access prevention  
- Alert messaging  

⚠️ **This project does NOT contain harmful or deployable ransomware code.  
All real malicious logic has been removed for safety.**  
Only pseudo-code and structural explanations are provided.

---

## 🎯 Project Goals

- Understand how ransomware locates and processes files  
- Study encryption concepts (XOR-based simulation)  
- Explore malicious behavior patterns safely  
- Learn how Windows API functions work in malware simulations  
- Develop secure coding habits and safe testing practices  

---

## 🧩 High-Level Architecture




# Pseudo-Code :



# SAFETY NOTICE:
# This is NOT real ransomware code. 
# This is HIGH-LEVEL pseudo-code for academic understanding only.

function simulate_file_encryption(file_path):
    open the file
    read file data into memory
    for each byte in data:
        apply a placeholder "encryption" (example: XOR with a dummy key)
        # actual malicious encryption removed
    write modified data back to file
    rename file by adding ".locked" extension
    print "File encrypted (simulated)"

function is_file_locked(file_path):
    if file_path ends with ".locked":
        return true
    else:
        return false

function show_warning_popup():
    display warning message:
        "Your files have been encrypted (simulation)."

function simulate_user_open(file_path):
    if is_file_locked(file_path):
        show_warning_popup()
    else:
        print "File is accessible"

function process_directory(target_folder):
    list all files in folder
    for each file in folder:
        simulate_file_encryption(file)

function main():
    set target_folder to a test directory
    process_directory(target_folder)
    simulate_user_open("example.txt.locked")




# DESIGN FLOW : 



                [ Start Simulation ]
                         │
                         ▼
              [ Scan Target Directory ]
                         │
                         ▼
             [ Identify All Normal Files ]
                         │
                         ▼
             [ Simulated Encryption Loop ]
        ┌────────────────────────────────────┐
        │  - Read file into memory           │
        │  - Apply placeholder transformation│
        │  - Write modified data             │
        └────────────────────────────────────┘
                         │
                         ▼
                [ Rename to *.locked ]
                         │
                         ▼
         [ User Attempts to Open File ]
                         │
            ┌────────────┴──────────────┐
            │                           │
            ▼                           ▼
     [ If .locked ]               [ If normal file ]
  Show warning popup           Allow access message
            │                           │
            └────────────┬──────────────┘
                         ▼
                [ Simulation Complete ]


# LEARNING OUTCOMES :



