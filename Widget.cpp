#include "Widget.h"

Widget::Widget(QWidget *parent, TranslatePlugin *_edit)
{
	ui.setupUi(this);
	this->edit = _edit;
}

Widget::~Widget()
{

}