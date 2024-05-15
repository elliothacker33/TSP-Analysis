#ifndef TSP_ANALYSIS_MENU_H
#define TSP_ANALYSIS_MENU_H

/**
* @file Menu.h
* @brief This file contains the Menu header.
*/

// Project headers
#include "../controller/Manager.h"
// Standard Library Headers
#include <stack>

typedef vector<string> Folder;
using namespace std;

/**
 * @class Menu
 * @brief This is the view interface to access functionalities on manager.
 *
 * This class represents a view.
 */

class Menu{
public:
    /**
    * @brief Destructor for Menu.
    */
    ~Menu();

    /**
     * @brief Constructor for Menu.
     * @param manager Pointer to a Manager instance.
     */
    explicit Menu(Manager* manager);

    /**
     * @brief Displays the main view.
     */
    void mainMenu();


    /**
     * @brief Choose the type of the data set
     */
     void dataSetMenu();

    /**
     * @brief Shutdowns view.
     */
    void exitMenu();

    /**
     * @brief Returns to the previous view.
     */
    void goBack();


    /**
     * @brief Choose toy graph
    */
    void toyMenu();

    /**
     * @brief Choose medium graph
    */
     void mediumMenu();

     /**
      * @brief Choose real world graph
     */
      void realWorldMenu();
      /**
       * @bried Choose your own graph
       */
      void yourDataSetMenu();

    /**
     * @brief Displays the algorithm view.
     */
    void algorithmMenu();

    void extraMenu();
private:
    /**
    * @brief A stack that stores pointers to visited Menus.
    */

    stack<void(Menu::*)()> menuStack;
    /**
     * @brief Pointer to a manager instance.
     */
    Manager* manager;
    int mode;

    /**< Auxiliary functions >**/
    /**
    * @brief Removes leading and trailing spaces from a string.
    * @param input The input string to process.
    * @return A string with leading and trailing spaces removed.
    */
    static string removeLeadingTrailingSpaces(const string& input);

    static void displayResult(const Result& r);

    static Folder getFolderContents(const string& path);

    static Folder getFoldersInFolder(const string& path);

    static bool askNumberOfVertices(int * n);
    /**
     * @brief Retrieves a number input within a specified range.
     * @param minInput The minimum allowed input value.
     * @param maxInput The maximum allowed input value.
     * @param option Pointer to store the selected option.
     * @return True if the input is successfully obtained, false otherwise.
     */
    static bool getNumberInput(int* option,int maxInput,int minInput = 1);

    static bool isNumber(string number);
    void chooseVertex(int& vertex_id);

    /* Get examples of input */
    /**
     * @brief Retrieves examples of vertices.
     */
    void getVertexExamples();


};

#endif //TSP_ANALYSIS_MENU_H
