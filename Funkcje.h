#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <vector>
#include <algorithm>


struct BoundsSpace
{
	int top;
	int left;
	int widh;
	int height;
};
struct Dane
{
	std::string nik;
	int punkty;
};

class Hero : public sf::Sprite
{
public:
	Hero() {};
	~Hero() {};
	Hero(double x, double y);
	int  HP();
	bool ile_hp();
	void Hero_oberwal();
	virtual void setSpeed(int x);
	virtual void animate(const sf::Time& elapsed);
	void getBounds(int left, int right, int top, int bootom);

protected:
	int hp = 3;
	int speed_x;
	sf::Texture texture;
	BoundsSpace boundspace;
};

class Pocisk :public sf::CircleShape
{
public:
	Pocisk();
	~Pocisk() {};
	bool jaki_strzal;
	int getSpeed_x();
	int getSpeed_y();
	void setSpeed_x(int x);
	void setSpeed_y(int y);
	void setSpeed(int x, int y);
private:
	int r = 6;
	int speed_x = 0;
	int speed_y = 300;
};

class Enemy : public Hero
{
public:
	Enemy(sf::Vector2f position);
	~Enemy() {};
	void obrut();
	int getSpeed_x();
	void nadaj_texture();
	void przyspiesz_x(int s);
	void przyspiesz_y(int y);
	void animate(const sf::Time& elapsed, float& stala);
protected:
	int speed_y = 10;
	int speed_x_ = 200;

};
class Serce : public sf::Sprite
{
public:
	Serce() {};
	~Serce() {};
	void nadajtexture(double y, int i);

protected:
	sf::Texture texture;

};
class Dowodca :public Hero
{
public:
	Dowodca(double& x);
	~Dowodca() {};
	int getSpeed() { return speed_x; }
	void setSpeed(int x);
	void animate(sf::Time& elapsed, double& x, double& timer);
protected:
};



void animated(std::vector<Pocisk>& pociski, sf::Time& elapsed, sf::RenderWindow& window);
void colision_bulets(std::vector<Pocisk>& pociski, double y);
void colision_e(std::vector<Enemy>& e, double x, const sf::Time& elapsed, float& count);
void colision_b_d(std::vector<Enemy>& e, std::vector<Pocisk>& p, Dowodca& d, double& x, int& punkty, double& timer_d);
void colision_h_e(std::vector<Enemy>& e, Hero& hero);
void colision_b_e(std::vector<Enemy>& e, std::vector<Pocisk>& p, int& punkty);
void colision_eb_hero(std::vector<Pocisk>& p_e, Hero& hero);
void enemy_strzal(std::vector<Enemy>& e, std::vector<Pocisk>& p_e, const sf::Time& elapsed, double& timer);
void make_enemy(std::vector<Enemy>& e, double& x, double& y, int& ilosc);
void serduszka(std::vector<Serce>& rzycko, Hero& hero, double y);
void gra_start(std::vector<Enemy>& e, double& x, double& y, int& i, float& stala);
void setTlo(sf::Sprite& a, sf::Texture& texture, double& x, double& y);
void odczyt(std::vector<Dane>& d);
void zapis(std::vector<Dane>& d);