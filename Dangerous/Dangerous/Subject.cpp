#include "Subject.h"
#include "Observer.h"





void Subject::Notify(unsigned int uMessage, unsigned int lParam, unsigned int wParam,int nGroupID)
{
	if (m_observerlist.empty())
		return ;
	list<Observer*>::iterator it = m_observerlist.begin();
	for (; it != m_observerlist.end();it++)
	{
		(*it)->UpdateMessage(this, uMessage, lParam, wParam);
	}
}

void Subject::Detach(Observer * pObserver)
{
	m_observerlist.remove(pObserver);
}

void Subject::Attach(Observer * pObserver)
{
	m_observerlist.push_back(pObserver);

}
