#include <iostream>
#include <queue>
#include <list>
#include <string>
#include <time.h> 
#include "Hero.h"
#include "RoundLog.h"
using namespace std;

int toInteger(string s) 
{
    int num = 0; 

    for (int i = 0; i < s.length(); i++) {
        num = 10 * num + (s[i] - '0');
    }

    return num;

}

void AddToSquad(queue<Hero>& team, Hero hunter, Hero assassin, Hero mage, Hero warrior)
{
    bool isStop = false;
    string parameters;
    while (!isStop)
    {
        parameters = "";
        getline(cin, parameters);
        if (parameters.find(' ') == string::npos)
        {
            if (parameters == "Hunter")
            {
                team.push(hunter);
            }
            else if (parameters == "Assassin")
            {
                team.push(assassin);
            }
            else if (parameters == "Mage")
            {
                team.push(mage);
            }
            else if (parameters == "Warrior")
            {
                team.push(warrior);
            }
            else if (parameters == "stop")
            {
                isStop = true;
            }
            else
            {
                cout << "Invalid input! Follow this example: string int int int." << endl;
                cout << "≈ach team consists of at least one hero!" << endl;
            }
        }
        else
        {
            string name = parameters.substr(0, parameters.find(' '));

            parameters = parameters.substr(parameters.find(' ') + 1);
            int healthPoints = toInteger(parameters.substr(0, parameters.find(' ')));

            parameters = parameters.substr(parameters.find(' ') + 1);
            int damage = toInteger(parameters.substr(0, parameters.find(' ')));
            int armor = toInteger(parameters.substr(parameters.find(' ') + 1));

            Hero hero(name, healthPoints, damage, armor);
            team.push(hero);
        }
    }
}

void Attack(queue<Hero>& attacking“eam, Hero& heroAttackingTeam, queue<Hero>& team, Hero& heroTeam, list<RoundLog>& roundLogs, bool& end, string nameTeamAttacking)
{
    int injury = heroAttackingTeam.getDamage() - heroTeam.getArmor();
    if (injury >= 0)
    {
        if (injury < heroTeam.getHealthPoints())
        {
            heroTeam.setHealthPoints(heroTeam.getHealthPoints() - injury);
            heroTeam.setArmor(0);
            RoundLog roundLog(heroAttackingTeam.getName(), nameTeamAttacking, heroTeam.getName(), injury);
            roundLogs.push_back(roundLog);
        }
        else
        {
            RoundLog roundLog(heroAttackingTeam.getName(), nameTeamAttacking, heroTeam.getName(), injury);
            roundLogs.push_back(roundLog);
            if (team.size() != 0)
            {
                team.pop();
                if (team.size() != 0)
                {
                    heroTeam = team.front();
                }
            }
            if (team.size() == 0)
            {
                end = true;
            }
        }
    }
    else
    {
        heroTeam.setArmor(heroTeam.getArmor() - heroAttackingTeam.getDamage());
        RoundLog roundLog(heroAttackingTeam.getName(), nameTeamAttacking, heroTeam.getName(), injury);
        roundLogs.push_back(roundLog);
    }
}

void Battle(queue<Hero>& teamOne, string nameTeamOne, queue<Hero>& teamTwo, string nameTeamTwo)
{
    list<RoundLog> roundLogs;
    Hero heroTeamOne = teamOne.front();
    Hero heroTeamTwo = teamTwo.front();

    int numberInSeries = 1;
    bool end = false;
    while (!end)
    {
        if (numberInSeries % 2 != 0)
        {
            Attack(teamOne, heroTeamOne, teamTwo, heroTeamTwo, roundLogs, end, nameTeamOne);
        }
        else
        {
            Attack(teamTwo, heroTeamTwo, teamOne, heroTeamOne, roundLogs, end, nameTeamTwo);
        }
        numberInSeries++;
    }

    int size = roundLogs.size();
    string winner = roundLogs.back().getTeam();
    cout << endl;
    cout << "There were " << size << " attacks." << endl;
    for (int i = 0; i < size; i++)
    {
        cout << roundLogs.front() << endl;
        roundLogs.pop_front();
    }

    cout << "The winner is " << winner << ". Congratulations!" << endl;
}

int main()
{
    queue<Hero> firstTeam;
    queue<Hero> secondTeam;

    Hero hunter("Hunter", 450, 55, 30);
    Hero assassin("Assassin", 395, 45, 25);
    Hero mage("Mage", 365, 40, 15);
    Hero warrior("Warrior", 500, 37, 50);
    cout << hunter << assassin << mage << warrior << endl;
    cout << "Choose a hero from the suggested ones or make your own according to the model shown above." << endl;

    cout << "Enter the heroes of the First Team:" << endl;
    AddToSquad(firstTeam, hunter, assassin, mage, warrior);
    cout << "Enter the heroes of the Second Team:" << endl;
    AddToSquad(secondTeam, hunter, assassin, mage, warrior);

    int random = (rand() + time(0)) % 2 + 1;
    if (random == 1)
    {
        Battle(firstTeam, "First Team", secondTeam, "Second Team");
    }
    else
    {
        Battle(secondTeam, "Second Team", firstTeam, "First Team");
    }
}
