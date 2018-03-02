#pragma once
#include <list>

using namespace  std;

class Observer;
typedef list<Observer *> OBSERVERLIST;

class Subject
{
public:
	Subject(){};
	~Subject(){};
	virtual void Notify(unsigned int uMessage, unsigned int lParam, unsigned int wParam,int nGroupID);
	virtual void Detach(Observer * pObserver);
	virtual void Attach(Observer * pObserver);
protected:
	OBSERVERLIST m_observerlist;;
};

