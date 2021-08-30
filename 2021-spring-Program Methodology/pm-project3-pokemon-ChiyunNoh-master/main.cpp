#include <iostream>
#include <algorithm>
#include "poke_DS.hpp"
#include <cstdlib>
#include <ctime>
#include <string>
using namespace std;

std::ifstream next_poke_f;
std::vector<string> getSkill(string num);
class MyPokemon {
private:
    std::vector<string> character;
    std::vector<string> evolved;//누구로 진화가 가능한가?
    std::vector<string> stat;
    std::vector<vector<string>> skill;

public:
    MyPokemon(std::vector<string> character, std::vector<string> evolved, std::vector<string> stat, std::vector<vector<string>> skill) {
        this->character = character;
        this->evolved = evolved;
        this->stat = stat;
        this->skill = skill;
    }
    //rule of three
    MyPokemon(const MyPokemon& copy) {
        this->character = copy.character;
        this->evolved = copy.evolved;
        this->stat = copy.stat;
        this->skill = copy.skill;
    }

    MyPokemon& operator=(const MyPokemon& mine) {
        if (this == &mine) return *this;
        this->character = mine.character;
        this->evolved = mine.evolved;
        this->stat = mine.stat;
        this->skill = mine.skill;
        return *this;
    }
    std::string getMyName() {
        return this->character[1];
    }
    std::vector<string> getCharacter() {
        return this->character;
    }
    std::vector<string> getevolved() {
        return this->evolved;
    }
    std::vector<string> getStat() {
        return this->stat;
    }
    std::vector<vector<string>> getSkill() {
        return this->skill;
    }
    void setSkill(vector<vector<string>> newskill) {
        this->skill = newskill;
    }
    void setstat(string newstat, int i) {
        stat[i] = newstat;
    }
    void setCharacter(vector<string> character) {
        this->character = character;
    }
    void setEvolved(vector<string> evolved) {
        this->evolved = evolved;
    }
    void setStatAll(vector<string> stat) {
        this->stat = stat;
    }
};
MyPokemon select_your_pokemon();
int main_game();
int configuration();
void seePokemoneDB();
void seeMypokemonStat(MyPokemon mine);
void changeSkill(MyPokemon& mine);
std::vector<string> getPokemonCharacter(int num);
std::vector<string> getPokemonStat(int num);
std::vector<int> getPokemonType_asID(int num);
std::vector<string> getPokemonType_asString(int num);
std::vector<vector<string>> getPokemonSkill(int num);
std::vector<string> getPokemon_canbeEvolved(int num);
int attack_or_special(int num);
std::vector<vector<string>> getEnemySkill(int num);
void getSpecialSkill(std::vector<vector<string>>& skill);
void getAttackSkill(std::vector<vector<string>>& skill);
void getRandomSkill(std::vector<vector<string>>& skill);
bool skillTypecompare(string num, string type);
int damageMain(MyPokemon mine, MyPokemon enemy, int i);
int damageEnemy(MyPokemon mine, MyPokemon enemy, int i);
int typeToid(string in_type);
string getSkillInfo(string num);
int fight(MyPokemon& mine, MyPokemon& enemy, int myDamage, int enemyDamage, string mySkill, string yourSkill);
void overwhelm(MyPokemon& mine, MyPokemon& enemy);
MyPokemon generateNewOne(int id); 
int getId(string charname);

