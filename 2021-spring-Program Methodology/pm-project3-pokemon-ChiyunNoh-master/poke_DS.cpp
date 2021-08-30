#include "poke_DS.hpp"
#include <iostream>
#include <vector>
std::vector<int> poke_generator() {
    //initializer opened pokeDB/nextpokemon.txt
    //with std::ifstream

    //This function read one line from the pokeDB/nextpokemon.txt
    //and return the vector converted from the line
    //And then, this function will read "next line"

    //If there doesn't exist any line left,
    //the function will return the vector 
    //whose first element is randomly selected from 1~NUM_POKE

    std::vector<int> poke_information; //vector to be returned

    //read one line from next_poke_f
    //and save it to buf_string
    std::string buf_string;
    std::getline(next_poke_f, buf_string); //delimiter is default delimiter which is \n

    //buf_string is form of 
    //a,b,c,..  s.t. a,b,c are number
    //We call the each number as token
    //get the token from buf_string
    std::istringstream ss(buf_string);
    std::string token;
    std::getline(ss, token, ','); // delimiter is ,(comma) so we can get the number

    //if the token is number, selection is 0
    //else selection is the number
    //We assumed that there are no inappropriate input
    //in pokeDB/nextpokemon.txt
    //Therefore, if the otken is number, selection=1~NUM_POKE
    int selection;
    if (is_number(token)) {
        selection = std::stoi(token);
    }
    else {
        selection = 0;
    }


    if (selection == 0) {
        //if token is not number the vector should be the vector with one element
        //which is between 1~NUM_POKE
        poke_information.push_back((rand() % NUM_POKE) + 1);
    }
    else {
        poke_information.push_back(selection);
        while (std::getline(ss, token, ',')) {
            poke_information.push_back(std::stoi(token));
        }
    }
    return poke_information; // 여기로 수정해주시기 바랍니다.
}
void initializer() {
    //Initializer set the seed for random
    //In addition, initializer open the input file stream in pokeDB/next_pokemon.txt
    //to read the data of next pokemon
    srand(time(0));
    next_poke_f.open("pokeDB/next_pokemon.txt");
}
void terminator() {
    //close the input file stream when you finish the game
    next_poke_f.close();
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

