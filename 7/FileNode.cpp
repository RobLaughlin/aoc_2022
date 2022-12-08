#include "FileNode.h"

FileNode::FileNode(std::string filename, FileType file_type, size_t size, FileNode* parent) {
    this->filename = filename;
    this->size = size;
    this->file_type = file_type;
    this->parent = parent;
    this->children = std::unordered_map<std::string, FileNode*>();
}

FileNode* FileNode::get_parent() const {
    return this->parent;
}

size_t FileNode::get_size() const {
    return this->size;
}

FileNode::FileType FileNode::get_file_type() const {
    return this->file_type;
}

std::vector<const FileNode*>* FileNode::get_nodes() const {
    std::vector<const FileNode*>* node_list = new std::vector<const FileNode*>();
    std::stack<const FileNode*> nodes = std::stack<const FileNode*>();
    nodes.push(this);

    while (nodes.size() > 0) {
        const FileNode* node = nodes.top();
        nodes.pop();

        node_list->push_back(node);
        for (auto& it : node->children) {
            nodes.push(it.second);
        }
    }

    return node_list;
}

FileNode* FileNode::find(std::string filename) const {
    FileNode* file_node = nullptr;

    auto ptr = this->children.find(filename);
    if (ptr != this->children.end()) {
        file_node = this->children.at(filename);
    }

    return file_node;
}

FileNode* FileNode::insert_file(std::string filename, FileType file_type, size_t size) {
    if (this->children.find(filename) != this->children.end()) {
        throw std::invalid_argument(filename + " already exists under this directory.");
    }

    FileNode* inserted = new FileNode(filename, file_type, size, this);
    this->children[filename] = inserted;

    // Update the sizes
    FileNode* next = this;
    while (next != nullptr) {
        next->size += size;
        next = next->get_parent();
    }
    return inserted;
}

FileNode* FileNode::remove() {
    // Delete all nodes depth-first
    std::stack<FileNode*> delete_stack = std::stack<FileNode*>();
    FileNode* parent = this->parent;

    delete_stack.push(this);
    while (delete_stack.size() > 0) {
        FileNode* node = delete_stack.top();
        delete_stack.pop();

        for (auto const& [child_filename, child] : node->children) {
            child->parent = nullptr;
            delete_stack.push(child);
        }

        if (node->parent != nullptr) {
            node->parent->children.erase(node->filename);
        }
        
        delete node;
    }
    
    return parent;
}

std::ostream& operator<<(std::ostream& os, const FileNode& file_node) {
    struct Elem {
        FileNode node;
        int depth;
    };

    std::stack<Elem> nodes = std::stack<Elem>();
    nodes.push(Elem{file_node, 0});

    while (nodes.size() > 0) {
        Elem elem = nodes.top();
        FileNode node = elem.node;
        int depth = elem.depth;
        nodes.pop();
        
        std::stringstream filetype;
        if (node.file_type == FileNode::DIR) {
            filetype << "(dir)";
        }
        else {
            filetype << "(file, size=" << node.size << ')'; 
        }

        std::string spacing(2*depth, ' ');
        os << spacing << "- " << node.filename << ' ' << filetype.str() << std::endl;

        for (auto& it : node.children) {
            nodes.push(Elem{*it.second, depth+1});
        }
    }

    return os;
}