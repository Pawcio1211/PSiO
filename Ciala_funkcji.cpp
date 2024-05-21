#include "Funkcje.h"

//_______________________HERO_______________________

Hero::Hero(double x, double y)
{
	if (!texture.loadFromFile("tekstury/statek.png"))
	{
		std::cout << "nie wczytana textura" << std::endl;
	}
	setTexture(texture);
	setScale(0.5, 0.5);
	sf::FloatRect bounds = getGlobalBounds();
	setPosition(sf::Vector2f((x - bounds.width) / 2, y - bounds.height - 50));
}
int Hero::HP()
{
	return hp;
}

bool Hero::ile_hp()
{
	if (hp < 1)
		return true;
	else
		return false;
}

void Hero::Hero_oberwal()
{
	hp -= 1;
}

void Hero::setSpeed(int x)
{
	speed_x = x;
}



void Hero::animate(const sf::Time& elapsed)
{
	sf::FloatRect bounds = getGlobalBounds();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		if (bounds.left >= boundspace.left)
		{
			move(-speed_x * elapsed.asSeconds(), 0);
		}
		if (!texture.loadFromFile("tekstury/statek 2_l.png"))
		{
			std::cout << "nie wczytana textura" << std::endl;
		}
		setTexture(texture);
		setScale(0.5, 0.5);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (bounds.left + bounds.width <= boundspace.widh)
			move(speed_x * elapsed.asSeconds(), 0);
		if (!texture.loadFromFile("tekstury/statek 2_p.png"))
		{
			std::cout << "nie wczytana textura" << std::endl;
		}
		setTexture(texture);
		setScale(0.5, 0.5);
	}

	else
	{
		if (!texture.loadFromFile("tekstury/statek.png"))
		{
			std::cout << "nie wczytana textura" << std::endl;
		}
		setTexture(texture);
		setScale(0.5, 0.5);
	}
}

void Hero::getBounds(int left, int right, int top, int bootom)
{
	boundspace.left = left;
	boundspace.widh = right;
	boundspace.top = top;
	boundspace.height = bootom;
}
//_______________________POCISK_______________________

Pocisk::Pocisk() :CircleShape(r)
{
	setFillColor(sf::Color::Red);
}

int Pocisk::getSpeed_x()
{
	return speed_x;
}

int Pocisk::getSpeed_y()
{
	return speed_y;
}
void Pocisk::setSpeed_x(int x)
{
	speed_x = x;
}

void Pocisk::setSpeed_y(int y)
{
	speed_y = y;
}

void Pocisk::setSpeed(int x, int y)
{
	speed_x = x; speed_y = y;
}

void colision_bulets(std::vector<Pocisk>& pociski, double y)
{
	for (size_t i = 0; i < pociski.size(); i++)
	{

		if (pociski[i].getPosition().y < 0 && pociski[i].jaki_strzal == true)
		{
			pociski.erase(pociski.begin() + i);
			//std::cout << "Pocisk usuniêty";
		}
		else if (pociski[i].getPosition().y < y / 1.5 && pociski[i].jaki_strzal == false)
		{
			pociski.erase(pociski.begin() + i);
		}
	}
};

void animated(std::vector<Pocisk>& pociski, sf::Time& elapsed, sf::RenderWindow& window)
{
	if (!pociski.empty())
	{
		for (int i = 0; i < pociski.size(); i++)
		{
			window.draw(pociski[i]);
			pociski[i].move(pociski[i].getSpeed_x() * elapsed.asSeconds(),
				-pociski[i].getSpeed_y() * elapsed.asSeconds());
		}
	}
}

//_______________________ENEMY_______________________

Enemy::Enemy(sf::Vector2f position)
{
	setPosition(position);
}


void Enemy::obrut()
{
	speed_x_ = -speed_x_;
}

int Enemy::getSpeed_x()
{
	return speed_x_;
}

void Enemy::nadaj_texture()
{
	if (!texture.loadFromFile("tekstury/enemy_2.png"))
	{
		std::cout << "nie wczytana textura enemy" << std::endl;
	}
	setTexture(texture);
}


void Enemy::przyspiesz_x(int s)
{
	if (speed_x_ > 0)
	{
		speed_x_ += s;
		//std::cout << speed_x_ << std::endl;
	}
	else
	{
		speed_x_ -= s;
		//std::cout << speed_x_ << std::endl;
	}
}
void Enemy::przyspiesz_y(int y)
{
	speed_y += y;

}



