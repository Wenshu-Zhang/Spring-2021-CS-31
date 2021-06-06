#include <cstring>
#include <iostream>
#include <cctype>
#include <fstream>
using namespace std;

int fill(int lineLength, istream& inf, ostream& outf);


int main() {
    int len;
    cin >> len;
    
    ifstream infile("/Users/clairezhang/Desktop/input.txt");
    if ( ! infile )                // Did opening the file fail?
        {
            cerr << "Error: Cannot open input.txt!" << endl;
        }
    
    
    ofstream outfile("/Users/clairezhang/Desktop/results.txt");   // outfile is a name of our choosing.
        if ( ! outfile )           // Did the creation fail?
        {
            cerr << "Error: Cannot create results.txt!" << endl;
        }
    
    int returnCode = fill(len, infile, outfile);
    cerr << returnCode << endl;
    

}


int fill(int len, istream& inf, ostream& outf){
    if (len < 1)
        return 2;
    
    char c;
    char word[1000] = "";       //for storing the words
    int pos = 0;
    int wordNum = 0;
    char line[10000] = "";      //for keeping track of the length of the line and determining whether to add a newline or not
    int count = 0;
    bool tooLong = false;
    
    
    for (;;){
        while(inf.get(c)){      //get a word
            if (!isspace(c)){       //if not a space, c is a part of a word
                word[pos] = c;      //store c into the word c string
                pos++;      //proceed to the next character
            }
            else{       //if a space, the end of a word and the start of another
                pos++;      //proceed to the next character
                break;      //proceed to processing the word
            }
        }
        
        if (strcmp(word, "") != 0)
            wordNum++;
        if (inf.eof() && strcmp(line, "") == 0 && strcmp(word, "") == 0)      //if end of the file and the line and the word c string have nothing, it must be that the input file has nothing in it
            return 0 ;      //therefore, return 0 and print nothing as the spec says
        if (strlen(word) > len){     //if a word length is greater than the desired line length
            tooLong = true;
            if (wordNum != 1)
                outf << '\n';       //start the word on a new line
            memset(line,0,strlen(line));
            int i = 0;
            for (;; i++){       //check every element of the c string
                if (word[i] == '\0'){      //if the end of the word is reached
                    outf << '\n';       //the word ends
                    memset(word,0,strlen(word));
                    break;
                }
                outf << word[i];        //if the end is not reached, still output the word
                if ((i+1)%len == 0 && word[i+1] != '\0')     //split the word onto different lines
                    outf << '\n';
                }
        }
        if (strcmp(word, "#P#") != 0)       //if a word is not "#P#", reset count to 0
            count = 0;
        if (strcmp(word, "#P#") == 0){      //if a word is "#P#"
            if (count == 0 && wordNum != 1 && !inf.eof()){        //and count is 0 (it's the first paragraph break)
                outf << '\n' << '\n';       //make a paragraph break
                memset(word,0,strlen(word));        //do not print "#P#", and empty word
                memset(line,0,strlen(line));        //Since a newline starts, empty line
            }
            count++;        //to indicate that a paragraph break is encountered and to avoid processing more than one paragraph break if there are consecutive ones
        }
        else if(strcmp(line, "") == 0){    //if the start of a line, print the word directly
            outf << word;
            strcat(line, word);     //add the word to line to keep track of its size
        }
        else if (line[strlen(line)-1] == '.' || line[strlen(line)-1] == '?'){
            //if a "." or a "?" is encountered, print two spaces before the word
            if(strcmp(word, "") != 0 && strlen(line)+strlen(word)+2 <= len){
                //if adding two spaces and the word does not exceed len, print them
                outf << ' ' << ' ' << word;
                strcat(line, "  ");     //add the spaces to line to keep track of its size
                strcat(line, word);     //add the word to line to keep track of its size
            }
            else if (strcmp(word, "") != 0){
                //if adding two spaces and the word does exceed len, print a newline and then the word to the new line
                outf << '\n'<< word;;
                memset(line,0,strlen(line));        //empty the previous line
                strcat(line, word);     //add the word to line, and keep track of the new line
            }
        }
        else if (strcmp(word, "") != 0 && strlen(line)+strlen(word)+1 <= len){
            //if the word does not end in "." or "?" and if adding one space and the word does not exceed len, print only one space before the word
            outf << ' ' << word;
            strcat(line, " ");      //add the space to line to keep track of its size
            strcat(line, word);     //add the word to line to keep track of its size
        }
        else if (strcmp(word, "") != 0){
            //if adding one space and the word does exceed len, print a newline and then the word to the new line
            outf << '\n' << word;
            memset(line,0,strlen(line));        //empty the previous line
            strcat(line, word);     //add the word to line, and keep track of the new line
        }
        memset(word,0,strlen(word));        //empty word so that we can detecta nd process a new word in the next round
        pos = 0;        //set pos to 0 so word starts to store the new word from the first position
        if(inf.eof()){      //if end of the file, print a new line following the last output line, according to the spec
            outf << '\n';
            break;
        }
    }
    if (tooLong)
        return 1;       //return 1 if a word is too long
    else
        return 0;       //everything behaved correctly, so return 0
}

