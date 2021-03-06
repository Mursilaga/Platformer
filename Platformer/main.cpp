#include "level.h"
#include <Box2D\Box2D.h>

#include <iostream>
#include <random>

enum ret
{
	win,
	lose,
	close
};

int playlvl(Level lvl)
{

	Object player;
	b2Body* playerBody;

	std::vector<Object> coin;
	std::vector<Object> heart;

	std::vector<b2Body*> coinBody;
	std::vector<b2Body*> heartBody;

	std::vector<Object> enemy;
	std::vector<b2Body*> enemyBody;

	std::vector<Object> spike;
	std::vector<b2Body*> spikeBody;

	b2Vec2 gravity(0.0f, 2.0f);
	b2World world(gravity);

	sf::Vector2i tileSize = lvl.GetTileSize();

	std::vector<Object> block = lvl.GetObjects("block");
	for (int i = 0; i < block.size(); i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_staticBody;
		bodyDef.position.Set(block[i].rect.left + tileSize.x / 2 * (block[i].rect.width / tileSize.x - 1),
			block[i].rect.top + tileSize.y / 2 * (block[i].rect.height / tileSize.y - 1));
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(block[i].rect.width / 2, block[i].rect.height / 2);
		body->CreateFixture(&shape, 1.0f);
	}

	coin = lvl.GetObjects("coin");
	for (int i = 0; i < coin.size(); i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(coin[i].rect.left + tileSize.x / 2 * (coin[i].rect.width / tileSize.x - 1),
			coin[i].rect.top + tileSize.y / 2 * (coin[i].rect.height / tileSize.y - 1));
		bodyDef.fixedRotation = true;
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(coin[i].rect.width / 2, coin[i].rect.height / 2);
		body->CreateFixture(&shape, 1.0f);
		coinBody.push_back(body);
	}

	heart = lvl.GetObjects("heart");
	for (int i = 0; i < heart.size(); i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(heart[i].rect.left + tileSize.x / 2 * (heart[i].rect.width / tileSize.x - 1),
			heart[i].rect.top + tileSize.y / 2 * (heart[i].rect.height / tileSize.y - 1));
		bodyDef.fixedRotation = true;
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(heart[i].rect.width / 2, heart[i].rect.height / 2);
		body->CreateFixture(&shape, 1.0f);
		heartBody.push_back(body);
	}

	enemy = lvl.GetObjects("enemy");
	for (int i = 0; i < enemy.size(); i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(enemy[i].rect.left +
			tileSize.x / 2 * (enemy[i].rect.width / tileSize.x - 1),
			enemy[i].rect.top + tileSize.y / 2 * (enemy[i].rect.height / tileSize.y - 1));
		bodyDef.fixedRotation = true;
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(enemy[i].rect.width / 2, enemy[i].rect.height / 2);
		body->CreateFixture(&shape, 1.0f);
		enemyBody.push_back(body);
	}

	spike = lvl.GetObjects("spike");
	for (int i = 0; i < spike.size(); i++)
	{
		b2BodyDef bodyDef;
		bodyDef.type = b2_dynamicBody;
		bodyDef.position.Set(spike[i].rect.left +
			tileSize.x / 2 * (spike[i].rect.width / tileSize.x - 1),
			spike[i].rect.top + tileSize.y / 2 * (spike[i].rect.height / tileSize.y - 1));
		bodyDef.fixedRotation = true;
		b2Body* body = world.CreateBody(&bodyDef);
		b2PolygonShape shape;
		shape.SetAsBox(spike[i].rect.width / 2, spike[i].rect.height / 2);
		body->CreateFixture(&shape, 1.0f);
		spikeBody.push_back(body);
	}


	player = lvl.GetObject("player");
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(player.rect.left, player.rect.top);
	bodyDef.fixedRotation = true;
	playerBody = world.CreateBody(&bodyDef);
	b2PolygonShape shape; shape.SetAsBox(player.rect.width / 2, player.rect.height / 2);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f; fixtureDef.friction = 0.3f;
	playerBody->CreateFixture(&fixtureDef);



	sf::Vector2i screenSize(800, 600);

	sf::RenderWindow window;
	window.create(sf::VideoMode(screenSize.x, screenSize.y), "Adventures of little red star");


	sf::View view;
	view.reset(sf::FloatRect(0.0f, 0.0f, screenSize.x, screenSize.y));
	view.setViewport(sf::FloatRect(0.0f, 0.0f, 2.0f, 2.0f));

	while (window.isOpen())
	{
		sf::Event evt;

		while (window.pollEvent(evt))
		{
			switch (evt.type)
			{
			case sf::Event::Closed:
			{
				window.close();
				return close;
				break;
			}
			case sf::Event::KeyReleased:
			{
				if (evt.key.code == sf::Keyboard::D ||
					evt.key.code == sf::Keyboard::Right ||
					evt.key.code == sf::Keyboard::A ||
					evt.key.code == sf::Keyboard::Left)
				{
					playerBody->SetLinearVelocity(b2Vec2(0.0f, playerBody->GetLinearVelocity().y));
				}
				if (evt.key.code == sf::Keyboard::W)
				{
					playerBody->SetLinearVelocity(b2Vec2(playerBody->GetLinearVelocity().x, 0.0f));
				}
				break;
			}
			case sf::Event::KeyPressed:
			{
				if ((evt.key.code == sf::Keyboard::W && playerBody->GetLinearVelocity().y == 0) ||
					(evt.key.code == sf::Keyboard::Up && playerBody->GetLinearVelocity().y == 0))
				{
					playerBody->SetLinearVelocity(b2Vec2(playerBody->GetLinearVelocity().x, -30.0f));
				}

				if (evt.key.code == sf::Keyboard::D || evt.key.code == sf::Keyboard::Right)
				{
					playerBody->SetLinearVelocity(b2Vec2(8.0f, playerBody->GetLinearVelocity().y));
				}

				if (evt.key.code == sf::Keyboard::A || evt.key.code == sf::Keyboard::Left)
				{
					playerBody->SetLinearVelocity(b2Vec2(-8.0f, playerBody->GetLinearVelocity().y));
				}

				if (evt.key.code == sf::Keyboard::S || evt.key.code == sf::Keyboard::Down)
				{
					playerBody->SetLinearVelocity(b2Vec2(playerBody->GetLinearVelocity().x, 50.0f));
				}
				break;
			}
			}
		}

		world.Step(1.0f / 45.0f, 1, 1);


		for (b2ContactEdge* ce = playerBody->GetContactList(); ce; ce = ce->next)
		{
			b2Contact* c = ce->contact;

			for (int i = 0; i < coinBody.size(); i++)
				if (c->GetFixtureA() == coinBody[i]->GetFixtureList())
				{
					coinBody[i]->DestroyFixture(coinBody[i]->GetFixtureList());
					coin.erase(coin.begin() + i);
					coinBody.erase(coinBody.begin() + i);
				}

			for (int i = 0; i < spikeBody.size(); i++)
				if (c->GetFixtureA() == spikeBody[i]->GetFixtureList())
				{
					window.close();
					return lose;
				}

			for (int i = 0; i < heartBody.size(); i++)
				if (c->GetFixtureA() == heartBody[i]->GetFixtureList())
				{
					heartBody[i]->DestroyFixture(heartBody[i]->GetFixtureList());
					heart.erase(heart.begin() + i);
					heartBody.erase(heartBody.begin() + i);
					window.close();
					return win;
				}

			for (int i = 0; i < enemyBody.size(); i++)
				if (c->GetFixtureA() == enemyBody[i]->GetFixtureList())
				{
					if (playerBody->GetPosition().y < enemyBody[i]->GetPosition().y)
					{
						playerBody->SetLinearVelocity(b2Vec2(playerBody->GetLinearVelocity().x, -6.0f));

						enemyBody[i]->DestroyFixture(enemyBody[i]->GetFixtureList());
						enemy.erase(enemy.begin() + i);
						enemyBody.erase(enemyBody.begin() + i);
					}
					else
					{
						int tmp = (playerBody->GetPosition().x < enemyBody[i]->GetPosition().x)
							? -1 : 1;
						playerBody->SetLinearVelocity(b2Vec2(10.0f * tmp, 0.0f));
						window.close();
						return lose;
					}
				}
		}

		for (int i = 0; i < enemyBody.size(); i++)
		{
			if (enemyBody[i]->GetLinearVelocity() == b2Vec2_zero)
			{
				int tmp = (rand() % 2 == 1) ? 1 : -1;
				enemyBody[i]->SetLinearVelocity(b2Vec2(5.0f * tmp, 0.0f));
			}
		}


		b2Vec2 pos = playerBody->GetPosition();
		view.setCenter(pos.x + screenSize.x / 4, pos.y + screenSize.y / 4);
		window.setView(view);

		player.sprite.setPosition(pos.x, pos.y);

		for (int i = 0; i < coin.size(); i++)
			coin[i].sprite.setPosition(coinBody[i]->GetPosition().x, coinBody[i]->GetPosition().y);

		for (int i = 0; i < enemy.size(); i++)
			enemy[i].sprite.setPosition(enemyBody[i]->GetPosition().x, enemyBody[i]->GetPosition().y);

		for (int i = 0; i < spike.size(); i++)
			spike[i].sprite.setPosition(spikeBody[i]->GetPosition().x, spikeBody[i]->GetPosition().y);

		window.clear();

		lvl.Draw(window);

		window.draw(player.sprite);

		for (int i = 0; i < coin.size(); i++)
			window.draw(coin[i].sprite);

		for (int i = 0; i < heart.size(); i++)
			window.draw(heart[i].sprite);

		for (int i = 0; i < enemy.size(); i++)
			window.draw(enemy[i].sprite);

		for (int i = 0; i < spike.size(); i++)
			window.draw(spike[i].sprite);


		window.display();
	}

}

int main()
{
	int lvlnum = 1;
	int ret_code;
	srand(time(NULL));

	while (true)
	{
		errno_t err;
		std::string mapname = "..\\level" + std::to_string(lvlnum) + ".tmx";

		FILE *fo;
		err = fopen_s(&fo, mapname.c_str(), "r");
		if (err != 0)
		{
			std::cout << "file " << mapname << " not found" << std::endl;
			_sleep(5000);
			break;
		}
		Level lvl;
		lvl.LoadFromFile(mapname);

		ret_code = playlvl(lvl);
		switch (ret_code)
		{
		case win:
			lvlnum++;
			break;
		case lose:
			lvlnum = 1;
			break;
		case close:
			return 0;
		}
	}

	return 0;
}