void Enemy::animate(const sf::Time& elapsed, float& stala)
{
	if (stala > 0)
	{
		move(0, 430 * elapsed.asSeconds());
		stala -= elapsed.asSeconds();
		//std::cout<<stala<<std::endl;
	}
	else
	{
		move(speed_x_ * elapsed.asSeconds(), speed_y * elapsed.asSeconds());
	}
}


void make_enemy(std::vector<Enemy>& e, double& x, double& y, int& ilosc)
{
	int ile_rzedow = 6;
	int ile_kolumn = 7;
	int przyspieszenie_x = 5 * ile_kolumn * ile_rzedow;
	for (int rzad = 0; rzad < 4; rzad++)
	{
		for (int kolumny = 0; kolumny < 7; kolumny++)
		{
			Enemy enemy(sf::Vector2f(((x / 10) * kolumny) + 284, (-90 * rzad) - 40));
			enemy.getBounds(0, x, 0, y);
			enemy.przyspiesz_x(przyspieszenie_x * ilosc);
			enemy.przyspiesz_y(10 * ilosc);
			e.push_back(enemy);
		}
	}
	ilosc++;
}


void colision_e(std::vector<Enemy>& e, double x, const sf::Time& elapsed, float& count)
{
	count += elapsed.asSeconds();
	if (count > 0.2)
	{
		for (int i = 0; i < e.size(); i++)
		{
			sf::FloatRect bounds = e[i].getGlobalBounds();


			if (bounds.left <= 0)
			{
				for (int i = 0; i < e.size(); i++)
				{
					e[i].obrut();
					count = 0;
				}
				break;
			}
			if (bounds.left + bounds.width >= x)
			{
				for (int i = 0; i < e.size(); i++)
				{
					e[i].obrut();
					count = 0;
				}
				break;
			}

		}
	}


}

void enemy_strzal(std::vector<Enemy>& e, std::vector<Pocisk>& p_e, const sf::Time& elapsed, double& timer)
{
	if (!e.size() == 0)
	{
		timer += elapsed.asSeconds();
		//std::cout << timer<<std::endl;
		bool bezpiecznik = true;
		int a;
		if (timer > 1)
		{
			while (bezpiecznik)
			{


				for (int i = 0; i < rand() % 5 + 1; i++)
				{


					Pocisk p;
					p.setSpeed_y(-300);
					p.setFillColor(sf::Color::Yellow);
					int liczba = rand() % e.size();
					sf::FloatRect bounds = e[liczba].getGlobalBounds();
					p.setPosition(bounds.left + (bounds.width / 2), bounds.top + bounds.height);
					sf::FloatRect bounds_p = p.getGlobalBounds();
					if (bounds_p.top < 0)
						p.~Pocisk();
					else
					{
						bezpiecznik = false;
						p_e.push_back(p);
						timer = 0;
					}

				}


			}
		}
	}
}
void gra_start(std::vector<Enemy>& e, double& x, double& y, int& i, float& stala)
{
	if (e.size() == 0)
	{
		make_enemy(e, x, y, i);
		for (int i = 0; i < e.size(); i++)
		{
			e[i].nadaj_texture();
		}
		stala = 22;
	}
}

//_______________________SERCA_______________________

void Serce::nadajtexture(double y, int i)
{
	if (!texture.loadFromFile("tekstury/serce_2.1.png"))
	{
		std::cout << "nie wczytana textura serce" << std::endl;
	}
	setTexture(texture);
	setScale(0.05, 0.05);
	sf::FloatRect bounds = getGlobalBounds();
	setPosition(sf::Vector2f(bounds.width * i, y - bounds.height));
}
void serduszka(std::vector<Serce>& rzycko, Hero& hero, double y)
{
	for (int i = 0; i < hero.HP(); i++)
	{
		Serce s;
		rzycko.push_back(s);
	}
	for (int i = 0; i < rzycko.size(); i++)
	{
		rzycko[i].nadajtexture(y, i);
	}
}
//_______________________DOWODCA_______________________
Dowodca::Dowodca(double& x)
{
	if (!texture.loadFromFile("tekstury/ufo.png"))
	{
		std::cout << "nie wczytana textura Dowodcy" << std::endl;
	}
	setTexture(texture);
	setScale(0.5, 0.5);
	sf::FloatRect bounds = getGlobalBounds();
	setPosition(sf::Vector2f(x, 0));
	speed_x = -300;
}
void Dowodca::animate(sf::Time& elapsed, double& x, double& timer_d)
{
	//std::cout << timer_d << std::endl;
	sf::FloatRect bounds = getGlobalBounds();
	if (timer_d < 0.0f)
	{
		move(speed_x * elapsed.asSeconds(), 0);
		if (timer_d < 0.0f)
		{
			if (bounds.left < 0)
			{
				speed_x = -speed_x;
				setPosition(0, 0);

			}
			if (bounds.left > x)
			{
				setPosition(x, 0);
				timer_d = rand() % 30 + 1;
				speed_x = -speed_x;
			}
		}
	}
	else
	{
		timer_d -= elapsed.asSeconds();
	}
}
//_______________________VEKTORY INNE_______________________

