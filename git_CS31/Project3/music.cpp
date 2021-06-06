#include <iostream>
#include <string>
#include <cctype>
#include <cassert>
using namespace std;

bool hasCorrectForm(string song);
int convertSong(string song, string& instructions, int& badTick);
char convertNote(int octave, char noteLetter, char accidentalSign);


//Check if the song is in correct form
bool hasCorrectForm(string song)
{
    //An empty string is a correct song string
    if (song.size() == 0)
        return true;
    else{
        //Song must begin with upper A-G or "/"
        if (!isupper(song.at(0)) && song.at(0) != '/'){
            return false;
        }
        //Song must end with "/"
        if (song.at(song.size()-1) != '/'){
            return false;
        }
        for (unsigned int i=0; i != song.size(); i++){
            // if anything other than upper A-G, digits 0-9, b or #, and /, false
            if (song.at(i)!='A' && song.at(i)!='B' && song.at(i)!='C' && song.at(i)!='D' && song.at(i)!='E' && song.at(i)!='F' && song.at(i)!='G' && song.at(i)!='0' && song.at(i)!='1' && song.at(i)!='2' && song.at(i)!='3' && song.at(i)!='4' && song.at(i)!='5' && song.at(i)!='6' && song.at(i)!='7' && song.at(i)!='8' && song.at(i)!='9' && song.at(i)!='b' && song.at(i)!='#' && song.at(i)!='/'){
                return false;
            }
            // check the next character of any digit; if accidental sign or digit,false
            else if (isdigit(song.at(i))){
                if (song.at(i+1) == 'b' || song.at(i+1) == '#' || isdigit(song.at(i+1))){
                    return false;
                }
            }
            //an accidental sign cannot be followed by an accidental sign
            else if (song.at(i) == 'b' || song.at(i) == '#'){
                if (song.at(i+1) == 'b' || song.at(i+1) == '#'){
                    return false;
                }
            }
            //A tick must start with upper A-G or "/"; Check the next character of any "/"; if not upper nor "/",false
            else if (song.at(i) =='/' && i != song.size()-1){
                if (!isupper(song.at(i+1)) && song.at(i+1) != '/'){
                    return false;
                }
            }
        }
        return true;
    }
    
}


const int Default_Octave = 4;
int convertSong(string song, string& instructions, int& badTick)
{
    //if not a song string
    if (!hasCorrectForm(song)){
        return 1;
    }
    string newSong = "";
    int i = 0;
    
    for (int tickNum = 1; i < song.size(); tickNum++){    //start of a new tick
        //slashes that don't end a note are converted into spaces
        while (i < song.size() && song.at(i) == '/'){
            newSong += ' ';
            tickNum++;
            if (i < song.size())
                i++;
        }
        //Return noteNum to 0 as a new tick begins
        int noteNum = 0;
        //convert the song string into notes and add them up
        while (i < song.size() && song.at(i) != '/'){
            //Set the variables to default so that we can check if the note is playable later for each new note
            char convertedNote;
            char letter = ' ';
            char sign = ' ';
            char octave = Default_Octave;
            //A note starts with a uppercase letter; find the note letter
            letter = song.at(i);
            noteNum++;
            i++;
            //find the accidental sign
            if (song.at(i) == 'b' || song.at(i) == '#'){
                sign = song.at(i);
                i++;
            }
            //find the octave; if not indicated, it is always 4
            if (isdigit(song.at(i))){
                octave = song.at(i)-'0';
                i++;
            }
            //convert letter, sign, and octave into a note
            convertedNote= convertNote(octave, letter, sign);
            //check if the note is playable
            if (convertedNote == ' '){
                badTick = tickNum;
                return 2;
            }
            //add a '[' if there is more than 1 note in the tick
            if (song.at(i) != '/' && noteNum == 1){
                newSong += '[';
                }
            //Add the newly converted note to the newSong string
            newSong += convertedNote;
            }
        //If a tick with more than 1 note ends, add a ']'
        if (i < song.size() && song.at(i) == '/' && noteNum > 1){
            newSong += ']';
        }
        i++;   //Move to the next character and start a new tick
    }
    //All notes and ticks are converted; assign instructions to the newSong string
    instructions = newSong;
    return 0;
}

char convertNote(int octave, char noteLetter, char accidentalSign)
{
      // This check is here solely to report a common CS 31 student error.
    if (octave > 9)
    {
        cerr << "********** convertNote was called with first argument = "
             << octave << endl;
    }

      // Convert Cb, C, C#/Db, D, D#/Eb, ..., B, B#
      //      to -1, 0,   1,   2,   3, ...,  11, 12

    int note;
    switch (noteLetter)
    {
      case 'C':  note =  0; break;
      case 'D':  note =  2; break;
      case 'E':  note =  4; break;
      case 'F':  note =  5; break;
      case 'G':  note =  7; break;
      case 'A':  note =  9; break;
      case 'B':  note = 11; break;
      default:   return ' ';
    }
    switch (accidentalSign)
    {
      case '#':  note++; break;
      case 'b':  note--; break;
      case ' ':  break;
      default:   return ' ';
    }

      // Convert ..., A#1, B1, C2, C#2, D2, ... to
      //         ..., -2,  -1, 0,   1,  2, ...

    int sequenceNumber = 12 * (octave - 2) + note;

    string keymap = "1!2@34$5%6^78*9(0qQwWeErtTyYuiIoOpPasSdDfgGhHjJklLzZxcCvVbBnm";
    if (sequenceNumber < 0  ||  sequenceNumber >= keymap.size())
        return ' ';
    return keymap[sequenceNumber];
}

