#include "HashTable.h"

bool HashBucket::operator==(const HashBucket& bucket) const {
    return this->id == bucket.getId();
}

int HashBucket::getId() const {
    return this->id;
}

Vertex* HashBucket::getVertex() const{
    return this->vertex;
}

HashTable::HashTable(int real_capacity) {
    capacity = real_capacity*2; // 2 factor on table capacity for better results
    table = new HashBucket * [capacity];
    for (int i = 0; i < capacity; i++){
        table[i] = nullptr;
    }
    dummy = new HashBucket(-1, nullptr);
}

void HashTable::insertBucket(int _id, Vertex* _vertex) {
    auto* temp_bucket= new HashBucket(_id, _vertex);
    int hash_id = getHash(_id);

    while (table[hash_id] != nullptr && table[hash_id]->getId() != _id && table[hash_id]->getId() != -1) {
        hash_id++;
        hash_id%= capacity;
    }

    if (table[hash_id] == nullptr || table[hash_id]->getId() == -1)
        size++;

    table[hash_id] = temp_bucket;
}

void HashTable::deleteBucket(int _id){
    int hash_id = getHash(_id); // Get hash for deletion

    while(table[hash_id] != nullptr){
        if (table[hash_id]->getId() == _id) {
            table[hash_id] = dummy;
            size--;
            return;
        }
        hash_id++;
        hash_id %= capacity;
    }
}

Vertex* HashTable::search(int _id){
    int hash_id = getHash(_id);
    int counter = 0;

    while (table[hash_id]!= nullptr) {

        if (counter++ > capacity)
            return nullptr;

        if (table[hash_id]->getId() == _id)
            return table[hash_id]->getVertex();

        hash_id++;
        hash_id %= capacity;
    }
    return nullptr;
}

int HashTable::getHash(int id) const{
    return id%capacity;
}

int HashTable::getSize() const {
    return size;
}

bool HashTable::isEmpty() const {
    if (size == 0)
        return true;
    return false;
}

HashTable::~HashTable() {
    for(int i = 0; i < capacity; i++){
        if (table[i] != nullptr && table[i] != dummy) {
            delete table[i];
        }
    }
    delete [] table;
    delete dummy;
}


