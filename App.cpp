#define _USE_MATH_DEFINES
#define MENU 0
#define PLAYING 1
#define SCORES 2
#define GAMEOVER 3
#define CONTROLS 4
#define GAMEWIN 5

#include "App.h"
#include "Al.h"
#include "Enemies.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string.h>
#include <sstream>

using namespace std;

deque<Enemies*> enemySprites;
deque<bool>checkHit;
deque<Rectangle*> m1;
deque<Rectangle*>m2;
deque<Rectangle*>m3;
vector<Rectangle*> menu;
vector<string> scoreVec;
deque<Enemies*> sprites;
bool useSpecial = false;

App::App(const char* label, int x, int y, int w, int h) : GlutApp(label, x, y, w, h) {
	
	wall = loadTexture("background.bmp");
	background = new TexRect(-1, 1, 2, 2);

	menu.push_back(new Rectangle(-0.25, 0.3, 0.5, 0.25));
	menu.push_back(new Rectangle(-0.25, 0.0, 0.5, 0.25));
	menu.push_back(new Rectangle(-0.25, -0.3, 0.5, 0.25));

	mx = -1.0;
	my = -1.0;
	score = 0;
	var = -1;
	playerChar->al = playerChar->loadTexture("playership.bmp");

	for(int i = 0; i < 26; i++){

		checkHit.push_back(false);

	}

	enemySprites.push_back(new Enemies((float)-0.8, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.5, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.2, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.1, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.4, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.7, (float)0.7, (float)0.1, (float)0.1));

	for (int i = 0; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");

	}

	enemySprites.push_back(new Enemies((float)-0.95, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.65, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.35, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.05, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.25, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.55, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.85, (float)0.9, (float)0.1, (float)0.1));

	for (int i = 6; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");

	}

	enemySprites.push_back(new Enemies((float)-0.8, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)-0.5, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)-0.2, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.1, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.4, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.7, (float)1.1, (float)0.075, (float)0.075));

	for (int i = 13; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");
	
	}

	enemySprites.push_back(new Enemies((float)-0.95, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.65, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.35, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.05, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.25, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.55, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.85, (float)1.3, (float)0.05, (float)0.05));

	for(int i = 19; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t2invade.bmp");

	}

	paused = true;
	right = true;
	left = true;
	up = true;
	down = true;
	gameOver = false;
	gameLoop = true;
	theta = (float)0.0;
	inc = (float)0.05;
	missleX = 0;
	missleY = 0.5;
	missleX1 = 0;
	missleY1 = 0.5;
	missleX2 = 0;
	missleY2 = 0.5;
	missleCount = 0;
	state = MENU;

}

