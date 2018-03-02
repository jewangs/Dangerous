#pragma once

class Subject;

class Observer
{
public:
	Observer(int groupID){ m_nGroupID = groupID; };
	Observer(){ m_nGroupID = -1; };
	virtual int UpdateMessage(Subject * pSubject, unsigned int uMessage, unsigned lParam, unsigned int wParam){ return 0; };
private:
	int m_nGroupID;
};

