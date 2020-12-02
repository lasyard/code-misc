/* Compile it with
 * cl /W3 /EHsc files_move.cpp
 */

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include <direct.h>
#include <io.h>

static int g_searchLine = 0;
static string g_searchString;
static string g_destPath = ".";

static void searchFile();

static void moveFile(const char *fileName)
{
    if (rename(fileName, (g_destPath + "\\" + fileName).c_str()) != 0) {
        cerr << "Cannot move file " << fileName << " to " << g_destPath << endl;
    }
}

static void processFile(const char *fileName)
{
    string buf;
    ifstream file;
    file.open(fileName, ios::in);
    if (!file.is_open()) {
        cerr << "Cannot open the file " << fileName << endl;
        return;
    }
    for (int i = 0; i < g_searchLine; i++)
        getline(file, buf);
    file.close();
    if (buf.find(g_searchString) == string::npos) {
        cout << "Skipped!" << endl;
        return;
    }
    cout << "Match found. Move file to " << g_destPath << endl;
    moveFile(fileName);
}

static void processSubDir(const struct _finddata_t &file)
{
    if (file.attrib == _A_SUBDIR) {
        if (strcmp(file.name, ".") != 0 && strcmp(file.name, "..") != 0) {
            cout << "Change to directory \\" << file.name << "." << endl;
            _chdir(file.name);
            searchFile();
            cout << "Change to upper directory." << endl;
            _chdir("..");
        }
    } else {
        const char *p = strrchr(file.name, '.');
        if (p != NULL && strcmp(p + 1, "txt") == 0) {
            cout << file.name << ": ";
            processFile(file.name);
        }
    }
}

static void searchFile()
{
    struct _finddata_t file;
    long hFile;
    hFile = _findfirst("*", &file);
    if (hFile == -1L) {
        cout << "No files in current directory!" << endl;
    } else {
        processSubDir(file);
        while (_findnext(hFile, &file) == 0)
            processSubDir(file);
    }
    _findclose(hFile);
}

int main(int argc, char *argv[])
{
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            ++i;
            if (i == argc) {
                cerr << "Lack string to search." << endl;
                return -1;
            }
            g_searchString = argv[i];
        } else if (strcmp(argv[i], "-l") == 0) {
            ++i;
            if (i == argc) {
                cerr << "Lack line number." << endl;
                return -1;
            }
            g_searchLine = atoi(argv[i]);
        } else if (strcmp(argv[i], "-d") == 0) {
            ++i;
            if (i == argc) {
                cerr << "Lack destination path." << endl;
                return -1;
            }
            g_destPath = argv[i];
        }
    }
    searchFile();
    return 0;
}