int main(){
    initializer();
    //you can implement anything at here
    //1. select your pokemon
    MyPokemon mine=select_your_pokemon();
    while (true) {
        cout << endl;
        int num = main_game();
        if (num == 3) {
            break;
        }
        if (num == 2) {
            while (true) {
                int operation_menu = configuration();
                if (operation_menu == 1) {
                    seePokemoneDB();
                    continue;
                }
                if (operation_menu == 2) {
                    seeMypokemonStat(mine);
                    continue;
                }
                if (operation_menu == 3) {
                    changeSkill(mine);
                    continue;
                }
                if (operation_menu == 4) {
                    break;
                }
            }
        }
        if (num == 1) {
            std::vector<int> enemy = poke_generator();//pokemom id + skill 구성된 벡터
            int size = enemy.size();
            int id = enemy[0];
            std::vector<string> enemy_character = getPokemonCharacter(id);
            std::vector<string> evolved = getPokemon_canbeEvolved(id);
            std::vector<string> stat = getPokemonStat(id);
            std::vector<string> type = getPokemonType_asString(id);
            std::vector<vector<string>> skill;
            if (size == 1) {
                
                std::vector<string> p_type_asString = getPokemonType_asString(num);
                std::ifstream getpokeSkill;
                int as=attack_or_special(num);
                getpokeSkill.open("pokeDB/skill_list.txt");
    
                std::stringstream ss;
                std::string line;
                if (as == 0) {
                    int count = 0;
                    while (count < p_type_asString.size()) {
                        vector<string> temp1;//attack type skillName
                        vector<string> temp2;//special type skillName
                        while (getline(getpokeSkill, line, '\r')) {
                            line = line + ",";
                            ss << line;
                            std::string id;
                            std::string skillName;
                            std::string skillInfo;
                            std::string attack_special;
                            getline(ss, id, '.');
                            getline(ss, skillName, ':');
                            getline(ss, skillInfo, ',');
                            getline(ss, attack_special, ',');
                            skillName = skillName.substr(1);
                            skillInfo = skillInfo.substr(1);
                            attack_special = attack_special.substr(1);
                            if (temp1.empty() == 0) {
                                if (p_type_asString[count].compare(skillInfo) == 0) {
                                    temp2.push_back(id);
                                    temp2.push_back(skillName);
                                    temp2.push_back(attack_special);
                                    int random = (rand() % 2) + 1;//attack special 중 랜덤하게 skill 배정!
                                    if (random == 1) {
                                        skill.push_back(temp1);
                                    }
                                    else {
                                        skill.push_back(temp2);
                                    }
                                    count++;
                                    getline(getpokeSkill, line, '\n');
                                    line.clear();
                                    break;
                                }
                            }
                            if (p_type_asString[count].compare(skillInfo) == 0) {
                                temp1.push_back(id);
                                temp1.push_back(skillName);
                                temp1.push_back(attack_special);
                            }
                            ss.str("");
                            getline(getpokeSkill, line, '\n');
                            line.clear();
                        }
                    }
                }
                else{ //attack 이 더큼
                    int count = 0;
                    while (count < p_type_asString.size()) {
                        vector<string> temp1;//attack type skillName
                        while (getline(getpokeSkill, line, '\r')) {
                            line = line + ",";
                            ss << line;
                            std::string id;
                            std::string skillName;
                            std::string skillInfo;
                            std::string attack_special;
                            getline(ss, id, '.');
                            getline(ss, skillName, ':');
                            getline(ss, skillInfo, ',');
                            getline(ss, attack_special, ',');
                            skillName = skillName.substr(1);
                            skillInfo = skillInfo.substr(1);
                            attack_special = attack_special.substr(1);
                            if (as == 1) {
                                if (p_type_asString[count].compare(skillInfo) == 0 && attack_special.compare("attack") == 0) {
                                    temp1.push_back(id);
                                    temp1.push_back(skillName);
                                    temp1.push_back(attack_special);
                                    skill.push_back(temp1);
                                    count++;
                                    getline(getpokeSkill, line, '\n');
                                    line.clear();
                                    break;
                                }
                            }
                            if (as == -1) {
                                
                                if (p_type_asString[count].compare(skillInfo) == 0 && attack_special.compare("special") == 0) {
                                    temp1.push_back(id);
                                    temp1.push_back(skillName);
                                    temp1.push_back(attack_special);
                                    skill.push_back(temp1);
                                    count++;
                                    getline(getpokeSkill, line, '\n');
                                    line.clear();
                                    break;
                                }
                            }
                            
                            ss.str("");
                            getline(getpokeSkill, line, '\n');
                            line.clear();
                        }
                    }
                }
                getpokeSkill.close();
                //skill = getEnemySkill(id);
                if (attack_or_special(id) == 1) {
                    getAttackSkill(skill);
                }
                else if (attack_or_special(id) == -1) {
                    getSpecialSkill(skill);
                }
                else {
                    getRandomSkill(skill);
                }
                
            }
            else {
                for (int i = 1; i < size; i++) {
                    skill.push_back(getSkill(to_string(enemy[i])));
                }
            }
            MyPokemon enemyinfo(enemy_character, evolved, stat, skill);

            cout << endl;
            cout << "wild pokemon " << enemyinfo.getMyName() << " appeared" << endl;
            cout << "enemy pokemon's information" << endl;
            cout << "pokemon_id: " << enemyinfo.getCharacter()[0] << ", pokemon_name : " << enemyinfo.getMyName() << endl;

            if (is_number(enemy_character[2])) {
                std::vector<string> temp = getPokemonCharacter(stoi(enemy_character[2]));
                std::cout << "evolved from " << temp[1] << endl;
            }

            if (evolved[0].compare("None") != 0) {
                std::cout << "candidates to be evolved: ";
                for (int i = 0; i < evolved.size(); i++) {
                    std::cout << evolved[i] << " ";
                }
                std::cout << "\n";
            }
            cout << "stat: " << "hp " << stat[0] << " attack " << stat[1] << " defense " << stat[2] << " special_attack " << stat[3] << " special_defense " << stat[4] << " speed " << stat[5] << endl;
            std::cout << "type:";
            for (int i = 0; i < type.size(); i++) {
                std::cout << " " << type[i];
            }
            cout << endl;
            std::cout << "skill: " << skill[0][1];
            if (skill.size() != 1) {
                for (int i = 1; i < skill.size(); i++) {
                    std::cout << "/" << skill[i][1];
                }
            }
            cout <<"\n";
            int mySkill = 0;
            string s_mySkill=mine.getSkill()[0][1];
            int enemySkill = 0;
            string s_enemySkill=enemyinfo.getSkill()[0][1];
            cout << "\nyour pokemon's efficacy to the enemy" << endl;
            for (int i = 0; i < mine.getSkill().size(); i++) {
                cout << mine.getSkill()[i][1] << " damage is " << damageMain(mine, enemyinfo, i) << endl;
                if (damageMain(mine, enemyinfo, i) > mySkill) {
                    mySkill = damageMain(mine, enemyinfo, i);
                    s_mySkill = mine.getSkill()[i][1];
                }
            }
            cout << "enemy's efficacy to your pokemon" << endl;
            for (int i = 0; i < enemyinfo.getSkill().size(); i++) {
                cout << enemyinfo.getSkill()[i][1] << " damage is "<< damageEnemy(enemyinfo, mine, i) << endl;
                if (damageEnemy(enemyinfo, mine, i) > enemySkill) {
                    enemySkill = damageEnemy(enemyinfo, mine, i);
                    s_enemySkill = enemyinfo.getSkill()[i][1];
                }
            }
            cout << endl;

            int result = fight(mine, enemyinfo, mySkill, enemySkill, s_mySkill, s_enemySkill);
            if (result == 1) {
                overwhelm(mine, enemyinfo);
                int a=0;
                if (mine.getevolved()[0].compare("None")!= 0) {
                    a=1;
                    cout<<"\n";
                    cout << "Your pokemon can be evolved to ";
                    for (int i = 0; i < mine.getevolved().size(); i++) {
                        cout << i + 1 << ". " << mine.getevolved()[i] << " ";
                    }
                    cout << "\n" << "Which pokemon you want to be evolved to?" << endl;
                    cout << "select the number above, select 0 if you don't want to evolve your pokemon" << endl;
                    cout << "selection: ";
                    string in_num;
                    getline(std::cin >> std::ws, in_num);
                    bool correct = false;
                    while (true) {
                        for (int i = 0; i <= mine.getevolved().size(); i++) {
                            if (in_num.compare(to_string(i)) == 0)
                                correct = true;
                        }
                        if (correct == true) {
                            break;
                        }
                        else {
                            std::cout << "please insert appropriate number" << endl;
                            std::cout << "selection: ";
                            getline(std::cin >> std::ws, in_num);
                        }
                    }
                    int num = stoi(in_num);
                    if (num != 0) {
                        int newId = getId(mine.getevolved()[num - 1]);
                        MyPokemon newone = generateNewOne(newId);
                        overwhelm(mine, newone);

                        mine.setCharacter(newone.getCharacter());

                        mine.setEvolved(newone.getevolved());
                    }
                }
                if (a== 0){
                    cout<<"\n";
                }
                cout << "Will you change your pokemon into enemy's pokemon? 1. yes 2. no" << endl;
                std::cout << "selection: ";
                string in_num;
                getline(std::cin >> std::ws, in_num);
                while (true) {
                    if (in_num.compare("1") == 0 || in_num.compare("2") == 0)
                        break;
                    std::cout << "please insert appropriate number" << endl;
                    std::cout << "selection: ";
                    getline(std::cin >> std::ws, in_num);
                }
                if (stoi(in_num) == 1) {
                    enemyinfo.setStatAll(mine.getStat());
                    mine = enemyinfo;
                }
                

            }



        }
    }
    
    terminator();
    return 0;
}

