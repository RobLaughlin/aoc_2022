#include "FileNode.h"
#include <fstream>
#include <iostream>
#include <regex>
#include <limits>

using namespace std;

static const string INPUT_FILENAME = "input.txt";

FileNode* preprocess(const string &input_file) {
    ifstream input;
    input.open(input_file);

    if (!input.is_open()) {
        throw invalid_argument("Error opening input file");
    }

    FileNode* root = new FileNode("/", FileNode::DIR, 0);
    FileNode* cwd = root;

    string line;
    while (getline(input, line)) {
        bool isCommand = line[0] == '$';
        bool isDir = (line.substr(0, 3) == "dir");

        if (isCommand) {
            if (line.substr(2, 2) == "cd") {
                string dir = line.substr(5);
                if (dir == "..") { 
                    cwd = cwd->get_parent(); 
                }
                else { 
                    FileNode* newCwd = cwd->find(dir);
                    if (newCwd == nullptr) {
                        newCwd = cwd->insert_file(dir, FileNode::DIR, 0);
                        
                    }
                    cwd = newCwd;
                }
            }
            continue;
        }
        else if (isDir) {
            string dirName = line.substr(4);
            cwd->insert_file(dirName, FileNode::DIR, 0);
        }
        else {
            smatch match;
            regex_search(line, match, regex("(\\d+) "));

            int fileSize = stoi(match.str());
            string fileName = match.suffix().str();
            cwd->insert_file(fileName, FileNode::FILE, fileSize);
        }
    }

    return root;
}

size_t get_sizes(FileNode* root, size_t max_size=numeric_limits<size_t>::max()) {
    size_t size = 0;

    vector<const FileNode*>* nodes = root->get_nodes();
    for (const FileNode* node : *nodes) {
        size_t node_size = node->get_size();
        FileNode::FileType node_type = node->get_file_type();
        if (node_size <= max_size && node_type == FileNode::DIR) {
            size += node_size;
        }
    }

    delete nodes;
    return size;
}

size_t smallest_dir_required(FileNode* root, size_t size_filesystem, size_t space_required) {
    const size_t total_size = root->get_size();
    const size_t free_space = size_filesystem - total_size;

    size_t smallest_dir = numeric_limits<size_t>::max();
    vector<const FileNode*>* nodes = root->get_nodes();
    for (const FileNode* node : *nodes) {
        size_t node_size = node->get_size();
        FileNode::FileType node_type = node->get_file_type();
        if (node_type == FileNode::DIR 
            && node_size+free_space >= space_required
            && node_size < smallest_dir) 
        {
            smallest_dir = node_size;
        }
    }

    // No such directory we can delete.
    if (smallest_dir == numeric_limits<size_t>::max()) { return -1; }

    return smallest_dir;
}

int main() {
    const size_t MAX_SIZE = 100000;
    const size_t SIZE_FILESYSTEM = 70000000;
    const size_t SPACE_NEEDED = 30000000;

    FileNode* root = preprocess(INPUT_FILENAME);
    root = root->find("/");

    cout << *root << endl;
    cout << "Sum of directory sizes under " << MAX_SIZE << ": " << get_sizes(root, MAX_SIZE) << endl;
    cout << "Size of the smallest directory required to achieve the space requirement: ";
    cout << smallest_dir_required(root, SIZE_FILESYSTEM, SPACE_NEEDED) << endl;
    return 0;
}