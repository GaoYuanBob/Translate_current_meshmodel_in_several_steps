#pragma once
#include "qwidget.h"
#include "ui_Widget.h"

class TranslatePlugin;
class Widget : public QWidget
{
public:
	Widget(QWidget *parent, TranslatePlugin *_edit);
	~Widget();

	Ui::Form ui;

private:
	TranslatePlugin *edit;
};