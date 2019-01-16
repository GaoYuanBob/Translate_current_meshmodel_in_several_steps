#include <meshlab/glarea.h>
#include "Translate_by_Vector.h"
#include <meshlabplugins/edit_Customized/Mesh.h>

using namespace std;
using namespace vcg;

TranslatePlugin::TranslatePlugin() : widget(nullptr), total_steps(1), cur_step(1)
{
	qFont.setFamily("Helvetica");
	qFont.setPixelSize(12);
}

QString TranslatePlugin::Info()
{
	return tr("Return detailed info about a picked face or vertex of the model.");
}

void TranslatePlugin::slot_OK_pressed()
{
	if(widget->ui.lineEdit_steps->text().toUInt() < 1)
	{
		QMessageBox::critical(widget, QString::fromLocal8Bit("���ش�����ʾ��"), QString::fromLocal8Bit("����һ������ ���� ���費��������!"), QMessageBox::Close);
		return;
	}

	widget->ui.lineEdit_X->setEnabled(false);
	widget->ui.lineEdit_Y->setEnabled(false);
	widget->ui.lineEdit_Z->setEnabled(false);
	widget->ui.lineEdit_steps->setEnabled(false);

	translation_vector = Point3f{ widget->ui.lineEdit_X->text().toFloat(), widget->ui.lineEdit_Y->text().toFloat() , widget->ui.lineEdit_Z->text().toFloat() };
	total_steps = widget->ui.lineEdit_steps->text().toUInt();
	
	auto progress_text = QString::number(0);
	progress_text += " / ";
	progress_text += QString::number(total_steps);
	widget->ui.label_cur_progress->setText(progress_text);

	printf("��ƽ������(%.2f, %.2f, %.2f)��Ϊ %d ������\n", translation_vector.X(), translation_vector.Y(), translation_vector.Z(), total_steps);
}

void TranslatePlugin::slot_translate()
{
	if(cur_step == total_steps + 1)
	{
		widget->ui.pushButton_OK->setEnabled(false);	// ����˾Ͳ��õ� OK ��
		QMessageBox::information(widget, QString::fromLocal8Bit("�����ʾ��"), QString::fromLocal8Bit("ƽ�������!"), QMessageBox::Close);
		return;
	}
	// tri::UpdatePosition<CMeshO>::Translate(m->cm, translation_vector / total_steps);	// ����ģ�Ͳ��ᶯ
	Matrix44f trans_mat;
	trans_mat.SetIdentity();
	trans_mat[0][3] = translation_vector.X() * cur_step / total_steps;
	trans_mat[1][3] = translation_vector.Y() * cur_step / total_steps;
	trans_mat[2][3] = translation_vector.Z() * cur_step / total_steps;

	m->cm.Tr = trans_mat;

	auto progress_text = QString::number(cur_step);
	progress_text += " / ";
	progress_text += QString::number(total_steps);
	widget->ui.label_cur_progress->setText(progress_text);

	++cur_step;

	gla->update();
}

//  ��ƽ��������Ϊ�ಽ���� - 2019.1.16 - GY
bool TranslatePlugin::StartEdit(MeshModel &_m, GLArea * _gla, MLSceneGLSharedDataContext* )
{
	gla = _gla;
	m = &_m;

	if (!widget)
	{
		widget = new Widget(gla->window(), this);
		connect(widget->ui.pushButton_OK, SIGNAL(clicked()), this, SLOT(slot_OK_pressed()));
		connect(widget->ui.pushButton_Translate, SIGNAL(clicked()), this, SLOT(slot_translate()));
	}
	widget->show();

	return true;
}