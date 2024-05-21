#include "Funkcje.h"

int main()
{
	std::vector<Dane> dane;
	//menu
	odczyt(dane);
	for (;;)
	{

		char przelacz;
		std::cout << "Nasza flota przeszukuje dronami kosmos w poszukiwaniu surowcow lub planet na ktorych mozemy sie osiedlic." << std::endl;
		std::cout << "Niestety coraz czesciej spotyukamy kosmitow ktorzy sa do nas wrogo nastawieni." << std::endl;
		std::cout << "Twoim zadaniem jest przetrwac jak najdluzej w starciu z tymi potworami i zdobyc jak najwiecej informacji." << std::endl;
		std::cout << "Odkrylismu ze w starciu z przeciwnikiem zawsze kryje sie dowodca po jego zestrzeleniu wroga flota znika." << std::endl;
		std::cout << "No to tyle wstepu powodzenia rekrucie!!! " << std::endl << std::endl << std::endl;
		std::cout << "########################################################################################################################" << std::endl;
		std::cout << "                                     Witaj Rekrucie W Gwiezdnej Flocie           " << std::endl;
		std::cout << "                                        1: Rozpoczni Swoja Przygode" << std::endl;
		std::cout << "                                           2: Tabela Najlepszych" << std::endl;
		std::cout << "                                                 3: Zasady" << std::endl;
		std::cout << "                                                 4: Wyjd�" << std::endl;
		std::cout << "########################################################################################################################" << std::endl;
		std::cin >> przelacz;
		switch (przelacz)
		{
		case '1':
		{
			Dane a;
			system("cls");
			std::cout << "Witamy rekrucie jak sie nazywasz? " << std::endl;; std::cin >> a.nik;
			system("cls");


			//sama gra
			//Pojemniki i sta�e
			std::vector<Pocisk> pociski;
			std::vector<Pocisk> pociski_e;
			std::vector<Enemy> enemys;
			std::vector<Serce> rzycko;
			bool blokada = false;
			bool blokada_2 = false;
			bool bezpieczenstwo = true;
			bool bezpieczenstwo_2 = true;
			int speed_r = 6;
			int it = 5;
			int ilosc_fal = 0;
			int punkty = 0;
			double x = 1500;
			double y = 900;
			double timer = 0;
			double timer_d = 10;
			float count = 0;
			float stala = 22;
			//okno
			sf::RenderWindow window(sf::VideoMode(x, y), "zaliczenie");
			sf::Clock clock;
			window.setFramerateLimit(60);

			//t�o
			sf::Sprite tlo;
			sf::Texture texture;
			setTlo(tlo, texture, x, y);
			//tworzenie bohatera
			Hero hero(x, y);
			hero.setSpeed(200);
			sf::FloatRect bounds = hero.getGlobalBounds();
			hero.getBounds(0, window.getSize().x, 0, window.getSize().y);

			//serduszka
			serduszka(rzycko, hero, y);
			//tworzenie dow�dcy
			Dowodca dowudca(x);
			//tworzenie enemy
			gra_start(enemys, x, y, ilosc_fal, stala);

			while (window.isOpen())
			{
				// EVENTS
				sf::Event event;
				while (window.pollEvent(event)) {
					if (event.type == sf::Event::Closed) {
						window.close();
					}

				}


				// LOGIC
				sf::Time elapsed = clock.restart();
				window.clear(sf::Color::Black);

				tlo.rotate(speed_r * elapsed.asSeconds());
				colision_e(enemys, x, elapsed, count);

				colision_bulets(pociski, y);
				colision_b_e(enemys, pociski, punkty);
				enemy_strzal(enemys, pociski_e, elapsed, timer);
				colision_eb_hero(pociski_e, hero);
				colision_h_e(enemys, hero);
				colision_b_d(enemys, pociski, dowudca, x, punkty, timer_d);
				gra_start(enemys, x, y, ilosc_fal, stala);

				//strzelanie pojedyncze
				if (blokada == false && (sf::Mouse::isButtonPressed(sf::Mouse::Left)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				{
					blokada = true;
					bezpieczenstwo = true;
				}
				if (blokada == true && (!sf::Mouse::isButtonPressed(sf::Mouse::Left) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Space)))
				{
					while (bezpieczenstwo)
					{
						Pocisk p;
						p.jaki_strzal = true;
						p.setPosition(hero.getPosition().x + 32, hero.getPosition().y);
						sf::FloatRect bounds = p.getGlobalBounds();
						if (bounds.top < 0)
						{
							p.~Pocisk();
						}
						else
						{
							bezpieczenstwo = false;
							blokada = false;
							pociski.push_back(p);
						}
					}

				}
				//strzelanie szodgan
				if (blokada_2 == false && (sf::Mouse::isButtonPressed(sf::Mouse::Right)
					|| sf::Keyboard::isKeyPressed(sf::Keyboard::V)))
				{
					blokada_2 = true;
					bezpieczenstwo_2 = true;

					//std::cout << "dziala strzal_2" << std::endl;
				}
				if (blokada_2 == true && (!sf::Mouse::isButtonPressed(sf::Mouse::Right) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::V)))
				{
					for (int i = 0; i < it; i++)
					{
						bezpieczenstwo_2 = true;
						while (bezpieczenstwo_2)
						{
							Pocisk p;
							p.jaki_strzal = false;
							p.setFillColor(sf::Color::Green);
							p.setSpeed(600 - 300 * i, 600);
							p.setPosition(hero.getPosition().x + 32, hero.getPosition().y);
							sf::FloatRect bounds = p.getGlobalBounds();
							if (bounds.top < 0)
							{
								p.~Pocisk();
							}
							else
							{
								pociski.push_back(p);
								bezpieczenstwo_2 = false;
							}
						}
					}


					blokada_2 = false;
					//pociski.push_back(p);
				}






				//ANIMACJE
				window.draw(tlo);
				hero.animate(elapsed);
				animated(pociski, elapsed, window);
				animated(pociski_e, elapsed, window);
				for (int i = 0; i < enemys.size(); i++)
				{
					enemys[i].animate(elapsed, stala);
				}
				dowudca.animate(elapsed, x, timer_d);


				// DRAW
				for (size_t i = 0; i < hero.HP(); i++)
				{
					if (!rzycko.empty())
						window.draw(rzycko[i]);

				}
				window.draw(hero);
				for (int i = 0; i < enemys.size(); i++)
				{
					if (!enemys.empty())
						window.draw(enemys[i]);
				}
				window.draw(dowudca);
				if (hero.ile_hp())
				{
					window.close();
				}

				// end the current frame
				window.display();
			}
			std::string bez;
			do
			{
				std::cout << punkty << std::endl;
				std::cin >> bez;
				system("cls");
			} while (bez != "a");
			a.punkty = punkty;
			dane.push_back(a);
		}break;
		case '2':
		{
			std::sort(dane.begin(), dane.end(), [](const Dane& d, const Dane& a) {return d.punkty > a.punkty; });
			system("cls");
			for (int i = 0; i < dane.size(); i++)
			{
				std::cout << "Nik: " << dane[i].nik << "  " << dane[i].punkty << "p. " << std::endl;
			}
			std::getchar(); std::getchar();
			system("cls");
		}break;
		case '3':
		{
			system("cls");
			std::cout << "Posiadasz 3 zycia i po ich stracie konczy sie rozgrywka. Zycia mozesz stracic z kontakcie z wroga jednostka lub gdy cie trafia." << std::endl;
			std::cout << "Za kazdy zesrzelony statek otrzymujesz 10p. Gdy zestrzelisz dowudce zyskujesz punkty za cala wroga flote + 100p za dowodce." << std::endl;
			std::cout << "Mozesz poruszac sie na boki za pomoca A i D" << std::endl;
			std::cout << "Do dyspozycji masz 2 rodzaje strzalu:" << std::endl;
			std::cout << "Snajperski pojedynczy wolny ale dalekiego zasiegu. po nacisnieciu spacji lub LPM" << std::endl;
			std::cout << "Szotgan szybki z wieloma pociskami ale na krotki dystans. Po naci�nieciu V lub PPM" << std::endl;
			std::cout << "Mam nadzieje ze wszystko zrozumiale :) Powodzenia" << std::endl;
			std::cout << "Nacisni enter aby wyjsc." << std::endl;
			std::getchar(); std::getchar();
			system("cls");
		}break;
		
		case '4':
		{
			zapis(dane);
			exit(0);
		}break;
		default:
			system("cls");
			break;
		}
		zapis(dane);
	}

	return 0;
}