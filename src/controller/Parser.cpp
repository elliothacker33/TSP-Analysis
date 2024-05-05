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

bool isFirstLineToDiscard(const string& file_path){
    fstream fin;
    fin.open(file_path);
    if (!fin.is_open()){
        cerr << "Unable to open file " << file_path << endl;
        exit(EXIT_FAILURE);
    }
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
    fin.close();
    return true;
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

    bool firstLineToDiscard = isFirstLineToDiscard(file_path);
    if (firstLineToDiscard){
        getline(fin,line); // Discard first line
    }

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

        int origin_id = stoi(row[0]);
        int destination_id = stoi(row[1]);
        double distance = stod(row[2]);
        Vertex* origin = vertices_table->search(origin_id);
        Vertex* destination = vertices_table->search(destination_id);
        graph->addEdge(origin,destination,distance);


    }
}

void Parser::importVerticesWithEdges(const string &file_path) {
    fstream fin;
    fin.open(file_path,ios::in);

    if (!fin.is_open()){
        cerr << "Unable to open file " << file_path << endl;
        exit(EXIT_FAILURE);
    }

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
        if (row.size() == 5 || row.size() == 3) {
            int origin_id = stoi(row[0]);
            int destination_id = stoi(row[1]);
            double distance = stod(row[2]);
            auto* origin = new Vertex(origin_id, (row.size() == 5) ? row[3] : row[0], nullptr);
            auto* destination = new Vertex(destination_id, (row.size() == 5) ? row[4] : row[1], nullptr);
            graph->addVertex(origin);
            graph->addVertex(destination);
            graph->addEdge(origin, destination, distance);
        }

    }

}