MyPokemon select_your_pokemon() {
    std::cout << "choose your pokemon among 1. bulbasaur 2. charmander 3. squirtle" << endl;
    string in_num;
    std::cout << "your choice: ";
    getline(std::cin >> std::ws, in_num);
    while(true) {
        if (in_num.compare("1")==0 || in_num.compare("2")==0 || in_num.compare("3")==0)
            break;
        std::cout << "please insert appropriate number"<<endl;
        std::cout << "your choice: ";
        getline(std::cin >> std::ws, in_num);
    }
    int num = stoi(in_num);
    std::cout << "\nyour pokemon info" << endl;
    int num1;
    if (num == 1) {
        num1 = 1;               
    }
    else if (num == 2) {
        num1 = 4;
    }
    else {
        num1 = 7;
    }
    std::vector<string> character = getPokemonCharacter(num1);
    std::cout << "pokemon_id: " << num1 << ", pokemon_name: " << character[1] << endl;
    if (is_number(character[2])) {
        std::vector<string> temp = getPokemonCharacter(stoi(character[2]));
        std::cout << "evolved from " << temp[1] << endl;
    }
    std::vector<string> evolved = getPokemon_canbeEvolved(num1);
    if (evolved[0].compare("None") != 0) {
        std::cout << "candidates to be evolved: ";
        for (int i = 0; i < evolved.size(); i++) {
            std::cout << evolved[i] << " ";
        }
        std::cout << "\n";
    }
    


    std::vector<string> stat = getPokemonStat(num1);
    std::cout<<"stat: "<<"hp "<< stat[0] << " attack " << stat[1] << " defense " << stat[2] << " special_attack " << stat[3] << " special_defense " << stat[4] << " speed " << stat[5] << endl;  

    std::vector<string> type = getPokemonType_asString(num1);
    std::cout << "type:";
    for (int i = 0; i < type.size(); i++) {
        std::cout << ' ' << type[i];
    }
    std::cout << "\n";
    
    std::vector<vector<string>> skill = getPokemonSkill(num1);
    std::cout << "skill: " << skill[0][1];
    if (skill.size() != 1) {
        for (int i = 1; i < skill.size(); i++) {
            std::cout << "/" << skill[i][1];
        }
    }
    MyPokemon mine(character, evolved, stat, skill);//나의 포켓몬 관련 정보 저장 
    cout << endl;
    return mine;
}

int main_game() {
    cout <<"What do you want to do?" << endl;
    cout << "1. battle 2. change your pokemon's stat 3. exit" << endl;
    cout << "your choice: ";
    string in_num;
    getline(std::cin >> std::ws, in_num);
    while (true) {
        if (in_num.compare("1") == 0 || in_num.compare("2") == 0 || in_num.compare("3") == 0)
            break;
        std::cout << "please insert appropriate number" << endl;
        std::cout << "your choice: ";
        getline(std::cin >> std::ws, in_num);
    }
    int num = stoi(in_num);
    return num;
}

int configuration() {
    cout << endl;
    cout << "select the operation among 1~4" << endl;
    cout << "1. see pokemonDB" << endl;
    cout << "2. see my pokemon's stat" << endl;
    cout << "3. change my pokemon's skill" << endl;
    cout << "4. exit from configuration mode" << endl;
    cout << "select: ";
    string in_num;
    getline(std::cin >> std::ws, in_num);
    while (true) {
        if (in_num.compare("1") == 0 || in_num.compare("2") == 0 || in_num.compare("3") == 0|| in_num.compare("4") == 0)
            break;
        std::cout << "please insert appropriate number" << endl;
        std::cout << "select: ";
        getline(std::cin >> std::ws, in_num);
    }
    int num = stoi(in_num);
    return num;
}

void seePokemoneDB() {
    cout << endl;
    cout << "what pokekmon do you want to see? ";
    string in_num;
    getline(std::cin >> std::ws, in_num);
    if (!is_number(in_num)) {
        std::cout << "please insert appropriate number" << endl;
        return;
    }
    int num1 = stoi(in_num);
    if (num1 > NUM_POKE || num1 < 1) {
        std::cout << "please insert appropriate number" << endl;
        return;
    }
    else {
        std::vector<string> character = getPokemonCharacter(num1);
        std::cout << "pokemon_id: " << num1 << ", pokemon_name: " << character[1] << endl;
        if (is_number(character[2])) {
            std::vector<string> temp = getPokemonCharacter(stoi(character[2]));
            std::cout << "evolved from " << temp[1] << endl;
        }
        std::vector<string> evolved = getPokemon_canbeEvolved(num1);
        if (evolved[0].compare("None") != 0) {
            std::cout << "candidates to be evolved: ";
            for (int i = 0; i < evolved.size(); i++) {
                std::cout << evolved[i] << " ";
            }
            std::cout << "\n";
        }
        std::vector<string> stat = getPokemonStat(num1);
        std::cout << "stat: " << "hp " << stat[0] << " attack " << stat[1] << " defense " << stat[2] << " special_attack " << stat[3] << " special_defense " << stat[4] << " speed " << stat[5] << endl;
        std::vector<string> type = getPokemonType_asString(num1);
        std::cout << "type:";
        for (int i = 0; i < type.size(); i++) {
            std::cout << " " << type[i];
        }
        std::cout << "\n";
    }
    
}

