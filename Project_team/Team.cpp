﻿#include "Team.h"

Team::Team () {

	 m_Name = "Unknown";
	 m_ID = "Unknown";
	 m_EstablishedDate = "Unknown";
	 m_Stadium = new Stadium();
	 this->numSponsors = 0;
	 this->numPlayers = 0;
	 m_Coach = new Coach();
}

Team::Team(string n, string i,string b)
{
	m_Name = n;
	m_ID = i;
	m_EstablishedDate = b;
	m_Stadium = new Stadium();
	numSponsors = 0;
	numPlayers = 0;
	m_Coach = new Coach();
}

Team::~Team() 
{

}

void Team::Output()
{
	printInfo();
	cout << endl;
	printAchievements();
	cout << endl;
	cout << endl;
	cout << "Current coach: " << m_Coach->getName() << endl;
}

void Team::printPlayersList()
{
	cout <<"Number player: "<< numPlayers << endl;
	if (numPlayers > 0)
	{
		cout << "List of players in my teams: " << endl;
		for (int i = 0; i < numPlayers; i++)
		{
			m_Player[i]->Output();
			cout << endl;
		}
	}
	else
	{
		cout << "There is no player in your team!" << endl;
	}
}

void Team::printInfo() {
	cout << "Name of team: " << m_Name << endl;
	cout << "ID: " << m_ID << endl;
	cout << "Established Date: " << m_EstablishedDate << endl;
}

void Team::printAchievements() {
	if (numAchievement > 0)
	{
		cout << "Achievements we have got:" << endl;
		for (int i = 0; i < numAchievement; i++)
			cout << m_Achievements[i] << endl;
	}
}

void Team::setStadium(Stadium * s)
{
	if (m_Stadium != NULL)
	{
		delete m_Stadium;
	}
	m_Stadium = s;
	
}

void Team::setStadium()
{
	if (m_Stadium != NULL)
	{
		delete m_Stadium;
	}
	m_Stadium = new Stadium;
	m_Stadium->Input();

}



int Team::getNumPlayers()
{
	return this->numPlayers;
}
Finance& Team::getFinance()
{
	return *this->m_Finance;
}

void Team::addPerson() {
	Person * p;
	int ch;
	cout << "Position that you want to recruit: ";
	do
	{
		cout << endl << "(1: Coach; 2: Player)";
		cin >> ch;
	} while (ch > 2);
	cin.ignore(1);
	if (ch == 1)
	{
		p = new Coach();
	}
	else
	{
		p = new Player();
		m_Player.push_back((Player *) p);
		numPlayers++;

	}
	p->Input();
	cout << "Position that you want to recruit " << endl;
	do
	{
		cout << endl << "(1: Coach; 2: Player): ";
		cin >> ch;
	} while (ch > 2 || ch < 1);
	cin.ignore(1);
	if (ch == 1)
	{
		string answer;
		do {
			cout << "To Recruit a new coach, you have to fire the coach working in your team, do you sure about this? (Y/N):";
			getline(cin, answer);
		} while (answer != "Y" && answer != "y" && answer != "N" && answer != "n" && answer != "Yes" &&
			answer != "yes" && answer != "No" && answer != "no");
		if (answer == "Yes" || answer == "yes" || answer == "YES" || answer == "Y" || answer == "y")
		{
			p = new Coach();
			p->Input();
			m_Coach = (Coach *)p;
		}
		else
			return;
	}
	else
	{
		int num = 0;
		do {
			cout << "Enter number of players you want to recruit:";
			cin >> num;
			cin.ignore();
			if (num <= 0)
				cout << "Number of players you want to recruit has to be an positive integer." << endl;
		} while (num <= 0);
		for (int i = 0; i < num; i++)
		{
			p = new Player();
			p->Input();
			m_Player.push_back((Player *)p);
			numPlayers++;
		}
	}

}

void Team::Dissolution() {
	// -------------------- //

	// Hàm này đéo cứu được //

	// -------------------- //
	m_Name = "Unknown";
	m_ID = "Unknown";
	m_EstablishedDate = "Unknown";
	m_Sponsors.clear();
	m_Player.clear();
	m_Achievements.clear();
}	  

double Team::calcTotalSalary()
{
	double total=0;
	for(int i=0; i< this->numPlayers; i++)
		total+= this->m_Player[i]->getSalary();
	total+= m_Coach->getSalary();
	return total;
}

void Team::setFinanceBudget(double bud)
{
	this->m_Finance-> addMoney(bud);
}

double Team::getFinanceBudget()
{
	return this->m_Finance->getBudget();
}

void Team::Input()
{
	cout << "Enter team's name: ";
	cin.ignore();
	getline(cin, m_Name);

	cout << "Enter ID: ";
	cin.ignore();
	getline(cin, m_ID);


	cout << "Enter date of establishment: ";
	cin.ignore();
	getline(cin, m_EstablishedDate);

	cout << "Enter number of sponsors: ";
	cin >> numSponsors;
;
	for (int i = 0; i < numSponsors; i++)
	{
		Person * p = new Person;
		p->Input();
		m_Sponsors.push_back(p);
	}


}

void Team::inputPlayersList()
{
	// Tạo danh sách Players //
	cout << "Enter number of players: ";
	cin >> this->numPlayers;
	cin.ignore(1);
	for (int i = 0; i < this->numPlayers; i++)
	{
		Player * p = new Player();
		p->Input();
		m_Player.push_back(p);
	}

}

void Team::FirePlayer(string id)
{
	bool found = false;
		for (int i = 0; i < this->numPlayers; i++)
		{
			if (this->numPlayers == 0)
				break;
			else
				if (this->m_Player[i]->getID().compare(id) == 0)
				{
					this->m_Player.erase(this->m_Player.begin() + i);
					found = true;
					this->numPlayers--;
				}
		}
		if(this->numPlayers==0)
				cout << " All the player in the team has been fired." << endl;
		if (!found)
			cout << "You have entered the id that does not exist." << endl;
}

void Team::FireCoach()
{
	if (m_Coach != NULL)
		delete m_Coach;
	this->m_Coach = new Coach();
}

void Team::RecruitPlayer()
{
	int num = 0;
	do {
		cout << "Enter number of players you want to recruit:";
		cin >> num;
		if (num <= 0)
			cout << "Number of players you want to recruit has to be an positive integer." << endl;
	} while (num <= 0);
	for (int i = 0; i < num; i++)
	{
		Player *p = new Player;
		p->Input();
		m_Player.push_back(p);
	}
}

