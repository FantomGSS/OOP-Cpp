#pragma once
#include<iostream>
using namespace std;

class RoundLog {
private:
	string name;
	string team;
	string victim;
	int injury;

	void copy(const RoundLog& roundLog)
	{
		this->name = roundLog.name;
		this->team = roundLog.team;
		this->victim = roundLog.victim;
		this->injury = roundLog.injury;
	}

public:
	RoundLog();
	RoundLog(string, string, string, int);
	RoundLog(const RoundLog&);
	RoundLog& operator=(const RoundLog&);

	const string getName() const;
	const string getTeam() const;
	const string getVictim() const;
	const int getInjury() const;

	friend ostream& operator<<(ostream&, const RoundLog&);
};

RoundLog::RoundLog() {
	this->name = "";
	this->team = "";
	this->victim = "";
	this->injury = 0;
}

RoundLog::RoundLog(string name, string team, string victim, int injury) {
	this->name = name;
	this->team = team;
	this->victim = victim;
	this->injury = injury;
}

RoundLog::RoundLog(const RoundLog& roundLog) {
	this->copy(roundLog);
}

RoundLog& RoundLog::operator=(const RoundLog& roundLog) {
	if (this != &roundLog) {
		this->copy(roundLog);
	}
	return *this;
}

const string RoundLog::getName() const {
	return this->name;
}

const string RoundLog::getTeam() const {
	return this->team;
}

const string RoundLog::getVictim() const {
	return this->victim;
}

const int RoundLog::getInjury() const {
	return this->injury;
}

ostream& operator<<(ostream& output, const RoundLog& roundLog)
{
	if (roundLog.injury != 0)
	{
		output << roundLog.name << " from the " << roundLog.team << " took " << roundLog.injury << " hp (armor) from " << roundLog.victim << "." << endl;
	}
	else
	{
		output << roundLog.name << " removed " << roundLog.victim << "'s armor. " << roundLog.victim << "'s hp remains unchanged." << endl;
	}
	
	return output;
}