#ifndef valuechangehandler_h
#define valuechangehandler_h

class iValueChangeHandler
{
public:
	virtual ~iValueChangeHandler(){}
	virtual void ValueChange(float) = 0;
};

#endif
