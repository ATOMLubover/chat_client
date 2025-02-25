#include "Polisher.h"

Polisher* Polisher::GetInstance()
{
    static Polisher polisher;
    return &polisher;
}

void Polisher::Repolish( QWidget* widget )
{ 
    widget->style()->unpolish( widget );
    widget->style()->polish( widget );
}
