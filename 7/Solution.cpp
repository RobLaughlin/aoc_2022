#include "Solution.h"

Solution::Solution(const std::string& input_file, const size_t& filesystem_size) {
    // Set a pointer to the root of the "file system"
    std::ifstream input;
    input.open(input_file);

    if (!input.is_open()) {
        throw std::invalid_argument("Error opening input file");
    }
    
    FileNode* cwd = this->root; // Current working directory

    std::string line;
    while (std::getline(input, line)) {
        bool isCommand = line[0] == '$';
        bool isDir = (line.substr(0, 3) == "dir");

        if (isCommand) {
            if (line.substr(2, 2) == "cd") {
                std::string dir = line.substr(5);
                if (dir == "..") { 
                    cwd = cwd->get_parent(); 
                }
                else { 
                    /*
                        cd in this context acts as the "mkdir" command if the
                        directory doesn't exist.
                    */
                    FileNode* newCwd = cwd->find_child(dir);
                    if (newCwd == nullptr) {
                        newCwd = cwd->insert_file(dir, FileNode::DIR, 0);
                        
                    }
                    cwd = newCwd;
                }
            }
            continue;
        }
        else if (isDir) {
            std::string dirName = line.substr(4);
            cwd->insert_file(dirName, FileNode::DIR, 0);
        }
        else {
            std::smatch match;
            std::regex_search(line, match, std::regex("(\\d+) "));

            int fileSize = stoi(match.str());
            std::string fileName = match.suffix().str();
            cwd->insert_file(fileName, FileNode::FILE, fileSize);
        }
    }

    *this->root = *root->find_child("/");
    this->FILESYSTEM_SIZE = filesystem_size;
}

size_t Solution::sum_dir_sizes(size_t max_size) const {
    size_t size = 0;

    const std::vector<const FileNode*>* nodes = root->get_nodes();
    for (const FileNode* node : *nodes) {
        size_t node_size = node->get_size();
        FileNode::FileType node_type = node->get_file_type();

        // Node type must be a directory and must be <= max_size.
        if (node_size <= max_size && node_type == FileNode::DIR) {
            size += node_size;
        }
    }
    delete nodes;
    
    return size;
}

size_t Solution::smallest_dir_size(size_t space_required) const {
    const size_t total_size = root->get_size();
    const size_t free_space = this->FILESYSTEM_SIZE - total_size;
    size_t smallest_dir = std::numeric_limits<size_t>::max();

    const std::vector<const FileNode*>* nodes = root->get_nodes();
    for (const FileNode* node : *nodes) {
        size_t node_size = node->get_size();
        FileNode::FileType node_type = node->get_file_type();

        /*
            (1) File type must be DIR.
            (2) We must achieve the space requirement.
            (3) We must have a better directory choice available.
        */
        if (node_type == FileNode::DIR 
            && node_size+free_space >= space_required
            && node_size < smallest_dir) 
        {
            smallest_dir = node_size;
        }
    }
    delete nodes;

    // No such directory we can delete.
    if (smallest_dir == std::numeric_limits<size_t>::max()) { return -1; }

    return smallest_dir;
}