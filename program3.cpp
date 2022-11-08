/****************************
 *
 * Program 3: Password Check
 *
 * Course: CS 141, Fall 2022
 * System: g++ using VS Code
 * Author: Ava Enke, starter code provided by Dr. Sara Riazi
 *
 * *** **********************/

#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const string rule_msg_1 =
    "The selected password must be at least eight characters long.";
const string rule_msg_2 =
    "The selected password must have at least one uppercase letter.";
const string rule_msg_3 =
    "The selected password must have at least one lowercase letter.";
const string rule_msg_4 = "The selected password must have at least one digit.";
const string rule_msg_5 = "The selected password must have at least one of "
                          "special characters: [@,!,#,^,&,*,$]";
const string rule_msg_6 = "The selected password has been leaked.";
const string rule_msg_7 =
    "The selected password cannot contain a dictionary word.";

/* rule 1 check, takes password input and checks if it meets length
 requirements, returns true if the rule fails */
bool rule1(string password) {

  if (password.size() < 8) {
    return true;
  }

  else {
    return false;
  }
}

/* rule 2 check, takes password as input and checks if uppercase letter is
 present, returns true if this rule fails */
bool rule2(string password) {

  bool flag2 = true;

  for (int i = 0; i < password.size(); i++) {

    if (isupper(password.at(i))) {
      flag2 = false;
      break;
    }
  }
  return flag2;
}

/* rule 3 check, takes password as input and checks if lowercase letter is
 present, if none present: the rule fails and returns true */
bool rule3(string password) {

  bool flag3 = true;

  for (int i = 0; i < password.size(); i++) {

    if (islower(password.at(i))) {
      flag3 = false;
      break;
    }
  }
  return flag3;
}

/* rule 4 check, takes password as input and checks if number/digit is present,
 if none are found: the rule fails and true */
bool rule4(string password) {

  bool flag4 = true;

  for (int i = 0; i < password.size(); i++) {
    if (isdigit(password.at(i)) == true) {

      flag4 = false;
      break;
    }
  }

  return flag4;
}

/* rule 5 check, takes password as input, checks if special characters are
 present throughout, if none are found: the rule fails and returns true */
bool rule5(string password) {

  bool flag5 = true;

  for (int i = 0; i < password.size(); i++) {
    if (password.at(i) == '@' || password.at(i) == '!' ||
        password.at(i) == '#' || password.at(i) == '^' ||
        password.at(i) == '&' || password.at(i) == '*' ||
        password.at(i) == '$') {

      flag5 = false;
      break;
    }
  }
  return flag5;
}

/* rule 6 check, takes txt file and string as input, alters string accordingly, inputs txt file into a vector, alters vector accordingly, uses a binary search to find equivalences in the altered vector strings and the single string. If after binary search is complete if the two are equivalent: returns true */
bool compare(string leaked_password_file, string password) {
  vector<string> leaked;
  string str2, tempPass;
  bool found = false;
  int mid;

  //altering password to all lowercase and no digits 
  for (int i = 0; i < password.size(); i++) {
    password[i] = tolower(password[i]);

    if (isalnum(password[i])) {
      tempPass += password[i];
    }
  }
  
  //file operations: opens file takes strings from file to input to the leaked vector 
  ifstream fin;
  fin.open(leaked_password_file);

  if (fin.is_open()) {
    while (!fin.eof()) {
      fin >> str2;
      leaked.push_back(str2);
    }
  }


  int size = leaked.size();
  int low = 0;
  int high = size - 1;
  
  //binary search 
  while (low <= high) {
    mid = (high + low) / 2;

    //evaluates if leaked[mid] is substring of tempPass
    if(leaked[mid].find(tempPass) != string::npos){
     for(int i = 0; i < leaked[mid].length(); i++){
       if(!isalnum(leaked[mid][i])){
         leaked[mid].erase(i);
       }
     }
   }
    
    
    if (tempPass == leaked[mid]) { 
      cout << rule_msg_6 << endl;
      found = true;
      break;
    }

    else if (tempPass < leaked[mid]) {
      high = mid - 1;
    }

    else {
      low = mid + 1;
    }
  }
  return found;
}

/* rule 7 check, uses txt file and string for input, alters each string accordingly, enters the elements of the txt file into a vector, checks if any item in the vector is a subtring of the other string (password), if substring is found: returns true
*/
bool rule7(string english_word_file, string password) {
  bool found = false;
  vector<string> words;
  string str2;
  
  //file operations: opens file and inputs each element into a vector 
  fstream fin;
  fin.open(english_word_file, ios::in);

  if (fin.is_open()) {
    while (!fin.eof()) {
      fin >> str2;
      words.push_back(str2);
    }
    fin.close();
  }

  //altering password to all lowercase to more easily check subsets 
  for (int i = 0; i < password.size(); i++) {
    password[i] = tolower(password[i]);
  }

  //looping through each element in vector to check if subset position is found 
  for (int i = 0; i < words.size() - 1; i++) {
    if (password.find(words.at(i)) != string::npos) {
      cout << rule_msg_7 << endl;
      found = true;
      break;
    }
  }
  return found;
}


/****
 * Runs the main part of the program
 ****/
int run(string leaked_password_file, string english_word_file) {
  // put all the functions inside run and declare them here

  string password;
  bool flagLength = false;
  bool flagUpper = false;
  bool flagLower = false;
  bool flagDigit = false;
  bool flagSpecial = false; 
  bool flagLeaked = false;
  bool flagEngl = false;

  cout << "Enter password: ";
  cin >> password;
  

  // rule 1 function call and checks accuracy of password length
  if (rule1(password) == true) {
    cout << rule_msg_1 << endl;
    flagLength = true;
  }

  // rule 2 function call and checks accuracy of uppercase letters
  if (rule2(password) == true) {
    cout << rule_msg_2 << endl;
    flagUpper = true;
  }

  // rule 3 function call and checks accuracy of lowercase letters
  if (rule3(password) == true) {
    cout << rule_msg_3 << endl;
    flagLower = true;
  }

  // rule 4 function call and checks accuracy of password digits
  if (rule4(password) == true) {
    cout << rule_msg_4 << endl;
    flagDigit = true;
  }

  // rule 5 function call, checks accuracy of password characters
  if (rule5(password) == true) {
    cout << rule_msg_5 << endl;
    flagSpecial = true;
  }

  
    // if all any of the initial five rules is broken and flagged the password will reject
  if (flagUpper == true || flagLower == true || flagDigit == true ||  flagSpecial == true || flagDigit == true ) {
    cout << "Password rejected!";

  }

  //the first five rules were passed so the final two are now checked
  else {
    if (compare(leaked_password_file, password) != false) {
      cout << "Password rejected!" << endl;
    }

    else if (rule7(english_word_file, password) != false) {
      cout << "Password rejected!" << endl;
    } 
      
    else {
      cout << "Password accepted!" << endl;
    }
  }
  return 0;
}

int main() {
  /** Change the address of the files appropriatly based on your local machine.
   * This main function will be replaced during testing. Do not add any line of
   *code to the main function
   **/

  string leaked_password_file =
      "alleged-gmail-passwords.txt"; // change this based on the location of the
                                     // file on your machine
  string english_word_file = "5_words.txt"; // change this based on the location
                                            // of the file on your machine
  run(leaked_password_file, english_word_file);
  return 0;
}
