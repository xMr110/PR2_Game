#ifndef PLAYER_H
#define PLAYER_H

#include<string>
#include<iostream>
#include<memory>
#include<vector>
#include<map>

using namespace std;

class Game;

enum class Mode{Ranked,Unranked};

class Player:public enable_shared_from_this<Player>{	//HINWEIS: Um shared_pointer vom this-Objekt zu ergeugen, muss die Klasse Player public von Enable_shared_from_this<Player> erben
	string name;
	int mmr;
	shared_ptr<Game> hosted_game;
	map<string, weak_ptr<Game>> games; //Map von Spielen an denen Player teilnimmt
public:
	Player(string name, int mmr);
	string get_name() const
	int get_mmr() const;
	shared_ptr<Game> get_hosted_game() const;
	void change_mmr(int n);
	bool host_game(string s, Mode m);
	bool join_game(shared_ptr<Game> g);
	bool leave_game(shared_ptr<Game> g);
	vector<weak_ptr<Player>> invite_players(const vector<weak_ptr<Player>>& v);
	bool close_game();

	ostream& print(ostream& o) const;	//Format: [name, mmr, hosts: hosted_game_name, games: {Game_name, Game,name, ...}]
	operator<<;	//If hosted_game.empty() soll "nothing" ausgegeben werden. Bsp: [Heinrich, 20, hosts: nothing, games{Sims 4, Sims3, Doom}]

	
}


#endif