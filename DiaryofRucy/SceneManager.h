#pragma once
#include "SingletonBase.h"

class GameNode;


class SceneManager : public SingletonBase <SceneManager>
{
public:
	typedef map<string, GameNode*>mapSceneList;
	typedef map<string, GameNode*>::iterator mapSceneIter;

private:
	static GameNode* _currentScene;
	static GameNode* _loadingScene;
	static GameNode* _readyScene;

	mapSceneList _mSceneList;
	mapSceneList _mLodingSceneList;
public:
	HRESULT init();
	void release(void);
	void update(void);
	void render(void);
	void d2drender(void);
	void UIrender(void);

	GameNode* addScene(string sceneName, GameNode* scene);
	GameNode* addLoadingScene(string loadingSceneName, GameNode* scene);

	HRESULT chanegeScene(string sceneName);

	bool findScene(string sceneName);

	friend DWORD CALLBACK loadingThread(LPVOID prc);

	SceneManager() {}
	~SceneManager() {}

};

