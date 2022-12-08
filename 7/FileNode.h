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

    FileNode* get_parent() const;
    size_t get_size() const;
    FileType get_file_type() const;
    std::vector<const FileNode*>* get_nodes() const;

    FileNode* find(std::string filename) const;
    FileNode* insert_file(std::string filename, FileType file_type, size_t size=0);
    FileNode* remove();

    friend std::ostream& operator<<(std::ostream& os, const FileNode& file_node);
private:
    std::string filename;
    size_t size;
    FileType file_type;
    FileNode* parent;
    std::unordered_map<std::string, FileNode*> children;    
};