void App::draw() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	 if (state == MENU){

		glColor3d(1.0, 0.0, 0.0);
		print(-0.25, 0.5, 0.0, "Space Wars 3");

		print(-0.25, 0.15, 0.0, " New Game");
		print(-0.25, 0.0, 0.0, "High Scores"); 
		print(-0.25, -0.15, 0.0, "   Controls");	
		print(-0.25, -0.30, 0.0, "      Exit");



		for (int i = 0; i < sprites.size(); i++)
		{
			glBindTexture(GL_TEXTURE_2D, enemySprites[i]->sprite);
			sprites[i]->test->TexRect::draw();
		}

		if (mx < .25 && mx > -.25 && my < 0.3 && my > 0.1){

			state = PLAYING;

		}else if (mx < .25 && mx > -.25 && my < 0.1 && my > -0.1){

			state = SCORES;

		}else if (mx < .25 && mx > -.25 && my < -0.1 && my > -0.2){

			state = CONTROLS;

		}else if(mx < .25 && mx > -.25 && my < -0.2 && my > -0.5){

			exit(0);

		}

		mx = -1.0;
		my = -1.0;

	}else if (state == PLAYING){

		if(spritesKilled == 27){

			gameOver = true;
			state = GAMEWIN;
			redraw();

		}

		if(playerChar->missle1 & !gameOver){

			for(int i = 0; i < m1.size(); i++){

				m1[i]->draw();

			}
		}

		if(playerChar->missle2 & !gameOver){

			for(int i = 0; i < m2.size(); i++){

				m2[i]->draw();

			}

		}

		if(playerChar->missle3 & !gameOver){

			for(int i = 0; i < m3.size(); i++){

				m3[i]->draw();

			}

		}


		glColor3d(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, playerChar->al);
		playerChar->test->TexRect::draw();

		for (int i = 0; i < enemySprites.size(); i++){
			if(!checkHit[i]){

				glBindTexture(GL_TEXTURE_2D, enemySprites[i]->sprite);
				enemySprites[i]->test->TexRect::draw();

			}

		}

		print(-0.9, -0.7, 0.0, "ESC = Menu");
		print(-0.9, -0.8, 0.0, "R = restart");

		if(!paused){

			print(-0.2, 0.0, 0.0, "PAUSE");

		}
		
		print(0.5, -0.8, 0.0, "Score: ");

		//std::string strscore = boost::lexical_cast<std::string>(score);

		ostringstream ss;
		ss << score;
		string strscore = ss.str();
		char *cstr = new char[strscore.length() + 1];
		strcpy(cstr, strscore.c_str());

		print(0.8, -0.8, 0.0, cstr);
		glBindTexture(GL_TEXTURE_2D, wall);
		background->draw();
		glDisable(GL_TEXTURE_2D);

	}else if(state == SCORES){

		print(-0.25, 0.75, 0.0, "HIGHSCORES");
		getScores();
		float iter = 0.5;

		for (int i = 0; i < 7; i++){

			ostringstream ss;
			ss << i + 1;
			string strscore = ss.str();
			char *cstr = new char[strscore.length() + 1];
			strcpy(cstr, strscore.c_str());

			print(-0.15, iter, 0.0, cstr);
			print(-0.10, iter, 0.0, ". ");

			string strscore1 = scoreVec[i];
			char *cstr1 = new char[strscore1.length() + 1];
			strcpy(cstr1, strscore1.c_str());

			print(-0.05, iter, 0.0, cstr1);
			iter = iter - 0.2;

		}

	}else if (state == GAMEOVER){

		if(var == -1){

			var++;
			saveScore();
		}

		print(-0.25, 0.3, 0.0, "  GAME OVER");
		
		ostringstream ss;
		ss << score;
		string strscore = ss.str();
		char *cstr = new char[strscore.length() + 1];
		strcpy(cstr, strscore.c_str());

		if(score >= highscore){

			print(-0.25, 0.0, 0.0, "New High Score!");
			print(-0.25, -0.25, 0.0, "    Score:");
			print(0.1, -0.25, 0.0, cstr);

		}else{

			print(-0.25, -0.25, 0.0, "    Score:");
			print(0.1, -0.25, 0.0, cstr);

		}

	}else if (state == CONTROLS){

		print(-0.25, 0.75, 0.0, "Instructions");
		print(-0.25, 0.3, 0.0, "Left = A");
		print(-0.25, 0.2, 0.0, "Right = D");
		print(-0.25, 0.1, 0.0, "Up = W");
		print(-0.25, 0.0, 0.0, "Down = S");
		print(-0.25, -0.1, 0.0, "Fire = SpaceBar");
		print(-0.25, -0.2, 0.0, "Special Fire = V");
		print(-0.25, -0.4, 0.0, "Return to menu = Esc");
		print(-0.25, -0.5, 0.0, "Restart Game = R");

	}else if(state == GAMEWIN){

		if(var == -1){

			var++;
			saveScore();
		}

		print(-0.25, 0.3, 0.0, "     YOU WIN");
		
		ostringstream ss;
		ss << score;
		string strscore = ss.str();
		char *cstr = new char[strscore.length() + 1];
		strcpy(cstr, strscore.c_str());

		if(score >= highscore){

			print(-0.25, 0.0, 0.0, "New High Score!");
			print(-0.25, -0.25, 0.0, "    Score:");
			print(0.1, -0.25, 0.0, cstr);

		}else{

			print(-0.25, -0.25, 0.0, "    Score:");
			print(0.1, -0.25, 0.0, cstr);

		}
		

	}

	glFlush();
	glutSwapBuffers();

}