void seeMypokemonStat(MyPokemon mine) {
    cout << endl;
    std::cout << "pokemon_id: " << mine.getCharacter()[0] << ", pokemon_name: " << mine.getCharacter()[1] << endl;
    if (is_number(mine.getCharacter()[2])) {
        std::vector<string> temp = getPokemonCharacter(stoi(mine.getCharacter()[2]));
        std::cout << "evolved from " << temp[1] << endl;
    }
    std::vector<string> evolved = mine.getevolved();
    if (evolved[0].compare("None") != 0) {
        std::cout << "candidates to be evolved: ";
        for (int i = 0; i < evolved.size(); i++) {
            std::cout << evolved[i] << " ";
        }
        std::cout << "\n";
    }
    std::vector<string> stat = mine.getStat();
    std::cout << "stat: " << "hp " << stat[0] << " attack " << stat[1] << " defense " << stat[2] << " special_attack " << stat[3] << " special_defense " << stat[4] << " speed " << stat[5] << endl;
    std::vector<string> type = getPokemonType_asString(stoi(mine.getCharacter()[0]));
    std::cout << "type:";
    for (int i = 0; i < type.size(); i++) {
        std::cout << " " << type[i];
    }
    std::cout << "\n";

    std::vector<vector<string>> skill = mine.getSkill();
    std::cout << "skill: " << skill[0][1];
    if (skill.size() != 1) {
        for (int i = 1; i < skill.size(); i++) {
            std::cout << "/" << skill[i][1];
        }
    }
    cout << endl;
}

void changeSkill(MyPokemon& mine) {
    cout << endl;
    string line;
    std::vector<vector<string>> myskill = mine.getSkill();
    string name = mine.getMyName();
    int switchSkill=0;
    //스킬이 다 찬 경우
    if (myskill.size() == 4) {
        cout << name << " has learned ";
        for (int i = 0; i < myskill.size(); i++) {
            cout << i + 1 << ". " << myskill[i][1] << " ";
        }
        cout << endl;
        cout << "which skill your pokemon want to replace? ";
        string in_num;
        getline(std::cin >> std::ws, in_num);
        if (!is_number(in_num)) {
            std::cout << "please insert appropriate number" << endl;
            return;
        }
        int num1 = stoi(in_num);
        if (num1 > 4 || num1 < 1) {
            std::cout << "please insert appropriate number" << endl;
            return;
        }
        switchSkill = stoi(in_num);
    }
    std::ifstream getpokeSkill;
    getpokeSkill.open("pokeDB/skill_list.txt");
    while (getline(getpokeSkill, line, '\r')) {
        cout << line << endl;
        getline(getpokeSkill,line,'\n');
        line.clear();
    }
    getpokeSkill.close();
    
    cout << "what skill your pokemon want to learn? ";
    string in_num;
    getline(std::cin >> std::ws, in_num);
    if (!is_number(in_num)) {
        std::cout << "please insert appropriate number" << endl;
        return;
    }
    int num1 = stoi(in_num);
    if (num1 > 36 || num1 < 1) {
        std::cout << "please insert appropriate number" << endl;
        return;
    }
    else {
        for (int i = 0; i < myskill.size(); i++) {//skill overlap
            if (myskill[i][0].compare(in_num) == 0) {
                cout << "already learned " << myskill[i][1] << endl;
                return;
            }
        }
        if (switchSkill == 0) {//스킬이 꽉 안찬경우
            myskill.push_back(getSkill(in_num));
            mine.setSkill(myskill);
            return;
        }
        else {
            vector<vector<string>> newskill;
            for (int i = 0; i < myskill.size(); i++) {
                if (i != switchSkill - 1) {
                    newskill.push_back(myskill[i]);
                }
            }
            newskill.push_back(getSkill(in_num));
            mine.setSkill(newskill);
        }
        return;
    }
}

