#pragma once
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include <stack>

class FileNode {
public:
    enum FileType {FILE, DIR};

    FileNode(std::string filename, FileType file_type, size_t size=0, FileNode* parent=nullptr);
    
    const std::unordered_map<std::string, FileNode*>& get_files() const;
    const size_t& get_size() const;
    const std::string& get_filename() const;
    const FileType& get_file_type() const;
    const std::vector<const FileNode*>* get_nodes() const;

    FileNode* get_parent() const;

    // Returns the found child node or nullptr if not found.
    FileNode* find_child(std::string filename) const;

    // Returns newly inserted file node.
    FileNode* insert_file(std::string filename, FileType file_type, size_t size=0);

    // Returns parent of current node after removal.
    FileNode* remove(); 

    friend std::ostream& operator<<(std::ostream& os, const FileNode& file_node);
private:
    std::string filename;
    size_t size;
    FileType file_type;
    FileNode* parent;
    std::unordered_map<std::string, FileNode*> children;    
};