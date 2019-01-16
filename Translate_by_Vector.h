#pragma once

#include <common/interfaces.h>
#include "Widget.h"

class TranslatePlugin : public QObject, public MeshEditInterface
{
	Q_OBJECT
	Q_INTERFACES(MeshEditInterface)
		
public:
	TranslatePlugin();
    virtual ~TranslatePlugin() = default;
	static QString Info();

    bool StartEdit(MeshModel &, GLArea * , MLSceneGLSharedDataContext* ) override;

// no implemention
	void EndEdit(MeshModel & , GLArea * , MLSceneGLSharedDataContext* ) override {};
    void Decorate(MeshModel & , GLArea * , QPainter * ) override {};
    void Decorate (MeshModel & , GLArea * ) override {};
    void mousePressEvent(QMouseEvent *, MeshModel &, GLArea * ) override {};
    void mouseMoveEvent(QMouseEvent *, MeshModel &, GLArea * ) override {};
    void mouseReleaseEvent(QMouseEvent * , MeshModel & , GLArea * ) override {};
	void keyReleaseEvent(QKeyEvent *, MeshModel &, GLArea *) override {};
	void suggestedRenderingData(MeshModel &, MLRenderingData& ) override{};

public slots:
	void slot_OK_pressed();
	void slot_translate();

private:
    QPoint cur;
	QFont qFont;

	GLArea * gla;
	Widget * widget;
	MeshModel *m;
	vcg::Point3f translation_vector;
	uint total_steps, cur_step;
};