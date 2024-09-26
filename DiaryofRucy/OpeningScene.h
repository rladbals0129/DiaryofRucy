#pragma once
#include "GameNode.h"
struct Particle
{
	int x;
	int y;
	float speed;
	int sinf;
	int cosf;
	int rnd;
	int size;
	float alpha2;
};
class OpeningScene : public GameNode
{
private:
	//Particle particle[20];
	vector<Particle>particle;
	GImage* _image;
	GImage* _new;
	GImage* _option;
	GImage* _end;
	GImage* _particle;
	GImage* _choose;
	GImage* _press;
	RECT rc1;
	RECT rc2;
	RECT rc3;
	RECT rc4;

	RECT s1;
	RECT s2;
	RECT s3;
	RECT s4;

	RECT particle1;
	RECT particle2;
	RECT particle3;
	RECT particle4;

	int count;
	int count1;
	int pcount;
	int alpha1;
	int alpha;
	int palpha;
	int speed;
	bool clicked;


	bool newStart;
	bool continued;
public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);

	OpeningScene() {}
	~OpeningScene() {}
};