void colision_b_e(std::vector<Enemy>& e, std::vector<Pocisk>& p, int& punkty)
{
	int ile = e.size();
	bool blokada = false;
	for (int po = 0; po < p.size(); po++)
	{
		sf::FloatRect bounds = p[po].getGlobalBounds();
		for (int en = 0; en < e.size(); en++)
		{
			if (bounds.intersects(e[en].getGlobalBounds()))
			{
				p.erase(p.begin() + po);
				e.erase(e.begin() + en);
				blokada = true;
				punkty += 10;
			}

		}
	}
	if (blokada)
	{

		for (int i = 0; i < e.size(); i++)
		{
			e[i].przyspiesz_x(5);
			e[i].nadaj_texture();
		}

	}
}
void colision_eb_hero(std::vector<Pocisk>& p_e, Hero& hero)
{
	sf::FloatRect bounds = hero.getGlobalBounds();
	for (int i = 0; i < p_e.size(); i++)
	{
		if (bounds.intersects(p_e[i].getGlobalBounds()))
		{
			hero.Hero_oberwal();
			p_e.erase(p_e.begin() + i);
		}
	}
}
void colision_h_e(std::vector<Enemy>& e, Hero& hero)
{
	bool blokada = false;
	sf::FloatRect bounds = hero.getGlobalBounds();
	for (int i = 0; i < e.size(); i++)
	{
		if (bounds.intersects(e[i].getGlobalBounds()) || e[i].getGlobalBounds().top == 900)
		{
			hero.Hero_oberwal();
			e.erase(e.begin() + i);
			blokada = true;
		}
	}
	if (blokada)
	{
		for (int i = 0; i < e.size(); i++)
		{
			e[i].przyspiesz_x(5);
			e[i].nadaj_texture();
		}
	}
}
void Dowodca::setSpeed(int x)
{
	speed_x += x;
}
void colision_b_d(std::vector<Enemy>& e, std::vector<Pocisk>& p, Dowodca& d, double& x, int& punkty, double& timer_d)
{
	if (timer_d < 0.0f)
	{
		sf::FloatRect bounds = d.getGlobalBounds();
		for (int i = 0; i < p.size(); i++)
		{
			if (bounds.intersects(p[i].getGlobalBounds()))
			{
				punkty += e.size() * 10 + 100;
				d.setPosition(x, 0);
				d.setSpeed(d.getSpeed());
				e.clear();
			}
		}
	}

}

void setTlo(sf::Sprite& a, sf::Texture& texture, double& x, double& y)
{
	if (!texture.loadFromFile("tekstury/galaktyka.jpg"))
	{
		std::cout << "nie wczytana textura serce" << std::endl;
	}
	a.setTexture(texture);
	a.setScale(1.5, 2);
	a.setOrigin(x / 2, y / 2);
	a.setPosition(x / 2, y / 2);
}
//_______________________zapis odczyt_______________________


void zapis(std::vector<Dane>& d)
{
	std::fstream plik;
	plik.open("dane.txt", std::ios::out | std::ios::app);

	for (int i = 0; i < d.size(); i++)
	{
		plik << d[i].nik << std::endl;
		plik << d[i].punkty << std::endl;
	}
	plik.close();
}
void odczyt(std::vector<Dane>& d)
{
	std::fstream plik;
	plik.open("dane.txt", std::ios::in);
	if (plik.good() == false)
	{
		std::cout << "Jeszcze nikt nie gral" << std::endl;
	}
	else
	{
		std::string linia;
		int nr = 1;
		int nr_m = 0;

		while (std::getline(plik, linia))
		{
			Dane d2;
			if (nr % 2)
			{
				d2.nik = linia;
				d.push_back(d2);
			}
			else
			{
				d[nr_m].punkty = atoi(linia.c_str());
				nr_m++;
			}
			nr++;
		}
		std::sort(d.begin(), d.end(), [](const Dane& d, const Dane& a) {return d.punkty > a.punkty; });
	}
	
	plik.close();
}
//______________________gra_________________________