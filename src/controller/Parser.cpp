
/**
 * @file Parser.cpp -> Implementation file for parser
 */

/**< Project headers >**/
#include "Parser.h"
#include "../Exceptions/CustomError.h"
/**< STD headers >**/
#include <fstream>
#include <sstream>


void Parser::setNewTable(HashTable* table){
    this->vertices_table = table;
}
void Parser::setNewGraph(Graph* _graph){
    this->graph = _graph;
}
// Import files main function
void Parser::importFiles(const string &vertices_path, int number_of_vertices, const string &edges_path, bool symmetric_or_real) {
    try {
        // Build graph
        if (edges_path.empty()) {
            importVerticesWithEdges(vertices_path, symmetric_or_real);
        }
        else {
            importVertices(vertices_path, number_of_vertices);
            importEdges(edges_path, symmetric_or_real);
        }
    }
    catch (const CustomError &e){
        cerr << e.what() << endl;
        exit(EXIT_FAILURE);
    }
}

// Program that checks if the first line of a file is to discard
bool isFirstLineToDiscard(const string& file_path){
    // Open file
    fstream fin;
    fin.open(file_path);
    if (!fin.is_open()){
        throw CustomError("Error opening file",FILE_ERROR);
    }
    // Process file
    string line;
    string word;
    getline(fin,line);
    stringstream ss(line);
    if (getline(ss, word, ',')) {
        try {
            stoi(word);
            fin.close();
            return false;
        } catch (const invalid_argument& e) {
            fin.close();
            return true;
        } catch (const out_of_range& e) {
            fin.close();
            return true;
        }
    }
    // Close file
    fin.close();
    return true;
}

// Import only vertices
void Parser::importVertices(const string &file_path, int number_of_vertices){
    // Open file
    fstream fin;
    fin.open(file_path,ios::in);
    int count = number_of_vertices;

    if (!fin.is_open()){
        throw CustomError("Error opening file",FILE_ERROR);
    }

    // Process file
    vector<string> row;
    string line;
    string word;

    bool firstLineToDiscard = isFirstLineToDiscard(file_path);
    if (firstLineToDiscard){
        getline(fin,line); // Discard first line
    }

    while(getline(fin,line) && count > 0 ){
        row.clear();
        // Carriage return
        if (line.at(line.size()-1) == '\r'){
            line = line.substr(0,line.size()-1);
        }
        stringstream ss(line);
        while(getline(ss,word,',')){
            if (!word.empty()){
                row.push_back(word);
            }
        }
        if (row.empty()){
            continue;
        }

        if (row.size() == 3){
            int id = stoi(row[0]);
            double latitude = stod(row[1]);
            double longitude = stod(row[2]);

            // Add vertex
            auto* coordinate = new Coordinate(latitude,longitude);
            auto* v = new Vertex(id,row[0],coordinate);
            graph->addVertex(v);
            vertices_table->insertBucket(id,v);
        }
        count--;
    }
    // Close file
    fin.close();
}

void Parser::importEdges(const string &file_path, bool symmetric_or_real){
    // Open file
    fstream fin;
    fin.open(file_path, ios::in);

    if (!fin.is_open()){
        throw CustomError("Error opening file",FILE_ERROR);
    }

    // Process file
    vector<string> row;
    string line;
    string word;

    bool firstLineToDiscard = isFirstLineToDiscard(file_path);
    if (firstLineToDiscard){
        getline(fin,line); // Discard first line
    }

    while(getline(fin,line)){
        row.clear();
        // Carriage return
        if (line.at(line.size()-1) == '\r'){
            line = line.substr(0,line.size()-1);
        }
        stringstream ss(line);
        while(getline(ss,word,',')){
            if (!word.empty()){
                row.push_back(word);
            }
        }
        if (row.empty()){
            continue;
        }
        if (row.size() == 3) {
            int origin_id = stoi(row[0]);
            int destination_id = stoi(row[1]);
            double distance = stod(row[2]);
            Vertex* origin = vertices_table->search(origin_id);
            Vertex* destination = vertices_table->search(destination_id);
            graph->addEdge(origin, destination, distance);
            if (symmetric_or_real){
                graph->addEdge(destination,origin,distance);
            }
        }
    }
    // Close file
    fin.close();
}

void Parser::importVerticesWithEdges(const string &file_path, bool symmetric_or_real) {
    // Open file
    fstream fin;
    fin.open(file_path,ios::in);

    if (!fin.is_open()){
        throw CustomError("Error opening file",FILE_ERROR);
    }

    // Process file
    vector<string> row;
    string line;
    string word;
    bool firstLineToDiscard = isFirstLineToDiscard(file_path);
    if (firstLineToDiscard){
        getline(fin,line); // Discard first line
    }

    while(getline(fin,line)){
        row.clear();
        // Carriage return
        if (line.at(line.size()-1) == '\r'){
            line = line.substr(0,line.size()-1);
        }
        stringstream ss(line);
        while(getline(ss,word,',')){
            if (!word.empty()){
                row.push_back(word);
            }
        }
        if (row.empty()){
            continue;
        }
        // In this type of files Size 5 (have labels), Size 3 (don't have labels)
        if (row.size() == 5 || row.size() == 3) {
            int origin_id = stoi(row[0]);
            int destination_id = stoi(row[1]);
            double distance = stod(row[2]);

            // Origin vertex
            Vertex* findOrigin = vertices_table->search(origin_id);
            if (findOrigin == nullptr){
                findOrigin = new Vertex(origin_id, (row.size() == 5) ? row[3] : row[0], nullptr);
                graph->addVertex(findOrigin);
                vertices_table->insertBucket(origin_id,findOrigin);
            }

            // Destination vertex
            Vertex* findDestination = vertices_table->search(destination_id);
            if (findDestination == nullptr){
                findDestination = new Vertex(destination_id, (row.size() == 5) ? row[4] : row[1], nullptr);
                graph->addVertex(findDestination);
                vertices_table->insertBucket(destination_id,findDestination);
            }

            graph->addEdge(findOrigin, findDestination, distance);
            if (symmetric_or_real){
                graph->addEdge(findDestination,findOrigin,distance);
            }
        }

    }
    // Close file
    fin.close();

}

