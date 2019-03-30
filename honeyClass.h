#ifndef HONEYCLASS_H
#define HONEYCLASS_H

#ifdef WIN32
#pragma execution_character_set("utf-8")

#endif

#include<QSqlDatabase>
#include<QtWidgets/QWidget>
#include<QTabWidget>
#include<QComboBox>
#include<QLayout>
#include<QBoxLayout>
#include<QString>
#include<QStringList>
#include<QSplitter>
#include<QTreeWidget>
#include<QIcon>
#include<QGroupBox>
#include<QMessageBox>
#include<QEvent>
#include<QFile>
#include<QTextStream>
#include<QDir>
#include<QFileDialog>
#include<QScrollArea>
#include"ui_honeyClass.h"
#include"FirstForm.h"
#include"SecondForm.h"
#include"ThirdForm.h"
#include"StudentInfo.h"

extern QString currentClassName;
extern QList<StudentInfo> currentStudentList;

class honeyClass : public QWidget
{
	Q_OBJECT
public:	
	signals:void clickedChooseClass(QString &string);
	signals:void clickedShuffer();
	signals:void clickedChooseOneByRandom();
	signals:void clickedChooseOneBoy();
	signals:void clickedChooseOneGirl();
	signals:void clickedChooseTwoByRandom();
	signals:void clickedChooseBoyAndGirl();
	signals:void clickedChooseTwoBoy();
	signals:void clickedChooseTwoGirl();
	signals:void clickedArrangeOneByOne();
	signals:void clickedArrangeTwo();
	signals:void clickedShowStudentInformation();
	signals:void clickedDeleteStudentInformation();
	signals:void clickedImportStudentInformation();
	signals:void clickedView();
	signals:void clickedCreateFirstForm();
	signals:void clickedCreateSecondForm();
	signals:void clickedCreateThirdForm();
	signals:void appClose();
private slots:void GetFunction(QTreeWidgetItem *item,int column);
private slots:void Shuffer();
private slots:void ChooseOneByRandom();
private slots:void ChooseOneBoy();
private slots:void ChooseOneGirl();
private slots:void ChooseTwoByRandom();
private slots:void ChooseBoyAndGirl();
private slots:void ChooseTwoBoy();
private slots:void ChooseTwoGirl();
private slots:void ArrangeOneByOne();
private slots:void ArrangeTwo();
private slots:void ShowStudentInformation();
private slots:void DeleteStudentInformation();
private slots:void ImportStudentInformation();
private slots:void View();
private slots:QWidget* CreateFirstForm();
private slots:void InitCurrentClassName(const QString &text);
private slots:void closeTab(int index);

public:
	honeyClass(QWidget *parent = Q_NULLPTR);
	~honeyClass();
private:
	void lineSignalAndSlot();
	void Init();
	void CreateFunctionTree();
	void CreateCombobox();
	bool eventFilter(QObject*, QEvent*);
	void closeAllTab();	
	QList<StudentInfo> getBoyList();
	QList<StudentInfo> getGirlList();
private:
	bool allClose;
	QSplitter *splitter;
	QComboBox *classChooseButton;
	QTreeWidget *functionTree;
	QTabWidget *tabWidget;
	Ui::honeyClassClass ui;
};

#endif