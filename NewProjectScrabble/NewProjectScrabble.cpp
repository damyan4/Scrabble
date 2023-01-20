/**
*
* Solution to course project # <номер на вариант>
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Damyan Georgiev
* @idnumber 4MI0600145
* @compiler VC
*
* Main file
*
*/


#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;
int const LETTERS_MAX_SIZE = 100;

int getLengthOfArray(const char* arr)
{
    int size = 0;
    while (arr[size++] != '\0');
    size--;
    return size;
}
bool findWord(const char* word, vector<string> dictionary)
{
    for (size_t i = 0; i < dictionary.size(); i++)
    {
        if (dictionary[i] == word)
        {
            return true;
        }
    }
    return false;
}
void initializeVector(vector<string>& v1)
{
    ifstream file;
    file.open("manywords.txt");
    string line;
    
    while (!file.eof())
    {
        getline(file, line);
    	v1.push_back(line);
    }
    file.close();
}
void recordRandomValues(char* arr, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = 'a' + rand() % 26;
    }
}
void printArray(const char* arr, int size)
{
    for (size_t i = 0; i < size; i++)
    {
        cout << arr[i] << ' ';
    }
}
void deleteLetterFromWord(char* word, unsigned int& index)
{
    while (word[index] != '\0')
    {
        word[index] = word[index + 1];
        index++;
    }
}
void fillDeletedWordAgain(char* word, const char* copy_word)
{
    for (size_t i = 0; copy_word[i] != '\0'; i++)
    {
        word[i] = copy_word[i];
    }
}
void copyArray(const char* word,char* copy_word)
{
    for (size_t i = 0; word[i]!='\0'; i++)
    {
        copy_word[i] = word[i];
    }
}
bool checkIfWordContainsLettersFromArray(const char* lettersArr,char* userWord,int size_word)
{
    int indexOfCoincidence = 0;
    char copy_userWord[LETTERS_MAX_SIZE] = {};

    copyArray(userWord,copy_userWord);

    for (size_t i = 0; lettersArr[i] != '\0'; i++)
    {
        for (int j = 0; userWord[j] != '\0'; j++)
        {
            if (userWord[j] == lettersArr[i])
            {
                indexOfCoincidence++;
                unsigned int k = j;
                deleteLetterFromWord(userWord, k);
                break;
            }
        }

    }
    fillDeletedWordAgain(userWord, copy_userWord);
    if (indexOfCoincidence == size_word)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void playGame(unsigned int number_of_words, unsigned int number_of_rounds)
{
    vector<string> dictionary;
    initializeVector(dictionary);

    
    char lettersArray[LETTERS_MAX_SIZE] = {};
    char userWordArray[LETTERS_MAX_SIZE] = {};

    int players_score = 0;
    bool isInvalidWord = false;

    for (size_t i = 0; i < number_of_rounds; i++)
    {
        if (!isInvalidWord)
        {
            recordRandomValues(lettersArray, number_of_words);
            cout << "Round " << i + 1 << ". Available letters: ";
        }

        printArray(lettersArray, number_of_words);
        cout << endl;
        cin >> userWordArray;
        int sizeOfWord = getLengthOfArray(userWordArray);

        bool ifLettersInWord = checkIfWordContainsLettersFromArray(lettersArray, userWordArray, sizeOfWord);
        bool isWordInDictionary = findWord(userWordArray, dictionary);

        if (ifLettersInWord && isWordInDictionary)
        {
            players_score += sizeOfWord;
            cout << "+" << sizeOfWord << " points\n\n";
            isInvalidWord = false;
        }
        else if (strcmp(userWordArray, "!skip") == 0)
        {
            cout << "Skipping Round " << i + 1 << "...\n\n";
            isInvalidWord = false;
        }
        else
        {
            cout << "Invalid word. Try again with: ";
            i--;
            isInvalidWord = true;
        }
    }
    cout <<"Congratulations!\n" << "Your Total Score is " << players_score << " points.\n\n";
}
void addNewWordInTheFile(const char* word)
{
    ofstream file;
    file.open("manywords.txt", ios::app);
    file << word << endl;	
    file.close();
}
int main()
{
    srand(time(nullptr));
    int rounds = 10;
    int words = 10;
    int const ADDWORD = 100;
    char add_word[ADDWORD] = "";
    char choice;
    cout << "Scrabble game\n" << endl;
    do
    {
	     cout << "1. Start a new game\n" << "2. Settings\n"  << "3. Add a new word\n" << "4. Exit the app\n";
         cin >> choice;
         while (choice < '1' || choice>'4')
         {
             cout << "Please enter a valid value: " << endl;
             cin >> choice;
         }

    	switch (choice)
    	{
	         case '1': 
         		playGame(words, rounds);
         		break;
                
	         case '2':
         		cout <<"\nSettings:\n" << "a) Change number of displayed letters\n" << "b) Change number of rounds\n";
	            cin >> choice;
	            if (choice=='a')
	            {
	                cout << "Number of letters: ";
                    cin >> words;
                    while (words < 1 || words > 50)
                    {
                        cout << "Please enter a valid number between 1 and 50: " << endl;
                        cin >> words;
                    }
                    cout << "The number of letters is updated!" << endl;
	            }
	            else if (choice == 'b')
	            {
	                cout << "Number of rounds: ";
	                cin >> rounds;
                    while (rounds < 1 || rounds > 20)
                    {
                        cout << "Please enter a valid number between 1 and 20: " << endl;
                        cin >> rounds;
                    }
                    cout << "The number of rounds is updated!" << endl;
	            }
	            break;

	         case '3':
	             cout << "Add new word: ";
	             cin >> add_word;
	             addNewWordInTheFile(add_word);
                 cout << "Word added successfully!" << endl;
	             break;

	         case '4': 
	             cout << "Thank you for playing Scrabble!" << endl;
	             return 0;
    	}
         
    }
    while (true);
   
    return 0;
    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
