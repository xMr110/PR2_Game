#include "player.h"
#include "game.h"
#include "gamekey.h"
#include<string>
#include<iostream>
#include<memory>
#include<algorithm>
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
	Player(string name, int mmr): name{name}, mmr{mmr} {};
//	string get_name() const;
//	int get_mmr() const;
	shared_ptr<Game> Player::get_hosted_game() const{
		return this->hosted_game;
	}
	void Player::change_mmr(int n){
		if(mmr < 0 || mmr > 9999) {
			return mmr;
		} else
			return mmr + n;
	}
	bool Player::host_game(string s, Mode m) {
		if(s.empty()) throw new runtime_error("empty string!");
		if(hosted_game) return false;
		
		if(m == Mode::Ranked) {
			this->hosted_game = make_shared<RGame>(s, shared_from_this());
		} else if(m == Mode:Unranked) {
			this->hosted_game = make_shared<UGame>(s, shared_from_this());
		}	
		return true;
	}
	bool Player::join_game(shared_ptr<Game> g) {
		string tmpName = g->get.name();
		auto it = games.find(tmpName);
		if(it == games.end()) {
			games.insert({tmpName, g});
			Game emag;
			emag.add_player(const GameKey& gk, shared_ptr<Player> p);	//valjda?
			return true;
		}
		return false;
	}
	bool leave_game(shared_ptr<Game> g) {
		string currentG = g.get_name();
		if(games.find(currentG)) {
			games.erase(currentG);
			delete this->g;
			return true;
		} else
			return false;

	}
	vector<weak_ptr<Player>> invite_players(const vector<weak_ptr<Player>>& v);
	bool close_game();

	ostream& print(ostream& o) const;	//Format: [name, mmr, hosts: hosted_game_name, games: {Game_name, Game,name, ...}]
	operator<<;	//If hosted_game.empty() soll "nothing" ausgegeben werden. Bsp: [Heinrich, 20, hosts: nothing, games{Sims 4, Sims3, Doom}]

	
}
