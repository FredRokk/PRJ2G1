#ifndef STATE
#define STATE

class State
{
public:
	virtual ~State();
	virtual void up();
	virtual void down();
	virtual void left();
	virtual void right();
	virtual void onePlayer();
	virtual void twoPlayer();
	virtual void back();
	virtual void fire();
	virtual void hit(int field);
	void miss();

protected:
	class GameThreadFunctor* gameTF;
	bool returning_ = false;
};

#endif