#include "Parser.h"

Parser::Parser(Graph *graph, HashTable *table) {
    this->graph = graph;
    this->vertices_table = table;
}

void Parser::importFiles(const string &vertices_path, int number_of_vertices, const string &edges_path) {

    // Build graph
    if (edges_path.empty()){
        importVerticesWithEdges(vertices_path);
    }
    else{
        importVertices(vertices_path,number_of_vertices);
        importEdges(edges_path);
    }
}

/**
 * @note @if number_of_vertices == -1, means that we explore all file
 */
void Parser::importVertices(const string &file_path, int number_of_vertices){
    fstream fin;
    fin.open(file_path,ios::in);

    int count = number_of_vertices;

    if (!fin.is_open()){
        cerr << "Unable to open file " << file_path << endl;
        exit(EXIT_FAILURE);
    }

    vector<string> row;
    string line;
    string word;
    getline(fin,line); // Discard first line of code
    while(getline(fin,line) && (count > 0 || count == -1)){
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

        // Parse the data received
        int id = stoi(row[0]);
        double latitude = stod(row[1]);
        double longitude = stod(row[2]);

        // Add vertex
        auto* coordinate = new Coordinate(latitude,longitude);
        auto* v = new Vertex(id,row[0],coordinate);
        graph->addVertex(v);

    }
    fin.close();
}

void Parser::importEdges(const string &file_path){
    fstream fin;
    fin.open(file_path, ios::in);

    if (!fin.is_open()){
        cerr << "Unable to open file " << file_path << endl;
        exit(EXIT_FAILURE);
    }

    vector<string> row;
    string line;
    string word;
    getline(fin,line); // Discard first line
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

        int origin_id = stoi(row[0]);
        int destination_id = stoi(row[1]);
        double distance = stod(row[2]);

    }
}

void Parser::importVerticesWithEdges(const string &file_path) {

}

