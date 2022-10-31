#include "mainscene.h"

#include <iostream>
#include <QDebug>
#include <QFontDatabase>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QString>

#include "enemy.h"
#include "player.h"

MainScene::MainScene(QGraphicsView* parent)
	: QGraphicsScene(0, 0, WIN_W, WIN_H, parent) // size
	, m_rng(QRandomGenerator::global())
	, m_keyLeftDown(false)
	, m_keyRightDown(false)
	, m_player(new Player(this, WIN_W / 2, WIN_H - 80))
	, m_updateTimer(new QTimer())
	, m_enemySpawnTimer(new QTimer())
	, m_missiles()
	, m_enemies()
	, m_score(0)
	//, m_lives(3)
	, m_scoreText(nullptr)
	//, m_livesText(nullptr)
	, m_loseText(nullptr)
	, m_running(true)
{
	connect(m_updateTimer, &QTimer::timeout, this, &MainScene::gameUpdate);
	m_updateTimer->setInterval(16); // 16ms ~= 60fps
	m_updateTimer->start();

	connect(m_enemySpawnTimer, &QTimer::timeout, this, &MainScene::spawnEnemy);
	m_enemySpawnTimer->setInterval(1500);
	m_enemySpawnTimer->start();

	// Textes
	loadFont();

	m_scoreText = addText(tr("Score: 0"), m_arcadeFont);
	//m_livesText = addText(tr("Lives: 3"), m_arcadeFont);
	m_scoreText->setPos(30, WIN_H - 50);
	//m_livesText->setPos(WIN_W - 70, WIN_H - 50);

	addItem(m_player);
}

void MainScene::loadFont()
{
	int id = QFontDatabase::addApplicationFont("fonts/Symtext.ttf");
	QString family = QFontDatabase::applicationFontFamilies(id).at(0);
	
	m_arcadeFont = QFont(family, 12);
}

void MainScene::spawnEnemy()
{
	// Entre MIN et MAX inclus
	int spd = m_rng->bounded(ENEMY_MAX_SPD - ENEMY_MIN_SPD + 1) + ENEMY_MIN_SPD;

	int x = m_rng->bounded(WIN_W - 50);

	auto* e = new Enemy(this, x, 0, spd);
	m_enemies.append(e);
	addItem(e);
}

// Tire un missile
void MainScene::shoot()
{
	auto* missile = new Missile(this, m_player->x() + 24, m_player->y()); // X + 24 => centré par rapport au joueur
																		  // 
	m_missiles.append(missile);
	addItem(missile);
}

void MainScene::gameUpdate()
{
	if (m_keyLeftDown)
	{
		m_player->move(-PLAYER_SPD, 0);
	}
	if (m_keyRightDown)
	{
		m_player->move(PLAYER_SPD, 0);
	}

	// Update des missiles
	for (int i = m_missiles.length() - 1; i >= 0; i--)
	{
		auto* m = m_missiles[i];
		m->gameUpdate();

		// Destruction si en dehors de l'écran
		if (!m->inBounds())
		{
			destroyItem(m);
			m_missiles.removeAt(i);
		}
		else
		{
			// Destruction si touche ennemi
			checkMissileCollisions(m);
		}
	}

	// Update des ennemis
	for (int i = m_enemies.length() - 1; i >= 0; i--)
	{
		auto* e = m_enemies[i];
		e->gameUpdate();

		// Si ennemi en dessous de l'écran: -1 vie
		if (e->y() >= WIN_H)
		{
			m_score--;
			m_enemies.removeAt(i);
			destroyItem(e);
		}
	}

	processPlayerEnemyCollision();

	//if (m_lives <= 0)
	//{
	//	lose();
	//}

	updateTexts();
}

void MainScene::checkMissileCollisions(Missile* m)
{
	QList<QGraphicsItem*> collidings = collidingItems(m);

	for (int i = collidings.length() - 1; i >= 0; i--)
	{
		// L'objet touché est un Enemy
		auto* item = collidings[i];
		if (typeid(*item) == typeid(Enemy))
		{
			// Score
			m_score++;

			// Suppression de l'ennemi de m_enemies
			auto* itemE = dynamic_cast<Enemy*>(item);
			m_enemies.removeOne(itemE);
			destroyItem(itemE);

			collidings.removeAt(i);

			// Destruction du missile
			m_missiles.removeOne(m); // suppression de la liste m_missiles
			destroyItem(m); // suppression de la scène
		}
	}
}

void MainScene::processPlayerEnemyCollision()
{
	QList<QGraphicsItem*> collidings = collidingItems(m_player);

	for (int i = collidings.length() - 1; i >= 0; i--)
	{
		// L'objet touché est un Enemy
		auto* item = collidings[i];
		if (typeid(*item) == typeid(Enemy))
		{
			// Perd instatemment
			//m_lives = 0;

			// Suppression de l'ennemi de m_enemies
			auto* itemE = dynamic_cast<Enemy*>(item);
			m_enemies.removeOne(itemE);
			destroyItem(itemE);

			collidings.removeAt(i);

			// Suppression du joueur
			removeItem(m_player);

			// Défaite
			lose();
		}
	}
}

void MainScene::destroyItem(QGraphicsItem* m)
{
	removeItem(m); // supprime de la scène
	delete m;
}

void MainScene::updateTexts()
{
	QString score = "Score: ";
	score.append(QString::number(m_score));
	//QString lives = "Lives: ";
	//lives.append(QString::number(m_lives));

	m_scoreText->setPlainText(score);
	//m_livesText->setPlainText(lives);
}

void MainScene::lose()
{
	m_running = false;

	m_updateTimer->stop();
	m_enemySpawnTimer->stop();

	QString lose = "You died.\nYour score is: ";
	lose.append(QString::number(m_score));
	lose.append("\nPress [R] to play again");

	m_loseText = addText(lose, m_arcadeFont);
	m_loseText->setPos(30, 20);
}

void MainScene::restartGame()
{
	// Reset player
	removeItem(m_player);
	addItem(m_player);
	m_player->setPos(WIN_W / 2, WIN_H - 80);

	// Reset scorse et textes
	m_score = 0;
	//m_lives = 3;

	m_scoreText->setPlainText("Score: 0");
	//m_livesText->setPlainText("Lives: 3");

	// Reset ennemis et missiles
	for (auto* e : m_enemies)
	{
		removeItem(e);
		destroyItem(e);
	}
	m_enemies.clear();

	for (auto* m : m_missiles)
	{
		removeItem(m);
		destroyItem(m);
	}
	m_missiles.clear();


	// Supprime texte lose
	removeItem(m_loseText);

	// Relance timers
	m_running = true;
	m_updateTimer->start();
	m_enemySpawnTimer->start();
}

void MainScene::keyPressEvent(QKeyEvent* evt)
{
	switch (evt->key())
	{
	case Qt::Key_Left:
		if (m_running)
			m_keyLeftDown = true;
		
		break;
	case Qt::Key_Right:
		if (m_running)
			m_keyRightDown = true;

		break;

	case Qt::Key_Up:
	case Qt::Key_Space:
		if (m_running)
			shoot();
		break;

	case Qt::Key_R:
		if (!m_running)
		{
			restartGame();
		}
		break;

	default:
		break;
	}
}

void MainScene::keyReleaseEvent(QKeyEvent* evt)
{
	switch (evt->key())
	{
	case Qt::Key_Left:
		m_keyLeftDown = false;

		break;
	case Qt::Key_Right:
		m_keyRightDown = false;

		break;
	default:
		break;
	}
}