void App::keyPress(unsigned char key) {
	
	if (paused == 1 && state == PLAYING) {
		
		if (key == 32) {

			//Standard shot 1 missile
			missleX = playerChar->test->getX() + (float)0.04;
			missleY = playerChar->test->getY() + (float)0.05;
			r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			m1.push_back(new Rectangle(missleX, missleY + (float)0.05, (float)0.02, (float)0.03, r1, r2, r3));
			playerChar->fire();
			missleCount++;

		}else if (key == 'v' && useSpecial == true) {

			//use Special
			missleX = playerChar->test->getX() + (float)0.04;
			missleY = playerChar->test->getY() + (float)0.05;
			missleX2 = playerChar->test->getX() + (float)0.04;
			missleY2 = playerChar->test->getY() + (float)0.05;
			missleX1 = playerChar->test->getX() + (float)0.04;
			missleY1 = playerChar->test->getY() + (float)0.05;
			r1 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r2 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			r3 = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
			m1.push_back(new Rectangle(missleX, missleY + (float)0.05, (float)0.02, (float)0.03, r1, r2, r3));
			m2.push_back(new Rectangle(missleX1, missleY1 + (float)0.05, (float)0.02, (float)0.03, r3, r2, r1));
			m3.push_back(new Rectangle(missleX2, missleY2 + (float)0.05, (float)0.02, (float)0.03, r2, r1, r3));
			playerChar->fire();
			missleCount++;
			useSpecial = false;
		
		}else if(key == 'w'){

			if(up){

				playerChar->test->setY(playerChar->test->getY() - 0.05);

			}else{

				playerChar->test->setY(playerChar->test->getY());

			}

		}else if(key == 'a'){

			if(left){

				playerChar->test->setX(playerChar->test->getX() - 0.05);

			}else{

				playerChar->test->setX(playerChar->test->getX());

			}

		}else if(key == 's'){

			if(down){

				playerChar->test->setY(playerChar->test->getY() - 0.05);

			}else{

				playerChar->test->setY(playerChar->test->getY());

			}
		
		}else if(key == 'd'){

			if(right){

				playerChar->test->setX(playerChar->test->getX() + 0.05);

			}else{

		
				playerChar->test->setX(playerChar->test->getX());

			}

		
		}else if(key == 27){

			//if Esc Return to Menu
			resetGame(0);

		}else if(key == 'r'){

			resetGame(1);
	
		}
		
	}
	
	 else if (key == 27 && state == MENU){
		
		//Menu on Esc
		exit(0);
		
	}else if (key == 27 && state != MENU){

		resetGame(0);
		redraw();
	
	}else if (key == 27 && state == SCORES){

		resetGame(0);

	}

	if(key == 'p'){

		//Pause game on p
		paused = !paused;

	}

	if(key == 'l'){

		//emergency quit
		exit(0);

	}
	
}
void App::mouseDown(float x, float y) {
	// Update app state
	mx = x;
	my = y;

	redraw();

}

void App::idle() {

	if (gameLoop == 1 && state == PLAYING) {

		if(paused){

			float x = playerChar->test->getX();
			float y = playerChar->test->getY();

			if(x >= 0.85){

				left = true;
				right = false;

			}else if (x <= -0.975) {

				left = false;
				right = true;

			}else{
				left = true;
				right = true;
			}

			if (y >= 0.975) {

				up = false;
				down = true;

			}else if (y <= -0.875) {

				up = true;
				down = false;

			}else{

				up = true;
				down = true;

			}

			if (playerChar->missle1 && paused) {

				missleY += (float)0.01;

				for (int i = 0; i < m1.size(); i++){

					m1[i]->setY(m1[i]->getY() + (float)0.01);

				}

			}

			if (playerChar->missle2 && paused) {

				missleX1 -= (float)0.01;
				missleY1 += (float)0.01;

				for (int i = 0; i < m2.size(); i++) {

					m2[i]->setY(m2[i]->getY() + (float)0.01);
					m2[i]->setX(m2[i]->getX() - (float)0.004);

				}
			}

			if (playerChar->missle3 && paused) {

				missleX2 += (float)0.01;
				missleY2 += (float)0.01;

				for (int i = 0; i < m3.size(); i++) {

					m3[i]->setY(m3[i]->getY() + (float)0.01);
					m3[i]->setX(m3[i]->getX() + (float)0.004);

				}

			}

			for (int i = 0; i < enemySprites.size(); i++){

				for (int j = 0; j < m1.size(); j++){

					if (enemySprites[i]->test->contains(m1[j]->getX(), m1[j]->getY()) && !checkHit[i]){

						checkHit[i] = true;
						spritesKilled++;
						m1.erase(m1.begin() + j);
						
						if (i < 20){
							score += 50;

						}else{

							useSpecial = true;
							score += 100;

						}

					}

				}

			}

			for (int i = 0; i < enemySprites.size(); i++){

				for (int j = 0; j < m2.size(); j++){

					if (enemySprites[i]->test->contains(m2[j]->getX(), m2[j]->getY()) && !checkHit[i]){

						checkHit[i] = true;
						spritesKilled++;
						m2.erase(m2.begin() + j);
						
						if (i < 20){
							score += 50;

						}else{
						
							useSpecial = true;
							score += 100;

						}

					}

				}

			}

			for (int i = 0; i < enemySprites.size(); i++){

				for (int j = 0; j < m3.size(); j++){

					if (enemySprites[i]->test->contains(m3[j]->getX(), m3[j]->getY()) && !checkHit[i]){

						checkHit[i] = true;
						spritesKilled++;
						m3.erase(m3.begin() + j);
						
						if (i < 20){
							score += 50;

						}else{
						
							score += 100;

						}

					}

				}

			}

			if(missleY > 1){

				playerChar->missle1 = false;

				if(m1.size() > 0){

					m1.pop_back();

				}

			}

			if(missleY1 > 1){

				playerChar->missle2 = false;

				if(m2.size() > 0)
					m2.pop_back();
			}

			if(missleY2 > 1){

				playerChar->missle3 = false;

				if(m3.size() > 0){

					m3.pop_back();

				}

			}

			for (int i = enemySprites.size() - 1; i >= 0; i--){

				if (enemySprites[i]->test->getY() > -1 && paused && !checkHit[i]){

					enemySprites[i]->test->setY(enemySprites[i]->test->getY() - 0.0009);

				}else if(enemySprites[i]->test->getY() > -1 && paused && checkHit[i]){

					enemySprites[i]->test->setY(enemySprites[i]->test->getY());

				}else{

					state = GAMEOVER;
					break;

				}

			}

		}

		redraw();

	}

}