std::vector<string> getPokemonCharacter(int num) {//pokemon_id를 받아 name, 진화전, 후 벡터 return
    std::vector<string> p_character;
    std::ifstream getpokeName;
    getpokeName.open("pokeDB/pokemon_species.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeName, line, '\n');//첫번째 줄 삭제 작업
    line.clear();
    while (getline(getpokeName, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string name;
        std::string evolves_from_id;
        std::string evolution_chain_id;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, evolves_from_id, ',');
        getline(ss, evolution_chain_id, ',');
        if (stoi(id) - num == 0) {
            p_character.push_back(id);
            p_character.push_back(name);
            p_character.push_back(evolves_from_id);
            p_character.push_back(evolution_chain_id);
            getpokeName.close();
            return p_character;
        }
        ss.str("");
        getline(getpokeName,line,'\n');
        line.clear();
    }
    std::vector<string> nil={""};
    return nil;
}

std::vector<string> getPokemonStat(int num) {//pokemon_id를 받아 pokemon stat return
    std::vector<string> p_stat;
    std::ifstream getpokeStat;
    getpokeStat.open("pokeDB/pokemon_stats.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeStat, line, '\n');
    line.clear();
    while (getline(getpokeStat, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string stat_id;
        std::string base_stat;
        getline(ss, id, ',');
        getline(ss, stat_id, ',');
        getline(ss, base_stat, ',');
        if (stoi(id) - num == 0) {
            p_stat.push_back(base_stat);
        }
        if (p_stat.size() == 6) {
            getpokeStat.close();
            return p_stat;
        }
        ss.str("");
        getline(getpokeStat,line,'\n');
        line.clear();
    }
    std::vector<string> nil={""};
    return nil;
}

std::vector<int> getPokemonType_asID(int num) {//pokemon_id를 받아 pokemon type_id를 return
    std::vector<string> p_type;
    std::vector<int> p_type_int;
    std::ifstream getpokeType;
    getpokeType.open("pokeDB/pokemon_types.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeType, line, '\n');
    line.clear();
    while (getline(getpokeType, line, '\r')) {
        ss << line;
        std::string id;
        std::string type_id;
        getline(ss, id, ',');
        getline(ss, type_id, ',');
        if (stoi(id) - num == 0) {
            p_type.push_back(type_id);
        }
        if (p_type.empty() == 0 && stoi(id) - num != 0) {
            for (int i = 0; i < p_type.size(); i++) {
                p_type_int.push_back(stoi(p_type[i]));
            }
            sort(p_type_int.begin(), p_type_int.end());
            getpokeType.close();
            return p_type_int;
        }
        ss.str("");
        getline(getpokeType,line,'\n');
        line.clear();
    }
    std::vector<int> nil={0};
    return nil;
}

std::vector<string> getPokemonType_asString(int num) {//pokemon_id를 받아 type의 이름 return 
    std::vector<int> p_type_int = getPokemonType_asID(num);
    std::vector<string> p_type_asString;
    std::ifstream getpokeType;
    getpokeType.open("pokeDB/types.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeType, line, '\n');
    line.clear();
    int count = 0;
    while (count < p_type_int.size()) {
        while (getline(getpokeType, line, '\r')) {
            line = line + ",";
            ss << line;
            std::string id;
            std::string identifier;
            getline(ss, id, ',');
            getline(ss, identifier, ',');
            if (stoi(id) - p_type_int[count] == 0) {
                p_type_asString.push_back(identifier);
                count++;
                break;
            }
            ss.str("");
            getline(getpokeType,line,'\n');
            line.clear();
        }
    }
    getpokeType.close();
    return p_type_asString;
}

std::vector<vector<string>> getPokemonSkill(int num) {//pokemon_id를 받아 id+skill의 이름+(attack, special) 2차원 vector return
    std::vector<string> p_type_asString = getPokemonType_asString(num);
    std::vector<vector<string>> temp;
    std::ifstream getpokeSkill;
    getpokeSkill.open("pokeDB/skill_list.txt");
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    while (count < p_type_asString.size()) {
        vector<string> temp1;//attack type skillName
        vector<string> temp2;//special type skillName
        while (getline(getpokeSkill, line, '\r')) {
            line = line + ",";
            ss << line;
            std::string id;
            std::string skillName;
            std::string skillInfo;
            std::string attack_special;
            getline(ss, id, '.');
            getline(ss, skillName, ':');
            getline(ss, skillInfo, ',');
            getline(ss, attack_special, ',');
            skillName = skillName.substr(1);
            skillInfo = skillInfo.substr(1);
            attack_special = attack_special.substr(1);
            if (temp1.empty() == 0) {
                if (p_type_asString[count].compare(skillInfo) == 0) {
                    temp2.push_back(id);
                    temp2.push_back(skillName);
                    temp2.push_back(attack_special);
                    int num = (rand() % 2) + 1;//attack special 중 랜덤하게 skill 배정!
                    if (num == 1) {
                        temp.push_back(temp1);
                    }
                    else {
                        temp.push_back(temp2);
                    }
                    count++;
                    break;
                }
            }
            if (p_type_asString[count].compare(skillInfo)== 0) {
                temp1.push_back(id);
                temp1.push_back(skillName);
                temp1.push_back(attack_special);
            }
            ss.str("");
            getline(getpokeSkill,line,'\n');
            line.clear();
        }
    }
    getpokeSkill.close();
    return temp;
}

std::vector<string> getSkill(string num) {//skill_id를 받아 id+skill의 이름+(attack, special) vector return 
    std::ifstream getpokeSkill;
    getpokeSkill.open("pokeDB/skill_list.txt");
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    std::vector<string> temp;
    while (getline(getpokeSkill, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string skillName;
        std::string skillInfo;
        std::string attack_special;
        getline(ss, id, '.');
        getline(ss, skillName, ':');
        getline(ss, skillInfo, ',');
        getline(ss, attack_special, ',');
        skillName = skillName.substr(1);
        skillInfo = skillInfo.substr(1);
        attack_special = attack_special.substr(1);
        if (num.compare(id) == 0) {//skill id 가 같다
            temp.push_back(id);
            temp.push_back(skillName);
            temp.push_back(attack_special);
        }
        getline(getpokeSkill, line, '\n');
        line.clear();
        ss.str("");
    }
    getpokeSkill.close();
    return temp;
}

string getSkillInfo(string num) {//skill_id를 받아 skill_type(normal fire~~) 리턴
    std::ifstream getpokeSkill;
    getpokeSkill.open("pokeDB/skill_list.txt");
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    std::vector<string> temp;
    while (getline(getpokeSkill, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string skillName;
        std::string skillInfo;
        std::string attack_special;
        getline(ss, id, '.');
        getline(ss, skillName, ':');
        getline(ss, skillInfo, ',');
        getline(ss, attack_special, ',');
        skillName = skillName.substr(1);
        skillInfo = skillInfo.substr(1);
        attack_special = attack_special.substr(1);
        if (num.compare(id) == 0) {//skill id 가 같다
            getpokeSkill.close();
            return skillInfo;
        }

        ss.str("");
        getline(getpokeSkill,line,'\n');
        line.clear();
    }
    string nil("");
    return nil;
    
}

std::vector<string> getPokemon_canbeEvolved(int num) {//pokemon_id를 받아 진화가능한 포켓몬의 이름 출력, 진화 가능한게 없다면 none 출력
    std::vector<string> evolved;
    std::ifstream getpokeName;
    getpokeName.open("pokeDB/pokemon_species.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeName, line, '\n');
    line.clear();
    while (getline(getpokeName, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string name;
        std::string evolves_from_id;
        std::string evolution_chain_id;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, evolves_from_id, ',');
        getline(ss, evolution_chain_id, ',');
        if (!is_number(evolves_from_id)) {//비어있다면
            evolves_from_id = "0";
        }
        if (stoi(evolves_from_id) - num == 0) {
            evolved.push_back(name);
        }
        ss.str("");
        getline(getpokeName,line,'\n');
        line.clear();
    }
    if (evolved.empty() == 1) {
        evolved.push_back("None");
    }
    getpokeName.close();
    return evolved;
}

int attack_or_special(int num) {//pokemon_id를 받아 attack stat 과 special stat 비교, attack 이 더 크면 1, 작으면 -1 같으면 0 리턴
    std::vector<string> p_stat;
    std::ifstream getpokeStat;
    getpokeStat.open("pokeDB/pokemon_stats.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeStat, line, '\n');
    line.clear();
    while (getline(getpokeStat, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string stat_id;
        std::string base_stat;
        getline(ss, id, ',');
        getline(ss, stat_id, ',');
        getline(ss, base_stat, ',');
        if (stoi(id) - num == 0) {
            p_stat.push_back(base_stat);
        }
        if (p_stat.size() == 6) {
            getpokeStat.close();
            if (stoi(p_stat[1]) > stoi(p_stat[3])){
                getpokeStat.close();
                return 1;
            }
            else if (stoi(p_stat[1]) < stoi(p_stat[3])){
                getpokeStat.close();
                return -1;
            }
            else if (stoi(p_stat[1]) == stoi(p_stat[3])){
                getpokeStat.close();
                return 0;
            }
        }
        ss.str("");
        getline(getpokeStat, line, '\n');
        line.clear();
    }
    return -2;
}

std::vector<vector<string>> getEnemySkill(int num) {//타입과 attack, special에 맞는 skill로 구성된 벡터 리턴
    std::vector<string> p_type_asString = getPokemonType_asString(num);
    std::vector<vector<string>> temp;
    std::ifstream getpokeSkill;
    int as=attack_or_special(num);
    getpokeSkill.open("pokeDB/skill_list.txt");
    //주소변경
    std::stringstream ss;
    std::string line;
    if (as == 0) {
        int count = 0;
        while (count < p_type_asString.size()) {
            vector<string> temp1;//attack type skillName
            vector<string> temp2;//special type skillName
            while (getline(getpokeSkill, line, '\r')) {
                line = line + ",";
                ss << line;
                std::string id;
                std::string skillName;
                std::string skillInfo;
                std::string attack_special;
                getline(ss, id, '.');
                getline(ss, skillName, ':');
                getline(ss, skillInfo, ',');
                getline(ss, attack_special, ',');
                skillName = skillName.substr(1);
                skillInfo = skillInfo.substr(1);
                attack_special = attack_special.substr(1);
                if (temp1.empty() == 0) {
                    if (p_type_asString[count].compare(skillInfo) == 0) {
                        temp2.push_back(id);
                        temp2.push_back(skillName);
                        temp2.push_back(attack_special);
                        int random = (rand() % 2) + 1;//attack special 중 랜덤하게 skill 배정!
                        if (random == 1) {
                            temp.push_back(temp1);
                        }
                        else {
                            temp.push_back(temp2);
                        }
                        count++;
                        getline(getpokeSkill, line, '\n');
                        line.clear();
                        break;
                    }
                }
                if (p_type_asString[count].compare(skillInfo) == 0) {
                    temp1.push_back(id);
                    temp1.push_back(skillName);
                    temp1.push_back(attack_special);
                }
                ss.str("");
                getline(getpokeSkill, line, '\n');
                line.clear();
            }
        }
    }
    else{ //attack 이 더큼
        int count = 0;
        while (count < p_type_asString.size()) {
            vector<string> temp1;//attack type skillName
            while (getline(getpokeSkill, line, '\n')) {
                line = line + ",";
                ss << line;
                std::string id;
                std::string skillName;
                std::string skillInfo;
                std::string attack_special;
                getline(ss, id, '.');
                getline(ss, skillName, ':');
                getline(ss, skillInfo, ',');
                getline(ss, attack_special, ',');
                skillName = skillName.substr(1);
                skillInfo = skillInfo.substr(1);
                attack_special = attack_special.substr(1);
                if (as == 1) {
                    if (p_type_asString[count].compare(skillInfo) == 0 && attack_special.compare("attack") == 0) {
                        temp1.push_back(id);
                        temp1.push_back(skillName);
                        temp1.push_back(attack_special);
                        temp.push_back(temp1);
                        count++;
                        getline(getpokeSkill, line, '\n');
                        line.clear();
                        break;
                    }
                }
                if (as == -1) {
                    
                    if (p_type_asString[count].compare(skillInfo) == 0 && attack_special.compare("special") == 0) {
                        temp1.push_back(id);
                        temp1.push_back(skillName);
                        temp1.push_back(attack_special);
                        temp.push_back(temp1);
                        count++;
                        getline(getpokeSkill, line, '\n');
                        line.clear();
                        break;
                    }
                }
                
                ss.str("");
                getline(getpokeSkill, line, '\n');
                line.clear();
            }
        }
    }
    getpokeSkill.close();
    return temp;
}

void getAttackSkill(std::vector<vector<string>>& skill) {
    int size = skill.size();
    int need_skill = 4 - size;
    int count = 0;
    while (need_skill > count) {
        bool same = false;
        int num = (rand() % 36) + 1;
        if (getSkill(to_string(num))[2].compare("special")) {
            continue;
        }
        for (int i = 0; i < size; i++) {
            if (stoi(skill[i][0]) - num == 0) {
                same = true;
                break;
            }
        }
        if (same == false) {
            size++;
            vector<string> newskill;
            skill.push_back(getSkill(to_string(num)));
            count++;
        }
        else {
            continue;
        }
    }
}

void getSpecialSkill(std::vector<vector<string>>& skill) {
    int size = skill.size();
    int need_skill = 4 - size;
    int count = 0;
    while (need_skill > count) {
        bool same = false;
        int num = (rand() % 36) + 1;
        if (getSkill(to_string(num))[2].compare("attack")) {
            continue;
        }
        for (int i = 0; i < size; i++) {
            if (stoi(skill[i][0]) - num == 0) {
                same = true;
                break;
            }
        }
        if (same == false) {
            size++;
            vector<string> newskill;
            skill.push_back(getSkill(to_string(num)));
            count++;
        }
        else {
            continue;
        }
    }
}

void getRandomSkill(std::vector<vector<string>>& skill) {
    int size = skill.size();
    int need_skill = 4 - size;
    int count = 0;
    while (need_skill > count) {
        bool same = false;
        int num = (rand() % 36) + 1;
        
        for (int i = 0; i < size; i++) {
            if (stoi(skill[i][0]) - num == 0) {
                same = true;
                break;
            }
        }
        if (same == false) {
            size++;
            vector<string> newskill;
            skill.push_back(getSkill(to_string(num)));
            count++;
        }
        else {
            continue;
        }
    }
}

bool skillTypecompare(string num, string type) {//num번째 skill의 type이 매개변수 type과 일치하는지 비교
    std::ifstream getpokeSkill;
    getpokeSkill.open("pokeDB/skill_list.txt");
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    std::vector<string> temp;
    while (getline(getpokeSkill, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string skillName;
        std::string skillInfo;
        std::string attack_special;
        getline(ss, id, '.');
        getline(ss, skillName, ':');
        getline(ss, skillInfo, ',');
        getline(ss, attack_special, ',');
        skillName = skillName.substr(1);
        skillInfo = skillInfo.substr(1);
        attack_special = attack_special.substr(1);
        if (num.compare(id) == 0) {//skill id 가 같다
            if (skillInfo.compare(type) == 0){
                getpokeSkill.close();
                return true;
            }
        }
        ss.str("");
        getline(getpokeSkill, line, '\n');
        line.clear();
    }
    getpokeSkill.close();
    return false;
}

int typeToid(string in_type) {

    std::ifstream getType;
    getType.open("pokeDB/types.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getType, line, '\n');
    line.clear();
    while (getline(getType, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string type;
        getline(ss, id, ',');
        getline(ss, type, ',');
        if (type.compare(in_type)==0) {
            getType.close();
            return stoi(id);
        }
        ss.str("");
        getline(getType, line, '\n');
        line.clear();
    }
    getType.close();
    return 0;
}

int damageMain(MyPokemon mine, MyPokemon enemy, int i) {//주인공이 i번째 스킬로 주는 데미지 계산
    string attackOrspecial = mine.getSkill()[i][2];
    string mine_id = mine.getCharacter()[0];
    string enemy_id = enemy.getCharacter()[0];
    string type= getSkillInfo(mine.getSkill()[i][0]);
    int type_id = typeToid(type);//skill의 type의 id
    std::vector<int> type_id_enemy = getPokemonType_asID(stoi(enemy_id));//적의 type id 벡터로 리턴
    double type_correction = 1;//타입보정
    std::ifstream gettype{ "pokeDB/type_efficacy.csv" };
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    std::vector<string> temp;
    getline(gettype, line,'\n');
    line.clear();
    while (getline(gettype, line, '\n')) {
        line = line + ",";
        ss << line;
        std::string my_skilltype_id;
        std::string your_type_id;
        std::string damagefactor;
        getline(ss, my_skilltype_id, ',');
        getline(ss, your_type_id, ',');
        getline(ss, damagefactor, ',');
        for (int i = 0; i < type_id_enemy.size(); i++) {
            if (stoi(my_skilltype_id)-type_id == 0 && stoi(your_type_id)-type_id_enemy[i] == 0) {
                double i_damagefactor = stod(damagefactor);
                type_correction *=i_damagefactor / 100;
            }
        }
        ss.str("");
    }
    gettype.close();
    int a=1;
    int d=1;
    double type_tech=1;
    if (attackOrspecial.compare("attack")==0) {
        a = stoi(mine.getStat()[1])+31;
        d = stoi(enemy.getStat()[2])+31;
        vector<string> type_vector = getPokemonType_asString(stoi(mine.getCharacter()[0]));
        type_tech=1;//타입 기술 보정
        for (int j = 0; j < type_vector.size(); j++) {
            if (skillTypecompare(mine.getSkill()[i][0], type_vector[j])) {
                type_tech = 1.5;
            }
        }
    }
    if (attackOrspecial.compare("special")==0) {
        a = stoi(mine.getStat()[3])+31;
        d = stoi(enemy.getStat()[4])+31;
        vector<string> type_vector = getPokemonType_asString(stoi(mine.getCharacter()[0]));
        type_tech = 1;//타입 기술 보정
        for (int j = 0; j < type_vector.size(); j++) {
            if (skillTypecompare(mine.getSkill()[i][0], type_vector[j])) {
                type_tech = 1.5;
            }
        }
    }
    double damage = (44 * (double)a / d + 2) * 1.5 * type_tech * type_correction;
    int ii_damage = static_cast<int>(damage);
    if (damage - ii_damage == 0) {
        return ii_damage;
    }
    else {
        return ii_damage + 1;
    }

}

int damageEnemy(MyPokemon mine, MyPokemon enemy, int i) {//적이 주는 데미지 계산
    string attackOrspecial = mine.getSkill()[i][2];
    string mine_id = mine.getCharacter()[0];
    string enemy_id = enemy.getCharacter()[0];
    string type = getSkillInfo(mine.getSkill()[i][0]);
    int type_id = typeToid(type);//skill의 type의 id
    std::vector<int> type_id_enemy = getPokemonType_asID(stoi(enemy_id));//적의 type id 벡터로 리턴

    double type_correction = 1;//타입보정
    std::ifstream gettype{ "pokeDB/type_efficacy.csv" };
    //주소변경
    std::stringstream ss;
    std::string line;
    int count = 0;
    std::vector<string> temp;
    getline(gettype, line, '\n');
    line.clear();
    while (getline(gettype, line, '\n')) {
        line = line + ",";
        ss << line;
        std::string my_skilltype_id;
        std::string your_type_id;
        std::string damagefactor;
        getline(ss, my_skilltype_id, ',');
        getline(ss, your_type_id, ',');
        getline(ss, damagefactor, ',');
        for (int i = 0; i < type_id_enemy.size(); i++) {
            if (stoi(my_skilltype_id) - type_id == 0 && stoi(your_type_id) - type_id_enemy[i] == 0) {
                double i_damagefactor = stod(damagefactor);
                type_correction *= i_damagefactor / 100;
            }
        }
        ss.str("");

    }
    gettype.close();
    int a = 1;
    int d = 1;
    double type_tech = 1;
    if (attackOrspecial.compare("attack") == 0) {
        a = stoi(mine.getStat()[1])+31;
        d = stoi(enemy.getStat()[2])+31;
        vector<string> type_vector = getPokemonType_asString(stoi(mine.getCharacter()[0]));
        type_tech = 1;//타입 기술 보정
        for (int j = 0; j < type_vector.size(); j++) {
            if (skillTypecompare(mine.getSkill()[i][0], type_vector[j])) {
                type_tech = 1.5;
            }
        }
    }
    if (attackOrspecial.compare("special") == 0) {
        a = stoi(mine.getStat()[3])+31;
        d = stoi(enemy.getStat()[4])+31;
        vector<string> type_vector = getPokemonType_asString(stoi(mine.getCharacter()[0]));
        type_tech = 1;//타입 기술 보정
        for (int j = 0; j < type_vector.size(); j++) {
            if (skillTypecompare(mine.getSkill()[i][0], type_vector[j])) {
                type_tech = 1.5;
            }
        }
    }
    double damage = (44 * (double)a / d + 2) * 1.0 * type_tech * type_correction;
    int ii_damage = static_cast<int>(damage);
    if (damage - ii_damage == 0) {
        return ii_damage;
    }
    else {
        return ii_damage + 1;
    }

}

int fight(MyPokemon &mine, MyPokemon &enemy, int myDamage, int enemyDamage,string mySkill, string yourSkill) {//myDamage 내가 상대에게 주는 damage, 이기면 1 지면 -1 리턴 비기면 0
    int mySpeed = stoi(mine.getStat()[5])+31;
    int enemySpeed = stoi(enemy.getStat()[5])+31;
    int count = 1;
    int myHp = stoi(mine.getStat()[0])+86;
    int enemyHp = stoi(enemy.getStat()[0])+86;

    if (mySpeed > enemySpeed) {
        while (count <= 20) {
            cout << "your pokemon used " << mySkill << " to enemy" << endl;
            int temp1;
            if (enemyHp - myDamage < 0) {
                temp1 = 0;
            }
            else {
                temp1 = enemyHp - myDamage;
            }
            cout << "enemy's hp is decreased from " << enemyHp << " to " << temp1 << endl;

            if (temp1 == 0) {
                cout <<"\n";
                cout << "you defeated the enemy" << endl;
                return 1;
            }
            enemyHp = temp1;


            cout << "enemy used " << yourSkill << " to your pokemon" << endl;
            int temp2;
            if (myHp - enemyDamage < 0) {
                temp2 = 0;
            }
            else {
                temp2 = myHp - enemyDamage;
            }
            cout << "your hp is decreased from " << myHp << " to " << temp2 << endl;
            if (temp2 == 0) {
                cout <<"\n";
                cout << "enemy defeated you" << endl;
                return -1;
            }
            myHp = temp2;
            count++;
        }
        if (myHp > enemyHp) {
            cout <<"\n";
            cout << "you defeated the enemy" << endl;
            return 1;
        }
        else if (myHp < enemyHp) {
            cout << "\n";
            cout << "enemy defeated you" << endl;
            return -1;
        }
        else {
            cout << "\n";
            cout << "draw" << endl;
            return 0;
        }
    }
    else if (mySpeed < enemySpeed) {
        while (count <= 20) {
            cout << "enemy used " << yourSkill << " to your pokemon" << endl;
            int temp2;
            if (myHp - enemyDamage < 0) {
                temp2 = 0;
            }
            else {
                temp2 = myHp - enemyDamage;
                
            }
            cout << "your hp is decreased from " << myHp << " to " << temp2 << endl;
            if (temp2 == 0) {
                cout << "\nenemy defeated you" << endl;
                return -1;
            }
            myHp = temp2;
            

            cout << "your pokemon used " << mySkill << " to enemy" << endl;
            int temp1;
            if (enemyHp - myDamage < 0) {
                temp1 = 0;
            }
            else {
                temp1 = enemyHp - myDamage;
                
            }
            cout << "enemy's hp is decreased from " << enemyHp << " to " << temp1 << endl;

            if (temp1 == 0) {
                cout<<"\n";
                cout << "you defeated the enemy" << endl;
                return 1;
            }
            enemyHp = temp1;

            count++;

        }
        if (myHp > enemyHp) {
            cout<<"\n";
            cout << "you defeated the enemy" << endl;
            return 1;
        }
        else if (myHp < enemyHp) {
            cout<<"\n";
            cout << "enemy defeated you" << endl;
            return -1;
        }
        else {
            cout<<"\n";
            cout << "draw" << endl;
            return 0;
        }
    }
    else {
        while (count <= 20) {
            int num = (rand() % 2) + 1;
            if (num == 1) {
                cout << "enemy used " << yourSkill << " to your pokemon" << endl;
                int temp2;
                if (myHp - enemyDamage < 0) {
                    temp2 = 0;
                }
                else {
                    temp2 = myHp - enemyDamage;
                }
                cout << "your hp is decreased from " << myHp << " to " << temp2 << endl;
                if (temp2 == 0) {
                    cout<<"\n";
                    cout << "enemy defeated you" << endl;
                    return -1;
                }
                myHp = temp2;


                cout << "your pokemon used " << mySkill << " to enemy" << endl;
                int temp1;
                if (enemyHp - myDamage < 0) {
                    temp1 = 0;
                }
                else {
                    temp1 = enemyHp - myDamage;
                    
                }
                cout << "enemy's hp is decreased from " << enemyHp << " to " << temp1 << endl;

                if (temp1 == 0) {
                    cout<<"\n";
                    cout << "you defeated the enemy" << endl;
                    return 1;
                }
                enemyHp = temp1;

                count++;
            }
            else {
                cout << "your pokemon used " << mySkill << " to enemy" << endl;
                int temp1;
                if (enemyHp - myDamage < 0) {
                    temp1 = 0;
                }
                else {
                    temp1 = enemyHp - myDamage;
                    
                }
                cout << "enemy's hp is decreased from " << enemyHp << " to " << temp1 << endl;

                if (temp1 == 0) {
                    cout<<"\n";
                    cout << "you defeated the enemy" << endl;
                    return 1;
                }
                enemyHp = temp1;


                cout << "enemy used " << yourSkill << " to your pokemon" << endl;
                int temp2;
                if (myHp - enemyDamage < 0) {
                    temp2 = 0;
                }
                else {
                    temp2 = myHp - enemyDamage;
                }
                cout << "your hp is decreased from " << myHp << " to " << temp2 << endl;
                if (temp2 == 0) {
                    cout<<"\n";
                    cout << "enemy defeated you" << endl;
                    return -1;
                }
                myHp = temp2;
                count++;
            }
        }
        if (myHp > enemyHp) {
            cout<<"\n";
            cout << "you defeated the enemy" << endl;
            return 1;
        }
        else if (myHp < enemyHp) {
            cout<<"\n";
            cout << "enemy defeated you" << endl;
            return -1;
        }
        else {
            cout<<"\n";
            cout << "draw" << endl;
            return 0;
        }
    }
}

void overwhelm(MyPokemon& mine, MyPokemon& enemy) {
    for (int i = 0; i < 6; i++) {
        if (stoi(mine.getStat()[i]) < stoi(enemy.getStat()[i])) {
            mine.setstat(enemy.getStat()[i],i);
        }
    }
}

MyPokemon generateNewOne(int id) {//포켓몬 id를 받으면 새로운 클래스 객체 생성
    std::vector<string> enemy_character = getPokemonCharacter(id);
    std::vector<string> evolved = getPokemon_canbeEvolved(id);
    std::vector<string> stat = getPokemonStat(id);
    std::vector<string> type = getPokemonType_asString(id);
    std::vector<vector<string>> skill ;
    MyPokemon newone(enemy_character, evolved, stat, skill);
    return newone;
}

int getId(string charname) {
    std::vector<string> p_character;
    std::ifstream getpokeName;
    getpokeName.open("pokeDB/pokemon_species.csv");
    //주소변경
    std::stringstream ss;
    std::string line;
    getline(getpokeName, line, '\n');//첫번째 줄 삭제 작업
    line.clear();
    while (getline(getpokeName, line, '\r')) {
        line = line + ",";
        ss << line;
        std::string id;
        std::string name;
        std::string evolves_from_id;
        std::string evolution_chain_id;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, evolves_from_id, ',');
        getline(ss, evolution_chain_id, ',');
        if (name.compare(charname) == 0) {
            getpokeName.close();
            return stoi(id);
        }
        ss.str("");
        getline(getpokeName, line, '\n');
        line.clear();
    }
    return 0;
}