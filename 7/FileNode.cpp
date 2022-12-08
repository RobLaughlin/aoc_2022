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

const std::unordered_map<std::string, FileNode*>& FileNode::get_files() const {
    return this->children;
}

const size_t& FileNode::get_size() const {
    return this->size;
}

const std::string& FileNode::get_filename() const {
    return this->filename;
}

const FileNode::FileType& FileNode::get_file_type() const {
    return this->file_type;
}

const std::vector<const FileNode*>* FileNode::get_nodes() const {
    // Traverse all the nodes using a stack and return a list of all nodes
    std::vector<const FileNode*>* node_list = new std::vector<const FileNode*>();
    std::stack<const FileNode*> nodes = std::stack<const FileNode*>();

    nodes.push(this);
    while (nodes.size() > 0) {
        const FileNode* node = nodes.top();
        nodes.pop();

        node_list->push_back(node);
        for (auto& [_ , child] : node->children) {
            nodes.push(child);
        }
    }

    return node_list;
}

FileNode* FileNode::find_child(std::string filename) const {
    FileNode* child = nullptr;

    auto ptr = this->children.find(filename);
    if (ptr != this->children.end()) {
        child = this->children.at(filename);
    }

    return child;
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

    // Return parent of this node at the end
    FileNode* parent = this->parent;

    delete_stack.push(this);
    while (delete_stack.size() > 0) {
        FileNode* node = delete_stack.top();
        delete_stack.pop();

        // Sever all parent connections
        if (node->parent != nullptr) {
            node->parent->children.erase(node->filename);
            node->parent = nullptr;
        }

        // Sever all child connections
        std::unordered_map<std::string, FileNode*> children = node->children;
        for (auto const& [child_filename, child] : children) {
            node->children.erase(child_filename);
            child->parent = nullptr;
            delete_stack.push(child);
        }

        delete node;
    }
    
    return parent;
}

std::ostream& operator<<(std::ostream& os, const FileNode& file_node) {
    struct Elem {
        FileNode node;
        int depth; // Need depth to determine spacing in terminal
    };

    std::stack<Elem> nodes = std::stack<Elem>();
    nodes.push(Elem{file_node, 0});

    while (nodes.size() > 0) {
        Elem elem = nodes.top();
        FileNode node = elem.node;
        int depth = elem.depth;
        nodes.pop();
        
        std::stringstream filetype;
        if (node.file_type == FileNode::DIR) { filetype << "(dir)"; }
        else { filetype << "(file, size=" << node.size << ')'; }

        std::string spacing(2*depth, ' ');
        os << spacing << "- " << node.filename << ' ' << filetype.str() << std::endl;

        for (auto const& [_, child] : node.children) {
            nodes.push(Elem{*child, depth+1});
        }
    }

    return os;
}