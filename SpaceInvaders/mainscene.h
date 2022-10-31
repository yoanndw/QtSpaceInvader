#pragma once

#ifndef _MAIN_SCENE_H_
#define _MAIN_SCENE_H_

#include <QFont>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QKeyEvent>
#include <QRandomGenerator>

#include "enemy.h"
#include "globalconsts.h"
#include "missile.h"
#include "player.h"

class MainScene : public QGraphicsScene
{
	Q_OBJECT

	static const int PLAYER_SPD = 5;
	static const int ENEMY_MIN_SPD = 2;
	static const int ENEMY_MAX_SPD = 5;

	QFont m_arcadeFont; // Symtext: https://www.dafont.com/symtext.font

	QRandomGenerator* m_rng;

	QTimer* m_updateTimer;
	QTimer* m_enemySpawnTimer;

	bool m_keyLeftDown, m_keyRightDown;

	Player* m_player;

	QList<Missile*> m_missiles;
	QList<Enemy*> m_enemies;

	// Scores
	int m_score;
	//int m_lives;
	bool m_running;

	QGraphicsTextItem* m_scoreText;
	//QGraphicsTextItem* m_livesText;
	QGraphicsTextItem* m_loseText;

public:
	MainScene(QGraphicsView* parent);

	void loadFont();

	void spawnEnemy();
	void shoot();

	void checkMissileCollisions(Missile* m);
	void processPlayerEnemyCollision();
	
	void destroyItem(QGraphicsItem* m);

	void updateTexts();

	void lose();

	void restartGame();

	void keyPressEvent(QKeyEvent* evt);
	void keyReleaseEvent(QKeyEvent* evt);

public slots:
	void gameUpdate();
};

#endif

