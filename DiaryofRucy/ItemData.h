#pragma once
enum PAGE
{
	PAGE_1
};

struct MyStruct
{
	/*
	구조체

	*/

};
class ItemData
{
protected:
	GImage _image;
	RECT _rc;
	string _name;
	string _fileLocation;
	float _x, _y;
	int _width;
	int _height;
	int _frameX;
	int _frameY;
	bool _RGB;
	bool _activeFlg;
	float _atk;
	float _mpk;
	float _Mhp;
	float _Mmp;
	int _page;
	string _ex;

	vector<string>name1;
	vector<string>fileLocation1;
	vector<string>ex1;
	vector<float>x1;
	vector<float>y1;
	vector<int>width1;
	vector<int>height1;
	vector<bool>RGB1;
	vector<float>atk1;
	vector<float>mpk1;
	vector<float>Mhp1;
	vector<float>Mmp1;
	vector<int>page1;
	vector<bool>activeFlg1;

protected:
	string _category;
	string _ability;
	string _ability2;
	string _ability3;
	string _tier;

	float _balance;
	float _addNum;
	float _addNum2;
	float _addNum3;


public:
	void init(string name, string fileLocation, string ex, float x, float y, int width, int height,
		bool RGB, float atk, float mpk, float Mhp, float Mmp, int page, bool activeFlg);
	void tier1(string tier, string category, float balance, string ability, float addNum);
	void tier2(string tier, string category, float balance, string ability, float addNum, string ability2, float addNum2);
	void tier3(string tier, string category, float balance, string ability, float addNum, string ability2, float addNum2, string ability3, float addNum3);

	//2. 참조형태
	GImage getImage() { return this->_image; }
	RECT getRect() { return this->_rc; }
	int getWidth() { return this->_width; }
	int getHeight() { return this->_height; }
	bool getRGB() { return this->_RGB; }

	string getName() { return this->_name; }
	string getFileLocation() { return this->_fileLocation; }
	string getEx() { return this->_ex; }

	float getX() { return this->_x; }
	float getY() { return this->_y; }
	float getAtk() { return this->_atk; }
	float getMpk() { return this->_mpk; }
	float getMhp() { return this->_Mhp; }
	float getMmp() { return this->_Mmp; }

	int getPage() { return this->_page; }
	bool getactiveFlg() { return this->_activeFlg; }
	ItemData() {};
	~ItemData() {};
};