GLuint App::loadTexture(const char *filename) {

	GLuint texture_id;
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	RgbImage theTexMap(filename);
	glGenTextures(1, &texture_id);
	glBindTexture(GL_TEXTURE_2D, texture_id);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, theTexMap.GetNumCols(), theTexMap.GetNumRows(), GL_RGB, GL_UNSIGNED_BYTE, theTexMap.ImageData());

	return texture_id;

}

void App::print(float x, float y, float z, char *string){

	glColor3d(1.0, 1.0, 1.0);
	glRasterPos2f(x, y);

	for (int i = 0; i < (int)strlen(string); i++){

		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string[i]);
	
	}

}

void App::saveScore(){

	ofstream file;
	file.open("highscore.txt", ofstream::out | ofstream::app);
	
	file << score << endl; 
	file.close();


	ifstream rfile("highscore.txt");
	string line;
	vector<int> scoreArr;

	while (getline(rfile, line)){

		int num = atoi(line.c_str());
		scoreArr.push_back(num);
		
	}

	sort(scoreArr.begin(), scoreArr.end());
	int i = scoreArr.size() - 1;
	rfile.close();
	highscore = scoreArr[i];

	file.open("highscore.txt", ios::out | ios::trunc);

	for (i = scoreArr.size() - 1; i >= 0; i--){

		file << scoreArr[i] << endl;

	}

	file.close();

	
}

void App::getScores(){

	//print High Score
	string strscore;
	ifstream myfile;
;	myfile.open("highscore.txt");
		
	while(!myfile.eof()){

		std::getline(myfile, strscore);
		scoreVec.push_back(strscore);
		
	}
	myfile.close();

	for(int i = 0; i < scoreVec.size(); i++){

		cout << scoreVec[i] << endl;

	}

}

void App::resetGame(int gameStateNum){

	state = gameStateNum;
	gameOver = false;
	spritesKilled = 0;
	score = 0;
	playerChar->test->setX(0.0);
	playerChar->test->setY(-0.7);
	enemySprites.clear();
	m1.clear();
	m2.clear();
	m3.clear();
	checkHit.clear();

	for(int i = 0; i < 26; i++){

		checkHit.push_back(false);

	}

	enemySprites.push_back(new Enemies((float)-0.8, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.5, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.2, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.1, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.4, (float)0.7, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.7, (float)0.7, (float)0.1, (float)0.1));

	for (int i = 0; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");

	}

	enemySprites.push_back(new Enemies((float)-0.95, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.65, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.35, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)-0.05, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.25, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.55, (float)0.9, (float)0.1, (float)0.1));
	enemySprites.push_back(new Enemies((float)0.85, (float)0.9, (float)0.1, (float)0.1));

	for (int i = 6; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");

	}

	enemySprites.push_back(new Enemies((float)-0.8, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)-0.5, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)-0.2, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.1, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.4, (float)1.1, (float)0.075, (float)0.075));
	enemySprites.push_back(new Enemies((float)0.7, (float)1.1, (float)0.075, (float)0.075));

	for (int i = 13; i < enemySprites.size(); i++){

		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t1invade.bmp");
	
	}

	enemySprites.push_back(new Enemies((float)-0.95, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.65, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.35, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)-0.05, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.25, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.55, (float)1.3, (float)0.05, (float)0.05));
	enemySprites.push_back(new Enemies((float)0.85, (float)1.3, (float)0.05, (float)0.05));
	
	for (int i = 19; i < enemySprites.size(); i++){
	
		enemySprites[i]->sprite = enemySprites[i]->loadTexture("t2invade.bmp");
	
	}

	redraw(); 

}

App::~App() {

	delete r;

}
