#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<cstdlib>
#include<time.h>
#include<ctype.h>

using namespace std;
vector<string> words;

int incorrect=6;
string so_far= " ";

//Open the file from command line.
int file_size(string path) {
  int count=0;
  string line;

  ifstream myfile(path.c_str());
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
     words.push_back(line);
     count++;
    }
    myfile.close();
    return count;
  }

  else{
     cout << "Unable to open file";
     return -1;
   }

}

//If lower case convert to upper case.
char to_uppercase(char c){
  char s;
  if(c>=97 && c<=122){
      s=c-32;
      return s;
  }
  else{
 
    return c;
  }
}

//Checks whether a string contains a charactor
int contains(string s, char c){
   int i;
   for(i=0;i<s.length();i++){
      if(s[i]==to_uppercase(c)){
        return 1;
      }
   }
   return 0;
}

//Gets a random word  stored  in vector.
string get_random_word(int count){
 int iSecret;
 string l;
  srand ( (unsigned) time(NULL) );
  iSecret = rand() % count;
 // cout<<iSecret<<'\n';
  int r=0;
  vector <string>::iterator It;

  for (It = words.begin(); It != words.end(); It++){
    if(r==iSecret){
       string c=*It;
      // cout << c << '\n';
      // cout<<r<<"  "<<iSecret<<'\n';
       return  c;
    }
    else{
       r++;
    }
  }
  return NULL;
}

//Display secret word after each guess.
string display_secret_word(string word,string s2,char c){
  int i;
  int occur=0;
  int flag=0;
 
  char upper;
  if(c<65 || (c>=92 && c<=96) || c >122){
    cout<<"Input not a letter! Please guess a letter"<<'\n';
    return s2;
  }

  for(i=0;i<word.length();i++){
    
     if((word[i]==c || word[i]==c+32)  && s2[i]=='_'){
        s2[i]=c;

         occur++;
     }
    else if((word[i]==c || word[i]==c+32) && (s2[i]==c || s2[i]==c-32 || s2[i]==c+32)){
       
        flag=1;
        break;
     }
  }

  if(occur!=0){
    cout<<"Right ! "<<'\n';
    so_far=so_far + to_uppercase(c) + "  ";
   }
  else if(occur==0 && flag==0){
    cout<<"Wrong ! "<<'\n';
    if(contains(so_far,c)==1){
        cout<<"Sorry you already guessed it before! "<<'\n';
        return s2;
     }
    so_far=so_far + to_uppercase(c) + "  ";
    incorrect--;
 
   }
  else if(flag==1){
     cout<<"Sorry you already guessed it before ! "<<'\n';
   }
   return s2;
 }

//Display the chosen word by hiding all letters.
string initialize_secret_word(string word){
  int i;
  string s2=word;
  for(i=0;i<s2.length();i++){
   s2[i]='_';
 }
 return s2;
}

//Check if won the game.
int check_win(string s){
  int i;
  for(i=0;i<s.length();i++){
    if(s[i]=='_'){
       return 0;
    }
  }
  return 1;
 }

//Display the updated word each time by displaying correctly guessed letters.
string display(string s){
 string s2=" ";
 char upper;
 int i;
 for(i=0;i<s.length();i++){
     if(s[i]!='_'){
         s2= s2 + to_uppercase(s[i]) + " ";
     }
    else{
         s2= s2 + s[i] + " ";
    }

 }
 return s2;
}

//Main program
int main (int argc,char*argv[]) {
  int i;
  int iSecret;
 
  int count=0;

  if (argc != 2)
    {
      printf("\n Insufficient arguments\n");
      return 1;
    }
  string path=argv[1];

  count=file_size(path);
  cout<<"*************************WELCOME TO HANGMAN IN C++*************************"<<'\n';
  cout<<"The total word  count is : "<< count<<'\n';

  string word=get_random_word(count);

  string s= initialize_secret_word(word);
  cout<<"Secret Word: "<<display(s)<<'\n';
  cout<<"Number of incorrect guesses remaining: "<<incorrect<<'\n';

  char input;

  while(incorrect>=0){
     cout<<"Guess a letter"<<'\n';
     cin>>input;
     string w=display_secret_word(word,s,input);
     s=w;
    
     cout<<"\n\n"<<'\n';

     cout<<"Secret Word: "<<display(w)<<'\n';
     cout<<"So far you have guessed :  " + so_far<<'\n';
    // cout<<"Number of incorrect guesses remaining: "<<incorrect<<'\n';

  
     if(check_win(w)==1){
      cout<<"You guessed right.The secret word is: "<<display(word)<<'\n';
      cout<<"You win !"<<'\n';
      break;
     }
    if(check_win(w)==0 && incorrect<0){
       cout<<"You ran out of chances to make incorrect guesses.The secret word was: "<<display(word)<<'\n';
       cout<<"You lose !"<<'\n';
       break;
    }
    cout<<"Number of incorrect guesses remaining: "<<incorrect<<'\n';


 }
  return 0;
}

    
