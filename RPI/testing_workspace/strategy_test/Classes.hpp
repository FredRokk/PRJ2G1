#ifndef CLASSES
#define CLASSES

class Machine
{
private:
	class State* state;
public:
	Machine();
	void setCurrent(State* s);
	void next();
};

class State
{
private:
	Machine* m;
public:
	virtual void next();
};

class First: public State
{
private:
	Machine* m;
public:
	First(Machine* m);
	~First();
	void next();
};

class Second: public State
{
private:
	Machine* m;
public:
	Second(Machine* m);
	~Second();
	void next();
};

class Third: public State
{
private:
	Machine* m;
public:
	Third(Machine* m);
	~Third();
	void next();
};


#endif